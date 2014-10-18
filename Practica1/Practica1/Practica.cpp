/**
 * @file Practica.cpp
 * @authors: Pablo Molina González y Diego Alberto Pérez Ortega
 */

// Activar para mostrar cout
#define DEBUG 1


#include "Practica.h"
#include <math.h>
#include <iostream>
#include <ctime>
using namespace std;

/**
 * @param _semilla Si se especifica no se pide semilla
 */
Practica::Practica(int _semilla):
	valorActual(99999999),
	valorSiguiente(99999999)
{
	if (_semilla == -1) {
		cout<<"¡ATENCION! La semilla proporcionada se utilizara durante toda la ejecucion"<<endl<<endl;
		cout << "Introduzca la semilla ";
		cin >> semilla;
	} else {
		semilla = _semilla;
	}
}

Practica::~Practica()
{
	delete solucionActual;
}


/* Métodos del proceso *********************************************************************/

/**
 * Cambia dos posiciones del vector
 * @pre Si las posiciones pasadas no son válidas dará error
 */
void Practica::cambiarPosicion (int* v, unsigned int pos1, unsigned int pos2) {
	int valor = v[pos1];
	v[pos1] = v[pos2];
	v[pos2] = valor;
}

/**
 * Se encarga de permutar valores de forma aleatoria según la semilla asignada
 * @pre La semilla debe ser un valor admisible por srand
 */
