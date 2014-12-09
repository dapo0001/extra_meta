#include "AlgoritmoGeneticoGeneracional.h"
#include <iostream>
using namespace std;

#include "Poblacion.h"
#include "Solucion.h"

#define DEBUG

void AlgoritmoGeneticoGeneracional::ejecutar (QAP& qap, int semilla) {
	this->iniciarTiempoEjecucion();

	Poblacion* poblacionActual = 0;
	Poblacion* poblacionVecina = 0;
	//Poblacion* nuevaPoblacion = 0;

	poblacionActual = new Poblacion(&qap, qap.getNumComp());
	this->valorSolucionInicial = poblacionActual->getMejorIndividuo()->getValorSolucionActual();

	Solucion::llamadasAFuncionObjetivo = 0;
	while (Solucion::llamadasAFuncionObjetivo < 20000) {
		poblacionVecina = poblacionActual->clonar();
		poblacionVecina->seleccion();
		//poblacionVecina->cruzar();
		poblacionVecina->cruzarPMX();
		poblacionVecina->mutar();
		poblacionActual = poblacionActual->combinar(poblacionVecina);
		//poblacionActual = nuevaPoblacion->clonar();
	}
	valorSolucion = poblacionActual->getMejorIndividuo()->getValorSolucionActual();
	
	this->finalizarTiempoEjecucion();
	this->mostrarResultados();

	delete poblacionActual;
}
