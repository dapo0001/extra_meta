#include "AlgoritmoGeneticoGeneracional.h"
#include <iostream>
using namespace std;

#define DEBUG

void AlgoritmoGeneticoGeneracional::ejecutar (QAP& qap, int semilla) {
	this->iniciarTiempoEjecucion();
	this->finalizarTiempoEjecucion();
	valorSolucion = 10;
}
