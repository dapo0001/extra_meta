
#include "CargaFichero.h"
#include <fstream>
#include <iostream>
using namespace std;

CargaFichero::CargaFichero(){
    
}
void CargaFichero::abrir(string nombreFich) {

    ifstream fich;
    fich.open(nombreFich.c_str(),ios::in);
    if(fich){
		cout<<"Fichero abierto correctamente"<<endl;
        int num;
        fich>>numComp;
		for(int i = 0;i<numComp;i++){
			vector<int> *vect = new vector<int>();
			for(int j=0;j<numComp;j++){
				fich>>num;
				vect->push_back(num);
			}
			matrizFlujo.push_back(vect);
			cout<<"tamaño de matrizFlujo "<<matrizFlujo.size()<<endl;
		}
		for(int i=0;i<numComp;i++){
			vector<int> *vect = new vector<int>();
			for(int j =0;j<numComp;j++){
				fich>>num;
				vect->push_back(num);
			}
			matrizDistancia.push_back(vect);
		}
    } else {
        cout<<"no se ha encontrado el archivo"<<endl;
    }
    fich.close();
}

CargaFichero::CargaFichero(const CargaFichero& orig) {
}


void CargaFichero::imprimirMatrizDistancia(){
	for(int i=0;i<matrizDistancia.size();i++){
		for(int j=0;j<matrizDistancia[i]->size();j++){
			cout<<matrizDistancia[i]->at(j)<<" ";
		}
		cout<<endl;
	}
}



CargaFichero::~CargaFichero() {
}
