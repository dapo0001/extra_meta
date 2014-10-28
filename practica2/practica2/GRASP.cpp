#include "GRASP.h"

int* generarSolucionGreedyAleatorizada () {
}

int* busquedaLocal (int* solucionInicial) {
}

int* seleccionarMejorSolucion (int* solucion1, int* solucion2) {
}

GRASP::GRASP() {
	bool criterioParada;
	int* solucionActual;
	int* mejorSolucionVecina;
	int* mejorSolucion;

	while (criterioParada) {
		solucionActual = generarSolucionGreedyAleatorizada();
		mejorSolucionVecina = busquedaLocal(solucionActual);
		mejorSolucion = seleccionarMejorSolucion(mejorSolucionVecina, mejorSolucion);
	}
}
