#ifndef GRASP_H
#define GRASP_H

#include "QAP.h"
#include "Practica.h"

class GRASP {
public:
	GRASP (QAP& qap, int semilla);
	int* GRASP::generarSolucionGreedyAleatorizada ();
	int* GRASP::seleccionarMejorSolucion (int* solucion1, int* solucion2);
private:
	int semilla;
	QAP* qap;
	Practica* practica;
};

#endif /* GRASP_H */
