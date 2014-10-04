/**
 * @file QAP.cpp
 * @authors: Pablo Molina Gonzalez y Diego Alberto Pérez Ortega
 */


#include "QAP.h"
#include <fstream>
#include <iostream>
using namespace std;

/**
 *
 */
QAP::QAP(){    
}

/**
 *
 */
QAP::QAP(const QAP& orig) {
}

/**
 * Método que se encarga de leer el fichero y de asignar 
 * los valores a la matriz correspondiente
 */
void QAP::abrir(string nombreFich) {
    ifstream fich;
    fich.open(nombreFich.c_str(),ios::in);

    if (fich) {
		cout << "Fichero abierto correctamente" << endl;
        int num;
        fich >> numComp;

		// Matriz de flujo
		for(int i = 0; i < numComp; i++){
			vector<int> *vect = new vector<int>();
			for(int j = 0; j < numComp; j++){
				fich >> num;
				vect->push_back(num);
			}
			matrizFlujo.push_back(vect);
		}

		//Matriz de distancia
		for(int i = 0;i < numComp; i++){
			vector<int> *vect = new vector<int>();
			for(int j = 0; j < numComp; j++){
				fich >> num;
				vect->push_back(num);
			}
			matrizDistancia.push_back(vect);
		}
    } else {
        cout << "no se ha encontrado el archivo" << endl;
    }
    fich.close();
}

/**
 *
 */
void QAP::imprimirMatrizDistancia(){
	for(unsigned int i = 0; i < matrizDistancia.size(); i++){
		for(unsigned int j = 0; j < matrizDistancia[i]->size(); j++){
			cout << matrizDistancia[i]->at(j) << " ";
		}
		cout << endl;
	}
}

/**
 *
 */
QAP::~QAP() {
}
