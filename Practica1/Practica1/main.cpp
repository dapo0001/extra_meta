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

	system("PAUSE");
    return 0;
}
