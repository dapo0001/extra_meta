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
	while(true){
		Practica prac;
		prac.menuFichero();
		prac.menuAlgoritmo();
		system("PAUSE");
		system("cls");
	}
    return 0;
}
