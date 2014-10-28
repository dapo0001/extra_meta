#ifndef GRASP_H
#define GRASP_H

#include "QAP.h"

class GRASP {
public:
	GRASP (QAP& qap,int semilla);
	int* GRASP::generarSolucionGreedyAleatorizada ();
	int* GRASP::busquedaLocal (int* solucionInicial);
	int* GRASP::seleccionarMejorSolucion (int* solucion1, int* solucion2);

};

#endif /* GRASP_H */
