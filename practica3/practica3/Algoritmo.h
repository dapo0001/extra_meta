#ifndef _ALGORITMO_H_
#define _ALGORITMO_H_

#include "QAP.h"
#include <ctime>

class Algoritmo {
public:
	virtual void ejecutar (QAP& qap, int semilla) = 0;

	int getValorSolucion () const { return valorSolucion; }
	float getTiempoEjecucion () const { return tiempoEjecucion; }

protected:
	void iniciarTiempoEjecucion () { inicio = clock(); }
	void finalizarTiempoEjecucion () { fin = clock(); tiempoEjecucion = (float)(fin - inicio) / CLOCKS_PER_SEC; }

	int valorSolucion;
	float tiempoEjecucion;

private:
	clock_t inicio;
	clock_t fin;
};

#endif
