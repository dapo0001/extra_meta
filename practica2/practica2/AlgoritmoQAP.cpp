#include "AlgoritmoQAP.h"
#include <iostream>
using namespace std;

AlgoritmoQAP::AlgoritmoQAP(void):
	valorSolucionActual(-1) {
}

void AlgoritmoQAP::mostrarSolucionActual () {
	cout << "Solución actual (" << valorSolucionActual << ")" << endl;
	for (unsigned int i = 0; i < solucionActual.size(); i++) {
		cout << solucionActual[i] << " ";
	}
	cout << endl;
}
