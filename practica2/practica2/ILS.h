#ifndef ILS_H
#define ILS_H

#include "QAP.h"
#include "Practica.h"

class ILS {
public:
	ILS (QAP& qap, int semilla);
private:
	int semilla;
	QAP* qap;
	Practica* practica;

	void clonarSolucion(int* destino, int* origen);
	void mutarSolucionActual (void* historia);
	void escogerSolucionActual(int* candidata, int valorCandidata, void* historia);
};

#endif /* ILS_H */
