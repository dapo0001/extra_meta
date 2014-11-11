#ifndef ILS_H
#define ILS_H

#include "QAP.h"
#include "Practica.h"
#include "Algoritmo.h"

class ILS: public Algoritmo {
public:
	ILS ();
	void ejecutar(QAP& qap, int semilla);
	~ILS();

private:
	int semilla;
	QAP* qap;
	Practica* practica;

	int* solucion;
	void clonarSolucion(int* destino, int* origen);
	void mutarSolucionActual (void* historia);
	void escogerSolucionActual(int* candidata, int valorCandidata, void* historia);
};

#endif /* ILS_H */
