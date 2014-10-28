#include "GRASP.h"

int* GRASP::generarSolucionGreedyAleatorizada () {
	return 0;
}

int* GRASP::busquedaLocal (int* solucionInicial) {
	return 0;
}

int* GRASP::seleccionarMejorSolucion (int* solucion1, int* solucion2) {
	return 0;
}

GRASP::GRASP(QAP& qap, int semilla) {
	bool criterioParada = false;
	int* solucionActual = 0;
	int* mejorSolucionVecina = 0;
	int* mejorSolucion = 0;

	while (criterioParada) {
		solucionActual = generarSolucionGreedyAleatorizada();
		mejorSolucionVecina = busquedaLocal(solucionActual);
		mejorSolucion = seleccionarMejorSolucion(mejorSolucionVecina, mejorSolucion);
	}
}
