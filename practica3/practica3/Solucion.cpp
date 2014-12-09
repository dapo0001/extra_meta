/**
 * @file Solucion.cpp
 * @authors: Pablo Molina González y Diego Alberto Pérez Ortega
 */

// Activar para mostrar cout
//#define DEBUG 1


#include "Solucion.h"
#include <math.h>
#include <iostream>
#include <ctime>
using namespace std;

int Solucion::llamadasAFuncionObjetivo = 0;

/**
 * @param _semilla Si se especifica no se pide semilla
 */
Solucion::Solucion():
	valorActual(99999999),
	valorSiguiente(99999999),
	solucionActual(0),
	n(0),
	matrices(0)
{
	solucionVecina.primero = -1;
	solucionVecina.segundo = -1;
}

Solucion::~Solucion()
{
	delete solucionActual;
}


/* Métodos del proceso *********************************************************************/

/**
 * Cambia dos posiciones del vector
 * @pre Si las posiciones pasadas no son válidas dará error
 */
void Solucion::cambiarPosicion (int* v, unsigned int pos1, unsigned int pos2) {
	int valor = v[pos1];
	v[pos1] = v[pos2];
	v[pos2] = valor;
}

/**
 * Se encarga de permutar valores de forma aleatoria seg?n la semilla asignada
 * @pre La semilla debe ser un valor admisible por srand
 */
void Solucion::solucionInicial () {
	for (unsigned int i = 0; i < n; i++) {
		this->solucionActual[i] = i;
	}

	for (unsigned int i = 0; i < n; i++) {
		unsigned int pos1 = rand() % n;
		unsigned int pos2 = rand() % n;
		cambiarPosicion(solucionActual, pos1, pos2);
	}

	cambiarPosicion(solucionActual, 0, 2);
	cambiarPosicion(solucionActual, 0, 1);

	funcionObjetivo();
#ifdef DEBUG
	imprimir();
	cout << endl << "Nueva: " << valorActual << endl;
#endif
}

/**
 * Calcula el valor de la solución actual aplicando la fórmula a todos
 * los operandos de las matrices de flujo y distancia.
 */
void Solucion::funcionObjetivo(){
	Solucion::llamadasAFuncionObjetivo += 1;
	valorActual = 0;

	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			valorActual +=
				matrices->flujo[i]->at(j) *
				matrices->distancia[solucionActual[i]]->at(j);
		}
	}
	
	//for (unsigned int k = 0; k < n; k++) {
	//	valorActual -=
	//		matrices.flujo[k]->at(k) *
	//		matrices.distancia[k]->at(k);
	//}
}

/**
 * Calcula el valor de la solución actual sin tener que recorrer todo el
 * contenido de las matrices. Para ello usa la solucion actual y el vector
 * de cambios en la solucionActual.
 */
void Solucion::factorizacion () {
	valorSiguiente = valorActual;
	int fp; // FlujoPrimero
	int dp; // DistanciaPrimera
	int fs; // FlujoSegundo
	int ds; // DistanciaSegunda

	for (unsigned int i = 0; i < n; i++) {
		/*
		valorSiguiente -=
			matrices.flujo[solucionVecina.primero]->at(i) *
			matrices.distancia[solucionActual[solucionVecina.primero]]->at(i);

		valorSiguiente -=
			matrices.flujo[solucionVecina.segundo]->at(i) *
			matrices.distancia[solucionActual[solucionVecina.segundo]]->at(i);

		valorSiguiente +=
			matrices.flujo[solucionVecina.primero]->at(i) *
			matrices.distancia[solucionActual[solucionVecina.segundo]]->at(i);

		valorSiguiente +=
			matrices.flujo[solucionVecina.segundo]->at(i) *
			matrices.distancia[solucionActual[solucionVecina.primero]]->at(i);
		*/

		// v = v + ( -fp*dp -fs*ds     +fp*ds +fs*dp ) =
		//   = v + ((+fs*dp -fp*dp) + (+fp*ds +fs*ds)) =
		//   = v + (dp*(fs -fp)     + ds*(fp - fs))
		
		fp = matrices->flujo[solucionVecina.primero]->at(i);
		dp = matrices->distancia[solucionActual[solucionVecina.primero]]->at(i);
		fs = matrices->flujo[solucionVecina.segundo]->at(i);
		ds = matrices->distancia[solucionActual[solucionVecina.segundo]]->at(i);
		valorSiguiente = valorSiguiente + (dp * (fs - fp) + ds * (fp - fs));
	}
}

