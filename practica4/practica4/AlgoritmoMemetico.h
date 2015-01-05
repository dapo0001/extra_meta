#ifndef _ALGORITMO_MEMETICO_H_
#define _ALGORITMO_MEMETICO_H_

#include "Algoritmo.h"

class AlgoritmoMemetico: public Algoritmo {
public:
	void ejecutar (QAP& qap, int semilla,int tipo);
	void setHibridacion (int hibridacion);

private:
	int hibridacion;
};

#endif
