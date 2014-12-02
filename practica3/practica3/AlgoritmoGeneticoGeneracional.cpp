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

	poblacionActual = new Poblacion(&qap, qap.getNumComp());
	cout << poblacionActual->getMejorIndividuo()->getValorSolucionActual() << endl;

	while (generaciones++ < 1000) {
		poblacionVecina = poblacionActual->clonar();
		poblacionVecina->seleccion();
		poblacionVecina->cruzar();
		poblacionVecina->mutar();
		nuevaPoblacion = poblacionActual->combinar(poblacionVecina);
		
		delete poblacionActual;
		delete poblacionVecina;
		poblacionActual = nuevaPoblacion;
	}

	valorSolucion = poblacionActual->getMejorIndividuo()->getValorSolucionActual();
	cout << valorSolucion << endl;
	this->finalizarTiempoEjecucion();

	delete poblacionActual;
}
