#include "AlgoritmoGeneticoEstacionario.h"
#include <iostream>
using namespace std;

#include "Poblacion.h"

#define DEBUG

void AlgoritmoGeneticoEstacionario::ejecutar (QAP& qap, int semilla,int tipo) {
	this->iniciarTiempoEjecucion();
	int generaciones = 0;

	Poblacion* poblacionActual = 0;
	Poblacion* poblacionVecina = 0;
	Poblacion* nuevaPoblacion = 0;

	poblacionActual = new Poblacion(&qap, qap.getNumComp(),50,1);
	this->valorSolucionInicial = poblacionActual->getMejorIndividuo()->getValorSolucionActual();
	Solucion::llamadasAFuncionObjetivo = 0;
	while (Solucion::llamadasAFuncionObjetivo < 20000) {
		if(tipo == 0){
			poblacionActual->seleccioncrucemutacion();
		}else{
			poblacionActual->seleccioncrucePMXmutacion();
		}
		poblacionActual->seleccioncrucemutacion();
		//poblacionActual->seleccioncrucePMXmutacion();
	}
	valorSolucion = poblacionActual->getMejorIndividuo()->getValorSolucionActual();
	this->finalizarTiempoEjecucion();
	this->mostrarResultados();

	delete poblacionActual;
}

