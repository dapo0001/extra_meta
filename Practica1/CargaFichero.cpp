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


CargaFichero::CargaFichero(string nombreFich) {

    ifstream fich;
    fich.open(nombreFich.c_str(),ios::in);
    cout<<"Nombre introducido "<<nombreFich<<endl;
    if(fich){
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

