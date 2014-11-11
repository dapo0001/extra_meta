#ifndef _ALGORITMO_H_
#define _ALGORITMO_H_

#include "QAP.h"

class Algoritmo {
public:
	virtual void ejecutar (QAP& qap, int semilla) = 0;
	int getValorSolucion () const { return valorSolucion; }
	float getTiempoEjecucion () const { return tiempoEjecucion; }
protected:
	int valorSolucion;
	float tiempoEjecucion;
};

#endif
