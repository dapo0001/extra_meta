/**
 * @file main.cpp
 * @authors: Pablo Molina Gonz�lez y Diego Alberto P�rez Ortega
 */


#include <cstdlib>
#include <iostream>
using namespace std;

#include "QAP.h"
#include "Practica.h"

int main(int argc, char** argv) {

	Practica prac;
	prac.menuFichero();
	prac.menuAlgoritmo();
	
	prac.funcionObjetivo();
	//prac.algoritmo();
	
	/*
    int val = menuFichero();
    QAP fichero;
	cargarFich(val,fichero);
	int algoritmo = menuAlgoritmo();
	Permutacion permuta(fichero.getNumComp());
	permuta.solInicial(semilla);

	*/
	//fichero.imprimirMatrizDistancia();
	system("PAUSE");
    return 0;
}
