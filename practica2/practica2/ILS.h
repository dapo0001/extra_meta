#ifndef ILS_H
#define ILS_H

#include "QAP.h"
#include "Practica.h"

class ILS {
public:
	ILS (QAP& qap, int semilla);
	~ILS();

	int* getSolucion() const { return solucion; }
	float getTiempoEjecucion() const { return tiempoEjecucion; }
	int getValorSolucion() const { return valorSolucion; }

private:
	int semilla;
	QAP* qap;
	Practica* practica;

	int* solucion;
	float tiempoEjecucion;
	long int valorSolucion;

	void clonarSolucion(int* destino, int* origen);
	void mutarSolucionActual (void* historia);
	void escogerSolucionActual(int* candidata, int valorCandidata, void* historia);
};

#endif /* ILS_H */
