/* 
 * File:   CargaFichero.cpp
 * Author: DiegoAlberto
 * 
 * Created on 1 de octubre de 2014, 17:34
 */

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
        int num;
        fich>>numComp;
        
        
        cout<<"abierto"<<endl;
    } else {
        cout<<"no encontrado"<<endl;
    }
    fich.close();
}

CargaFichero::CargaFichero(const CargaFichero& orig) {
}

CargaFichero::~CargaFichero() {
}

