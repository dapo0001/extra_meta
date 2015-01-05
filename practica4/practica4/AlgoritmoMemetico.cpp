#include "AlgoritmoMemetico.h"
#include <iostream>
using namespace std;

#include "Poblacion.h"
#include "Solucion.h"

#define DEBUG

void AlgoritmoMemetico::ejecutar (QAP& qap, int semilla,int tipo) {
	this->iniciarTiempoEjecucion();

	int generacion = 0;
	Solucion::llamadasAFuncionObjetivo = 0;
	Poblacion* poblacionActual = 0;
	Poblacion* poblacionVecina = 0;
	poblacionActual = new Poblacion(&qap, qap.getNumComp());
	this->valorSolucionInicial = poblacionActual->getMejorIndividuo()->getValorSolucionActual();

	while (Solucion::llamadasAFuncionObjetivo < 20000) {
		generacion++;

		if (generacion % 10 == 0) {
			poblacionActual->busquedaLocal(
				(hibridacion == 0) ? 1.0 : 0.1,
				(hibridacion == 2)
			);
		}

		poblacionActual->seleccion();
		if(tipo == 0) {
			poblacionActual->cruzar();
		} else {
			poblacionActual->cruzarPMX();
		}

		poblacionActual->mutar();
	}
	valorSolucion = poblacionActual->getMejorIndividuo()->getValorSolucionActual();
	
	this->finalizarTiempoEjecucion();
	this->mostrarResultados();
	delete poblacionActual;
}

void AlgoritmoMemetico::setHibridacion (int hibridacion) {
	this->hibridacion = hibridacion;
}
