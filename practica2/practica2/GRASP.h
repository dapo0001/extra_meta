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
	void seleccionarMejorSolucion (int* andidata, float valorCandidata);
	vector<CASILLA> etapa1();
	vector<CASILLA> etapa2();
	virtual ~GRASP();
private:
	void generarValoresComponentes();
	float** LC_valores;

	int semilla;
	QAP* qap;
	Practica* practica;
	int* solucionActual;
	float calcularCoste(vector<CASILLA> vector);
};

#endif /* GRASP_H */
