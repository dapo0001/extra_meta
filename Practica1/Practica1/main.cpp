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
	Practica prac;

	prac.menuFichero();
	prac.menuAlgoritmo();

	system("PAUSE");
    return 0;
}
