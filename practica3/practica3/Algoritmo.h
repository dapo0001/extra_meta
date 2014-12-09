#ifndef _ALGORITMO_H_
#define _ALGORITMO_H_

#include "QAP.h"
#include <ctime>
#include <iostream>
using namespace std;

class Algoritmo {
public:
	virtual void ejecutar (QAP& qap, int semilla) = 0;

	int getValorSolucion () const { return valorSolucion; }
	float getTiempoEjecucion () const { return tiempoEjecucion; }
	void mostrarResultados () {
		cout << "Solución inicial:\t" << valorSolucionInicial << endl
			 << "Solución final:\t\t" << valorSolucion << endl
			 << "Tiempo ejecución:\t" << tiempoEjecucion << "s" << endl;
	}

protected:
	void iniciarTiempoEjecucion () { inicio = clock(); }
	void finalizarTiempoEjecucion () {
		fin = clock();
		tiempoEjecucion = ((float)(fin - inicio)) / CLOCKS_PER_SEC; }

	int valorSolucionInicial;
	int valorSolucion;
	float tiempoEjecucion;

private:
	clock_t inicio;
	clock_t fin;
};

#endif
