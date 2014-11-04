#ifndef GRASP_H
#define GRASP_H

#include "QAP.h"
#include "Practica.h"
#include <vector>

typedef struct {
	int i;
	int j;
} CASILLA;


class GRASP {
public:
	GRASP (QAP& qap, int semilla);
	int* generarSolucionGreedyAleatorizada ();
	int* seleccionarMejorSolucion (int* solucion1, int* solucion2);
	vector<CASILLA> etapa1();
	int* etapa2();
private:
	int semilla;
	QAP* qap;
	Practica* practica;
	int valorActual;
};

#endif /* GRASP_H */