void Practica::solucionInicial (int semilla){
	srand(semilla);
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
void Practica::funcionObjetivo(){
	valorActual = 0;

	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			valorActual +=
				matrices.flujo[i]->at(j) *
				matrices.distancia[solucionActual[i]]->at(j);
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
void Practica::factorizacion () {
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
		
		fp = matrices.flujo[solucionVecina.primero]->at(i);
		dp = matrices.distancia[solucionActual[solucionVecina.primero]]->at(i);
		fs = matrices.flujo[solucionVecina.segundo]->at(i);
		ds = matrices.distancia[solucionActual[solucionVecina.segundo]]->at(i);
		valorSiguiente = valorSiguiente + (dp * (fs - fp) + ds * (fp - fs));
	}
}

/**
 * Aplica el vector de cambios a la solucion actual para llegar a un nuevo
 * vecino. Si el valor de 'valorSiguiente' es el mismo que 'valorActual'
 * calcula su nuevo valor mediante el método factorización, en caso contrario
 * se considera que ya está correctamente calculado.
 */
void Practica::aplicarVecindad () {
	if (solucionVecina.primero != -1 && solucionVecina.segundo != -1) {
		factorizacion();
		cambiarPosicion(solucionActual, solucionVecina.primero, solucionVecina.segundo);
		solucionVecina.primero = solucionVecina.segundo = -1;
		valorActual = valorSiguiente;
	}
}

void Practica::algoritmo (unsigned int valor) {
	if(valor == 1){
		solucionInicial(semilla);
		busquedaLocal();
	} else if (valor == 2) {
		solucionInicial(semilla);
		tabu();
	} else if (valor == 3) {
		greedy();
	}
}



/* Interfaz de la práctica *********************************************************************/

/**
 * Menú para la lectura de ficheros
 * @param num Si se especifica un valor concreto carga este fichero directamente sin preguntar
 */
void Practica::menuFichero(int num){
	if (num == 0) {
		int val = 0;
		cout<<endl;
		cout<<"Escoja el fichero a leer"<<endl;
		cout<<"1. bur26a"<<endl;
		cout<<"2. bur26b"<<endl;
		cout<<"3. chr20a"<<endl;
		cout<<"4. chr25a"<<endl;
		cout<<"5. els19"<<endl;
		cout<<"6. esc32a"<<endl;
		cout<<"7. kra32"<<endl;
		cout<<"8. lipa90a"<<endl;
		cout<<"9. nug25"<<endl;
		cout<<"10. sko42"<<endl;
		cout<<"11. sko49"<<endl;
		cout<<"12. tai30a"<<endl;
		cout<<"13. tai30b"<<endl;
		cout<<"14. tai35a"<<endl;
		cout<<"15. tai35b"<<endl;
		cout<<"16. tai40a"<<endl;
		cout<<"17. tai50a"<<endl;
		cout<<"18. tai50b"<<endl;
		cout<<"19. tai60a"<<endl;
		cout<<"20. tho40"<<endl;
		cout<<"21. salir"<<endl;
		cout<<endl;    
		do {
			cin >> val;
		} while (val < 0 || val > 21);

		if(val==21) exit(EXIT_SUCCESS);

		cargarFich(val);
		
	} else {
		cout << "Fichero " << num << endl;
		cargarFich(num);
	}
}

/**
 * Menú para seleccionar el algoritmo que se desea ejecutar
 * @param num Si se especifica este valor se ejecuta el algoritmo sin preguntar
 */
void Practica::menuAlgoritmo(int num){
	if (num == 0) {
		int val = 0;
		cout<<endl;
		cout<<"Selecciona el algoritmo que deseas usar"<<endl;
		cout << "1. Busqueda local" << endl;
		cout << "2. Busqueda tabu" << endl;
		cout << "3. Algoritmo Greedy" << endl;
		cout << "4. Salir" << endl;
		cout<<endl;
		do {
			cin>>val;
		} while (val < 1 || val > 4);

		if(val==4) exit(EXIT_SUCCESS);
		algoritmo(val);
			
	} else {
		cout << "Algoritmo " << num << endl;
		algoritmo(num);
	}
}

/**
 * Método que carga el fichero seleccionado
 */
void Practica::cargarFich(int valor){
    switch(valor){
        case 1:
            matrices.abrir("ficheros/bur26a.dat");
            break;
        case 2:
            matrices.abrir("ficheros/bur26b.dat");
            break;
        case 3:
            matrices.abrir("ficheros/chr20a.dat");
            break;
        case 4:
            matrices.abrir("ficheros/chr25a.dat");
            break;
        case 5:
            matrices.abrir("ficheros/els19.dat");
            break;
        case 6:
            matrices.abrir("ficheros/esc32a.dat");
            break;
        case 7:
            matrices.abrir("ficheros/kra32.dat");
            break;
        case 8:
            matrices.abrir("ficheros/lipa90a.dat");
            break;
        case 9:
            matrices.abrir("ficheros/nug25.dat");
            break;
        case 10:
            matrices.abrir("ficheros/sko42.dat");
            break;
        case 11:
            matrices.abrir("ficheros/sko49.dat");
            break;
        case 12:
            matrices.abrir("ficheros/tai30a.dat");
            break;
        case 13:
            matrices.abrir("ficheros/tai30b.dat");
            break;
        case 14:
            matrices.abrir("ficheros/tai35a.dat");
            break;
        case 15:
            matrices.abrir("ficheros/tai35b.dat");
            break;
        case 16:
            matrices.abrir("ficheros/tai40a.dat");
            break;
        case 17:
            matrices.abrir("ficheros/tai50a.dat");
            break;
        case 18:
            matrices.abrir("ficheros/tai50b.dat");
            break;
        case 19:
            matrices.abrir("ficheros/tai60a.dat");
            break;
        case 20:
            matrices.abrir("ficheros/tho40.dat");
            break;
    }

	n = matrices.getNumComp();
	solucionActual = new int[n];
	for (unsigned int i = 0; i < n; i++) {
		solucionActual[i] = i;
	}

}

/**
 * Imprime el vector permutación en la salida estándar
 */
void Practica::imprimir(){
	for(unsigned int i = 0; i < n; i++){
		cout << solucionActual[i] << " ";
	}
	cout << endl;
}

/* Algoritmos *******************************************************************************/


void Practica::busquedaLocal(){
	clock_t inicio,fin;
	int numIteraciones = 0;
	unsigned int val1 = 0;
	unsigned int val2 = 1;
	bool* DLB = new bool[n];
	bool dlbAUno = false;

	for (unsigned int i = 0; i < n; i++) {
		DLB[i] = false;
	}

	inicio = clock();
	
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

	fin = clock();
	
	cout << endl <<
		"Tiempo de ejecución: " << (float) (fin - inicio) / CLOCKS_PER_SEC << "ms"
		<< endl <<
		"Número de iteraciones: " << numIteraciones
		<< endl <<
		"La mejor solución obtenida es " << valorActual << endl;
	
	imprimir();

	delete DLB;

}





void Practica::greedy () {
	clock_t inicio, fin;
	
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

	// Inicio del reloj
	inicio = clock();

	// Almacena la media de flujos y distancias para cada
	// edificio/localizacion
	for (i = 0; i < n; i++) {
		
		posicionesFlujo[i] = i;
		posicionesDistancia[i] = i;
		mediaFlujoActual = 0;
		mediaDistanciaActual = 0;

		for (j = 0; j < n; j++) {
			mediaFlujoActual += matrices.flujo[i]->at(j);
			mediaDistanciaActual += matrices.distancia[i]->at(j);
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

	fin = clock();
	funcionObjetivo();

	cout << endl
		<< "Tiempo total: " << (float)(fin - inicio)/CLOCKS_PER_SEC << "ms" << endl
		 << "Valor: " << valorActual << endl;

	imprimir();

	delete mediaFlujo;
	delete mediaDistancia;
	delete posicionesFlujo;
	delete posicionesDistancia;
}

/* Componentes para la lista tabu ******************************************************************************/

bool has (const vector<CAMBIO>& v, const CAMBIO& c) {
	for (unsigned int i = 0; i < v.size(); i++) {
		if (v[i].primero == c.primero &&
			v[i].segundo == c.segundo ||
			v[i].segundo == c.primero &&
			v[i].primero == c.segundo) {
			return true;
		}
	}
	return false;
}

void Practica::tabu () {
	// Contadores de iteraciones y generaciones
	// de vecinos

#ifdef DEBUG
	int reinicializaciones = 0;
#endif

	unsigned int numIteraciones = 0;
	unsigned int iteracionesSinMejorar = 0;
	unsigned int vecinosGenerados = 0;
	clock_t inicio,fin;

	// Memoria para guardar la mejor
	// solución encontrada y el mejor vecino de la iteración

	CAMBIO cambiosMejorVecino;
	int valorMejorVecino;

	int* mejorSolucion = new int[n];
	int valorMejorSolucion = valorActual;

	// Flags para el proceso de búsqueda
	bool esTabuActivo;
	bool solucionMejorada;

	// Inicialización de las memorias de corto
	// y largo plazo

	vector<CAMBIO> vecinosAleatorios;
	vector<CAMBIO> memoriaCortoPlazo;
	unsigned int maxMemoriaCortoPlazo = n / 2;
	int** memoriaLargoPlazo = new int*[n];

	for (unsigned int i = 0; i < n; i++) {
		memoriaLargoPlazo[i] = new int[n];
		for (unsigned int j = 0; j < n; j++) {
			memoriaLargoPlazo[i][j] = 0;
		}
	}

	// Comienzo del algoritmo
	inicio = clock();

	while (++numIteraciones < 10000) {
		vecinosGenerados = 0;
		valorMejorVecino = 99999999;
		vecinosAleatorios.clear();

		// Generamos vecinos hasta llegar al límite
		do {
			solucionMejorada = false;

			// Evitamos generar varias veces el mismo vecino
			do {
				solucionVecina.segundo = rand() % n;
				solucionVecina.primero = rand() % n;
			} while (solucionVecina.primero == solucionVecina.segundo ||
					 has(vecinosAleatorios, solucionVecina));
			vecinosAleatorios.push_back(solucionVecina);
			factorizacion();

			// Comprobamos si el vecino generado es tabú activo
			esTabuActivo = false;
			for (unsigned int i = 0; i < memoriaCortoPlazo.size(); i++) {
				if ((memoriaCortoPlazo[i].primero == solucionVecina.primero &&
					memoriaCortoPlazo[i].segundo == solucionVecina.segundo) ||
					(memoriaCortoPlazo[i].primero == solucionVecina.segundo &&
					memoriaCortoPlazo[i].segundo == solucionVecina.primero)) {
					esTabuActivo = true;
				}
			}

			// Si el vecino generado nos sirve (criterio de aspiracion)
			if ((esTabuActivo && valorSiguiente < valorMejorSolucion) || (!esTabuActivo)) {
				// Lo guardamos si es el mejor vecino
				if (valorSiguiente < valorMejorVecino) {
					valorMejorVecino = valorSiguiente;
					cambiosMejorVecino.primero = solucionVecina.primero;
					cambiosMejorVecino.segundo = solucionVecina.segundo;
				}

				// Lo requeteguardamos si es la mejor solucion
				if (valorSiguiente < valorMejorSolucion) {
					valorMejorSolucion = valorSiguiente;
					for (unsigned int j = 0; j < n; j++) { mejorSolucion[j] = solucionActual[j]; }
					cambiarPosicion(mejorSolucion, solucionVecina.primero, solucionVecina.segundo);
					solucionMejorada = true;
				}
			}
		} while (++vecinosGenerados < 30);

		// Contamos las soluciones sin mejorar
		if (solucionMejorada) {
			iteracionesSinMejorar = 0;
		} else {
			iteracionesSinMejorar++;
		}

		// Actualizamos las memorias
		memoriaLargoPlazo[solucionVecina.primero][solucionVecina.segundo]++;
		memoriaLargoPlazo[solucionVecina.segundo][solucionVecina.primero]++;
		memoriaCortoPlazo.insert(memoriaCortoPlazo.begin(), solucionVecina);
		if (memoriaCortoPlazo.size() > maxMemoriaCortoPlazo) {
			memoriaCortoPlazo.pop_back();
		}

		// Aplicamos el mejor vecino encontrado
		aplicarVecindad();

		// Comprobamos si tenemos que reinicializar
		if (iteracionesSinMejorar >= 10) {
#ifdef DEBUG
			reinicializaciones++;
#endif
			iteracionesSinMejorar = 0;
			memoriaCortoPlazo.clear();

			// Nueva solucion actual
			int r = rand() % 100;
			// Solucion inicial aleatoria
			if (r < 25) {
				solucionInicial(semilla + numIteraciones);
				funcionObjetivo();
			// Mejor solucion obtenida
			} else if (r < 50) {
				for (unsigned int i = 0; i < n; i++) {
					solucionActual[i] = mejorSolucion[i];
					valorActual = valorMejorSolucion;
				}
#ifdef DEBUG
				imprimir();
				cout << endl << "Mejor: " << valorActual << endl;
#endif
				// Solucion a partir de memoria
			} else {
				// Decidimos si queremos diversificar o intensificar
				// cambiando el tamaño de la memoria a corto plazo...

				// Aplicamos el cambio menos frecuente

				int cambioI = 0;
				int cambioJ = 0;
				int cambioFrec = memoriaLargoPlazo[0][0];
				for (unsigned int i = 0; i < n; i++) {
					for (unsigned int j = i + 1; j < n; j++) {
						if (cambioFrec > memoriaLargoPlazo[i][j]) {
							cambioI = i;
							cambioJ = j;
							cambioFrec = memoriaLargoPlazo[i][j];
						}
					}
				}
				memoriaLargoPlazo[cambioI][cambioJ]++;
				memoriaLargoPlazo[cambioJ][cambioI]++;
				solucionVecina.primero = cambioI;
				solucionVecina.segundo = cambioJ;
				aplicarVecindad();
				
				// Decidimos si diversificar o intensificar aleatoriamente
#ifdef DEBUG
				imprimir();
				cout << endl << "Calcu: " << valorActual << endl;
#endif
				if ((rand() % 100) < 50) {
					maxMemoriaCortoPlazo += maxMemoriaCortoPlazo / 2;
				} else {
					maxMemoriaCortoPlazo -= maxMemoriaCortoPlazo / 2;
					if (maxMemoriaCortoPlazo < 2) { maxMemoriaCortoPlazo = 2; }
				}

				// Fue una decisión difícil
			}
		}
	}

	valorActual = valorMejorSolucion;
	for (unsigned int i = 0; i < n; i++) {
		solucionActual[i] = mejorSolucion[i];
		valorActual = valorMejorSolucion;
	}

#ifdef DEBUG
	cout << endl << "reinicializaciones " << reinicializaciones << endl;
#endif
	fin = clock();
	cout << endl << "Tiempo de ejecución: " << (float) (fin - inicio) / CLOCKS_PER_SEC << "ms"<< endl;
	cout  << "Mejor solucion encontrada: " << valorActual << endl;
	imprimir();

	delete mejorSolucion;
}