/**
 * Aplica el vector de cambios a la solucion actual para llegar a un nuevo
 * vecino. Si el valor de 'valorSiguiente' es el mismo que 'valorActual'
 * calcula su nuevo valor mediante el método factorización, en caso contrario
 * se considera que ya está correctamente calculado.
 */
void Solucion::aplicarVecindad () {
	if (solucionVecina.primero != -1 && solucionVecina.segundo != -1) {
		factorizacion();
		cambiarPosicion(solucionActual, solucionVecina.primero, solucionVecina.segundo);
		solucionVecina.primero = solucionVecina.segundo = -1;
		valorActual = valorSiguiente;
	}
}


/* Interfaz de la práctica *********************************************************************/

/**
 * Imprime el vector permutación en la salida estándar
 */
void Solucion::imprimir(){
	for(unsigned int i = 0; i < n; i++){
		cout << solucionActual[i] << " ";
	}
	cout << endl;
}

/* Algoritmos *******************************************************************************/


void Solucion::busquedaLocal(){
#ifdef DEBUG
	clock_t inicio,fin;
#endif
	int numIteraciones = 0;
	unsigned int val1 = 0;
	unsigned int val2 = 1;
	bool* DLB = new bool[n];
	bool dlbAUno = false;

	for (unsigned int i = 0; i < n; i++) {
		DLB[i] = false;
	}

#ifdef DEBUG
	inicio = clock();
#endif
	
	while (val1 != n && val2 < n && !dlbAUno && numIteraciones < 10000) {
		if (DLB[val1] == false) {
			solucionVecina.primero = val1;
			solucionVecina.segundo = val2;
			factorizacion();
		
			if (valorSiguiente < valorActual) {
#ifdef DEBUG
				cout << "Se mejora la solucion" << endl;
				cout << "Valor Actual " << valorActual << endl;
				cout << "Valor Siguiente " << valorSiguiente << endl;
#endif
				aplicarVecindad();
#ifdef DEBUG
				imprimir();
#endif
				val1 = 0;
				val2 = 1;
			}
		}
		
		numIteraciones++;
		
		val2++;
		solucionVecina.primero = solucionVecina.segundo = -1;

		if (val2 == n) {
			DLB[val1] = true;
			val1++;
			val2 = val1 + 1;

			// Comprobamos si el DLB está entero a 1
			dlbAUno = true;
			for (unsigned int i = 0; i < n && dlbAUno; i++) {
				dlbAUno = dlbAUno && DLB[i];
			}
		}
	}

#ifdef DEBUG
	fin = clock();
	cout << endl <<
		"Tiempo de ejecución: " << (float) (fin - inicio) / CLOCKS_PER_SEC << "ms"
		<< endl <<
		"Número de iteraciones: " << numIteraciones
		<< endl <<
		"La mejor solución obtenida es " << valorActual << endl;
	imprimir();
#endif

	delete DLB;

}

void Solucion::greedy () {
#ifdef DEBUG
	clock_t inicio, fin;
#endif

	// Valores auxiliares
	unsigned int i, j;
	int j1;
	int aux;
	bool swapFlujo;
	bool swapDistancia;
	
	// Vectores con las medias de flujo/distancia
	int* mediaFlujo = new int[n];
	int* mediaDistancia = new int[n];
	int mediaFlujoActual;
	int mediaDistanciaActual;

	// La media de la posicion i corresponde al
	// edificio número posicionesFlujo[i]
	// (ídem para distancia)
	int* posicionesFlujo = new int[n];
	int* posicionesDistancia = new int[n];

#ifdef DEBUG
	// Inicio del reloj
	inicio = clock();
#endif

	// Almacena la media de flujos y distancias para cada
	// edificio/localizacion
	for (i = 0; i < n; i++) {
		
		posicionesFlujo[i] = i;
		posicionesDistancia[i] = i;
		mediaFlujoActual = 0;
		mediaDistanciaActual = 0;

		for (j = 0; j < n; j++) {
			mediaFlujoActual += matrices->flujo[i]->at(j);
			mediaDistanciaActual += matrices->distancia[i]->at(j);
		}
		
		mediaFlujoActual /= n;
		mediaDistanciaActual /= n;
		mediaFlujo[i] = mediaFlujoActual;
		mediaDistancia[i] = mediaDistanciaActual;

		// Hacemos insercion, ordenando los flujos
		// de menor a mayor y las distancias de mayor a menor
		swapFlujo = true;
		swapDistancia = true;
		for (j = i; j > 0 && (swapFlujo || swapDistancia); j--) {
			j1 = j - 1;

			// Swap de flujos
			if (swapFlujo && mediaFlujo[j] > mediaFlujo[j1]) {
				aux = mediaFlujo[j];
				mediaFlujo[j] = mediaFlujo[j1];
				mediaFlujo[j1] = aux;

				aux = posicionesFlujo[j];
				posicionesFlujo[j] = posicionesFlujo[j1];
				posicionesFlujo[j1] = aux;
			} else {
				swapFlujo = false;
			}

			// Swap de distancias
			if (swapDistancia && mediaDistancia[j] < mediaDistancia[j1]) {
				aux = mediaDistancia[j];
				mediaDistancia[j] = mediaDistancia[j1];
				mediaDistancia[j1] = aux;

				aux = posicionesDistancia[j];
				posicionesDistancia[j] = posicionesDistancia[j1];
				posicionesDistancia[j1] = aux;
			} else {
				swapDistancia = false;
			}
		}
	}

	// Guardamos los resultados
	for (i = 0; i < n; i++) {
		solucionActual[posicionesFlujo[i]] = posicionesDistancia[i];
	}

	funcionObjetivo();

#ifdef DEBUG
	fin = clock();
	cout << endl
		<< "Tiempo total: " << (float)(fin - inicio)/CLOCKS_PER_SEC << "ms" << endl
		 << "Valor: " << valorActual << endl;

	imprimir();
#endif

	delete mediaFlujo;
	delete mediaDistancia;
	delete posicionesFlujo;
	delete posicionesDistancia;
}

