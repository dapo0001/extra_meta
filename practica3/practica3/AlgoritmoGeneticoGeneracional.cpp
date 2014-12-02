#include "AlgoritmoGeneticoGeneracional.h"
#include <iostream>
using namespace std;

#include "Poblacion.h"

#define DEBUG

void AlgoritmoGeneticoGeneracional::ejecutar (QAP& qap, int semilla) {
	this->iniciarTiempoEjecucion();
	int generaciones = 0;

	Poblacion* poblacionActual = 0;
	Poblacion* poblacionVecina = 0;
	Poblacion* nuevaPoblacion = 0;

	poblacionActual = new Poblacion(qap.getNumComp());

	while (generaciones++ < 25) {
		poblacionVecina = poblacionActual->clonar();
		poblacionVecina->cruzar();
		poblacionVecina->mutar();
		nuevaPoblacion = Poblacion::combinar(poblacionActual, poblacionVecina);
		
		delete poblacionActual;
		delete poblacionVecina;
		poblacionActual = nuevaPoblacion;
	}

	valorSolucion = poblacionActual->getMejorIndividuo()->getValor();
	this->finalizarTiempoEjecucion();
}
