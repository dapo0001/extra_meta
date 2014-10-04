/**
 * @file Practica.cpp
 * @authors: Pablo Molina González y Diego Alberto Pérez Ortega
 */

#include "Practica.h"
#include <math.h>
#include <iostream>
using namespace std;

Practica::Practica():
	valorMinimo(999999)
{}

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

/**
 *
 */
void Practica::funcionObjetivo(){
	int valor = 0;

	for(unsigned int i = 0; i < permutacion.size(); i++) {
		for(unsigned int j = 0; j < permutacion.size(); j++) {
			int flujo = matrices.matrizFlujo[i]->at(j);
			int distancia = matrices.matrizDistancia[i]->at(permutacion[i]);
			valor += flujo * distancia;
		}
	}
	cout << "valor minimo " << valor << endl;
	valorMinimo = valor;
}

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
    cout<<"21. salir"<<endl;
    do{
        cin>>val;
    }while (val < 1 || val > 21);
    
    cargarFich(val);
}

/**
 * Menú para seleccionar el algoritmo que se desea ejecutar
 */
void Practica::menuAlgoritmo(){
	int val = 0;
	cout<<endl;
	cout<<"Selecciona el algoritmo que deseas usar"<<endl;
	cout<<"1. Busqueda local"<<endl;
	cout<<"2. Busqueda tabu"<<endl;
    do{
        cin>>val;
    }while (val < 1 || val > 2);
    
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
            system("EXIT");
    }

	for(int i=0;i<matrices.getNumComp();i++){
		permutacion.push_back(i);
	}

}

/**
 *
 */
Practica::~Practica(){
}