void Solucion::setQAP (QAP* qap)  {
	this->matrices = qap;
	n = qap->getNumComp();
	delete solucionActual;
	this->solucionActual = new int[n];
}

void Solucion::setSolucionActual (int* _s, int valor) {
	for (unsigned int i = 0; i < n; i++) {
		solucionActual[i] = _s[i];
	}
	valorActual = valor;
}

void Solucion::setSolucionActual (int* _s) {
	for (unsigned int i = 0; i < n; i++) {
		solucionActual[i] = _s[i];
	}
	funcionObjetivo();
}

Solucion* Solucion::cruzarPosicion (Solucion* s) {
	// this posicion
	// s flujo

	Solucion* hijo = new Solucion();
	hijo->setQAP(matrices);
	hijo->setSolucionActual(this->solucionActual, this->n);

	vector<int> saco;

	for (unsigned int i = 0; i < n; i++) {
		if (this->solucionActual[i] != s->solucionActual[i]) {
			saco.push_back(this->solucionActual[i]);
		}
	}

	int randomPosition;
	vector<int>::iterator it;

	for (unsigned int i = 0; i < n; i++) {
		if (this->solucionActual[i] != s->solucionActual[i]) {
			randomPosition = rand() % saco.size();
			hijo->solucionActual[i] = saco.at(randomPosition);

			it = saco.begin();
			it += randomPosition;
			saco.erase(it);
		}else{
			hijo->solucionActual[i] = this->solucionActual[i];
		}
	}
	hijo->funcionObjetivo();

	return hijo;
}


void Solucion::cruzarPosicion(Solucion* padre2, Solucion* &hijo1,Solucion* &hijo2){

	hijo1 = new Solucion();
	hijo2 = new Solucion();
	hijo1->setQAP(matrices);
	hijo2->setQAP(matrices);
	hijo1->setSolucionActual(this->solucionActual, this->n);
	hijo2->setSolucionActual(this->solucionActual, this->n);

	vector<int> saco1,saco2;

	for (unsigned int i = 0; i < n; i++) {
		if (this->solucionActual[i] != padre2->solucionActual[i]) {
			saco1.push_back(this->solucionActual[i]);
		}
	}
	saco2 = saco1;

	int randomPosition,randomPosition2;
	vector<int>::iterator it;

	for (unsigned int i = 0; i < n; i++) {
		if (this->solucionActual[i] != padre2->solucionActual[i]) {
			randomPosition = rand() % saco1.size();
			randomPosition2 = rand() % saco2.size();
			hijo1->solucionActual[i] = saco1.at(randomPosition);
			hijo2->solucionActual[i] = saco2.at(randomPosition2);

			it = saco1.begin();
			it += randomPosition;
			saco1.erase(it);

			it = saco2.begin();
			it+=randomPosition2;
			saco2.erase(it);
		}else{
			hijo1->solucionActual[i] = this->solucionActual[i];
			hijo2->solucionActual[i] = this->solucionActual[i];
		}
	}


	//hijo1->funcionObjetivo();
	//hijo2->funcionObjetivo();
}