/* 
 * File:   main.cpp
 * Author: DiegoAlberto
 *
 * Created on 1 de octubre de 2014, 17:23
 */

#include <cstdlib>
#include <iostream>
#include "CargaFichero.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string nombre;
    cout<<"Introduce el nombre del archivo"<<endl;
    cin>>nombre;
    CargaFichero fich(nombre);
    return 0;
}

