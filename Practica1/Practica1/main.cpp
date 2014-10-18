/**
 * @file main.cpp
 * @authors: Pablo Molina González y Diego Alberto Pérez Ortega
 */


#include <cstdlib>
#include <iostream>
using namespace std;

#include "QAP.h"
#include "Practica.h"

int main(int argc, char** argv) {
	while(true){
		Practica prac;
		prac.menuFichero();
		prac.menuAlgoritmo();
		system("PAUSE");
		system("cls");
	}
    return 0;
}
