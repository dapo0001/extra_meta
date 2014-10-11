/**
 * @file Practica.cpp
 * @authors: Pablo Molina González y Diego Alberto Pérez Ortega
 */

#include "Practica.h"
#include <math.h>
#include <iostream>
#include <ctime>
using namespace std;

Practica::Practica():
	valorActual(999999),
	valorSiguiente(999999)
{
	cout << "Introduzca la semilla ";
	cin >> semilla;
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
void Practica::cambiarPosicion (unsigned int pos1, unsigned int pos2) {
	int valor = solucionActual[pos1];
	solucionActual[pos1] = solucionActual[pos2];
	solucionActual[pos2] = valor;
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
		cambiarPosicion(pos1, pos2);
	}

	cambiarPosicion(0, 2);
	cambiarPosicion(0, 1);

	imprimir();
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
	
	for (unsigned int k = 0; k < n; k++) {
		valorActual -=
			matrices.flujo[k]->at(k) *
			matrices.distancia[k]->at(k);
	}
}

/**
 * Calcula el valor de la solución actual sin tener que recorrer todo el
 * contenido de las matrices. Para ello usa la solucion actual y el vector
 * de cambios en la solucionActual.
 */
void Practica::factorizacion () {
	valorSiguiente = valorActual;

	for (unsigned int i = 0; i < n; i++) {
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
		cambiarPosicion(solucionVecina.primero, solucionVecina.segundo);
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


void Practica::busquedaLocal(){
	clock_t inicio,fin;
	int numIteraciones = 0;
	unsigned int val1 = 0;
	unsigned int val2 = 1;
	bool* DLB = new bool[n];

	for (unsigned int i = 0; i < n; i++) {
		DLB[i] = false;
	}

	inicio = clock();
	
	funcionObjetivo();
	
	while (val1 != n && val2 < n && numIteraciones < 10000) {
		if (DLB[val1] == false) {
			solucionVecina.primero = val1;
			solucionVecina.segundo = val2;
			factorizacion();
		
			if (valorSiguiente < valorActual) {
				cout << "Se mejora la solucion" << endl;
				cout << "Valor Actual " << valorActual << endl;
				cout << "Valor Siguiente " << valorSiguiente << endl;
				aplicarVecindad();
				imprimir();
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


/* Interfaz de la práctica *********************************************************************/

/**
 * Menú para la lectura de ficheros
 */
void Practica::menuFichero(){
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
	cout<<"21. _try"<<endl;
    cout<<"22. salir"<<endl;
    
	do {
        cin >> val;
    } while (val < 0 || val > 22);
    cargarFich(val);
}

/**
 * Menú para seleccionar el algoritmo que se desea ejecutar
 */
void Practica::menuAlgoritmo(){
	int val = 0;
	cout<<endl;
	cout<<"Selecciona el algoritmo que deseas usar"<<endl;
	cout << "1. Busqueda local" << endl;
	cout << "2. Busqueda tabu" << endl;
	cout << "3. Algoritmo Greedy" << endl;
    
	do {
        cin>>val;
    } while (val < 1 || val > 3);
	algoritmo(val);
  //  return val;
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
		case 21:
			matrices.abrir("ficheros/_try.dat");
        case 22:
            system("EXIT");
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
		 << "Tiempo total: " << (float)(fin - inicio) << "ms" << endl
		 << "Valor: " << valorActual << endl;

	imprimir();

	delete mediaFlujo;
	delete mediaDistancia;
	delete posicionesFlujo;
	delete posicionesDistancia;
}

void Practica::tabu () {
}
