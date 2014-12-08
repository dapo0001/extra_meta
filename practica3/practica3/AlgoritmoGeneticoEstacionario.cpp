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

	while (generaciones++ < 20000) {
		//poblacionVecina = poblacionActual->clonar();
		poblacionActual->seleccioncrucemutacion();
		//poblacionVecina->seleccion();
		//poblacionVecina->cruzar();
		//poblacionVecina->cruzarPMX();
		//poblacionVecina->mutar();
		//nuevaPoblacion = poblacionActual->combinar(poblacionVecina);
		
		//cout<<"Generacion "<<generaciones<<endl;
		//poblacionActual = nuevaPoblacion->clonar();
	}
	valorSolucion = poblacionActual->getMejorIndividuo()->getValorSolucionActual();
	cout << valorSolucion << endl;
	this->finalizarTiempoEjecucion();

	delete poblacionActual;
}

