#ifndef _ALGORITMO_GENETICO_GENERACIONAL_H_
#define _ALGORITMO_GENETICO_GENERACIONAL_H_

#include "Algoritmo.h"

class AlgoritmoGeneticoGeneracional: public Algoritmo {
	void ejecutar (QAP& qap, int semilla,int tipo);
};

#endif
