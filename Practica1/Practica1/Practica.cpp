/**
 * @file Practica.cpp
 * @authors: Pablo Molina González y Diego Alberto Pérez Ortega
 */

#include "Practica.h"
#include <math.h>
#include <iostream>
using namespace std;

Practica::Practica():
	valorActual(999999),
	valorSiguiente(999999)
{}

Practica::~Practica()
{}


/* Métodos del proceso *********************************************************************/

/**
 * Cambia dos posiciones del vector
 * @pre Si las posiciones pasadas no son válidas dará error
 */
void Practica::cambiarPosicion (unsigned int pos1, unsigned int pos2) {
	int valor = permutacion[pos1];
	permutacion[pos1] = permutacion[pos2];
	permutacion[pos2] = valor;
}

/**
 * Se encarga de permutar valores de forma aleatoria según la semilla asignada
 * @pre La semilla debe ser un valor admisible por srand
 */
void Practica::solInicial (int semilla){
	srand(semilla);
	for(unsigned int i = 0; i < permutacion.size(); i++){
		unsigned int pos1 = rand()%permutacion.size();
		unsigned int pos2 = rand()%permutacion.size();
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
	int valor = 0,
		n = permutacion.size();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			valor +=
				matrices.matrizFlujo[permutacion[i]]->at(j) *
				matrices.matrizDistancia[i]->at(j);
		}
	}
	
	for (int k = 0; k < n; k++) {
		valor -=
			matrices.matrizFlujo[k]->at(k) *
			matrices.matrizDistancia[k]->at(k);
	}

	valorActual = valor;

	cout << "a: " << valorActual << endl;
}

/**
 * Añade un cambio al vector de cambios.
 * @param posicion Posición de la permutación que se quiere modificar.
 * @param valor Valor nuevo que se desea aplicar.
 */
void Practica::addCambio (unsigned int posicion, int valor) {
	cambios.push_back(new pair<unsigned int, int>(posicion, valor));
}

/**
 * Calcula el valor de la solución actual sin tener que recorrer todo el
 * contenido de las matrices. Para ello usa la solucion actual y el vector
 * de cambios en la permutacion.
 * @TODO Arreglar
 */
void Practica::factorizacion () {
	int n = permutacion.size(),
		flujo,
		distancia;
	valorSiguiente = valorActual;

	for (int i = 0; i < cambios.size(); i++) {
		for (int j = 0; j < n; j++) {
			flujo = matrices.matrizFlujo[permutacion[cambios[i]->first]]->at(j);
			distancia = matrices.matrizDistancia[cambios[i]->first]->at(j);
			valorSiguiente -= flujo * distancia;

			flujo = matrices.matrizFlujo[cambios[i]->second]->at(j);
			// La distancia se mantiene
			// distancia = matrices.matrizDistancia[cambios[i]->first]->at(j);
			valorSiguiente += flujo * distancia;
		}
	}

	cout << "s: " << valorSiguiente << endl;
}

/**
 * Aplica el vector de cambios a la solucion actual para llegar a un nuevo
 * vecino. Si el valor de 'valorSiguiente' es el mismo que 'valorActual'
 * calcula su nuevo valor mediante el método factorización, en caso contrario
 * se considera que ya está correctamente calculado.
 */
void Practica::aplicarVecindad () {
	factorizacion();

	for (unsigned int i = 0; i < cambios.size(); i++) {
		permutacion[cambios[i]->first] = cambios[i]->second;
		delete cambios[i];
	}

	cambios.clear();
	valorActual = valorSiguiente;
}

void Practica::algoritmo () {
	// 1. Escoge un vecino almacenando los cambios hechos en el vector de cambios.
	// 2. Comprueba su calidad con factorizacion() y valorSiguiente.
	// 3. Busca otro vecino si es necesario.
	// ...
	// 4. Aplica la vecindad con aplicarVecindad()

	funcionObjetivo();
	addCambio(0, 2);
	addCambio(1, 0);
	aplicarVecindad();
	funcionObjetivo();
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

	for(int i=0;i<matrices.getNumComp();i++){
		permutacion.push_back(i);
	}

}

/**
 * Imprime el vector permutación en la salida estándar
 */
void Practica::imprimir(){
	for(unsigned int i = 0; i < permutacion.size(); i++){
		cout << permutacion[i] << " ";
	}
	cout << endl;
}

/* Algoritmos *******************************************************************************/

void Practica::greedy () {
	int n = matrices.matrizDistancia.size();
	vector<int> mediaFlujo;
	vector<int> mediaDistancia;
	int mediaFlujoActual;
	int mediaDistanciaActual;

	for (int i = 0; i < n; i++) {
		mediaFlujoActual = 0;
		mediaDistancia = 0;
		for (int j = 0; j < n; j++) {
			mediaFlujoActual += matrices.matrizFlujo[i]->at(j);
			mediaDistanciaActual += matrices.matrizDistancia[i]->at(j);
		}
		mediaFlujoActual /= n;
		mediaDistanciaActual /= n;
		mediaFlujo.push_back(mediaFlujoActual);
		mediaDistancia.push_back(mediaDistanciaActual);
	}

	// TODO completar greedy
}
