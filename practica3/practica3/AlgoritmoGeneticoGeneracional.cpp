#include "AlgoritmoGeneticoGeneracional.h"
#include <iostream>
using namespace std;

#include "Poblacion.h"
#include "Solucion.h"

#define DEBUG

void AlgoritmoGeneticoGeneracional::ejecutar (QAP& qap, int semilla,int tipo) {
	this->iniciarTiempoEjecucion();

	Poblacion* poblacionActual = 0;
	Poblacion* poblacionVecina = 0;

	poblacionActual = new Poblacion(&qap, qap.getNumComp());
	this->valorSolucionInicial = poblacionActual->getMejorIndividuo()->getValorSolucionActual();

	Solucion::llamadasAFuncionObjetivo = 0;
	while (Solucion::llamadasAFuncionObjetivo < 20000) {
		//poblacionVecina = poblacionActual;
		poblacionActual->seleccion();
		if(tipo == 0){
			poblacionActual->cruzar();
		}else{
			poblacionActual->cruzarPMX();
		}
		poblacionActual->mutar();
		//poblacionActual = poblacionVecina;
		//poblacionActual = poblacionActual->combinar(poblacionVecina);
		//delete poblacionVecina;
	}
	valorSolucion = poblacionActual->getMejorIndividuo()->getValorSolucionActual();
	
	this->finalizarTiempoEjecucion();
	this->mostrarResultados();

	delete poblacionActual;
}
