/*
@authors: Pablo Molina Gonzalez y Diego Alberto Pérez Ortega
*/


#include <cstdlib>
#include <iostream>
#include "QAP.h"
#include "Practica.h"

using namespace std;

/*
 * 
 */





int main(int argc, char** argv) {
	int semilla = 0;
	cout<<"Introduzca la semilla ";
	cin>>semilla;

	Practica prac;
	prac.menuFichero();
	prac.menuAlgoritmo();
	prac.solInicial(semilla);
	prac.funcionObjetivo();
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
