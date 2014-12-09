#include "AlgoritmoGeneticoEstacionario.h"
#include <iostream>
using namespace std;

#include "Poblacion.h"

#define DEBUG

void AlgoritmoGeneticoEstacionario::ejecutar (QAP& qap, int semilla) {
	this->iniciarTiempoEjecucion();
	int generaciones = 0;

	Poblacion* poblacionActual = 0;
	Poblacion* poblacionVecina = 0;
	Poblacion* nuevaPoblacion = 0;

	poblacionActual = new Poblacion(&qap, qap.getNumComp());
	cout << poblacionActual->getMejorIndividuo()->getValorSolucionActual() << endl;
	Solucion::llamadasAFuncionObjetivo = 0;
	while (Solucion::llamadasAFuncionObjetivo < 20000) {
		//poblacionActual->seleccioncrucemutacion();
		poblacionActual->seleccioncrucePMXmutacion();
	}
	valorSolucion = poblacionActual->getMejorIndividuo()->getValorSolucionActual();
	cout << valorSolucion << endl;
	this->finalizarTiempoEjecucion();

	delete poblacionActual;
}

