#ifndef ALGORITMOQAP_H
#define ALGORITMOQAP_H

#include "QAP.h"
#include <vector>
using namespace std;

class AlgoritmoQAP {
public:
	void mostrarSolucionActual();
	virtual void iniciar () = 0;

protected:
	QAP qap;
	vector<int> solucionActual;
	int valorSolucionActual;
};

#endif
