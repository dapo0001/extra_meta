#include "ILS.h"

int* generarSolucionInicial () {
}

int* busquedaLocal (int* solucionInicial) {
}

int* modificar (int* solucionActual, void* historia) {
}

int* criterioAceptacion (int* solucionActual, int* solucionVecinaMejorada, void* historia) {
}

int* seleccionarMejorSolucion (int* solucionActual, int* mejorSolucion) {
}

ILS::ILS() {
	bool criterioDeParada;
	void* historia;

	int* solucionActual;
	int* solucionVecina;
	int* solucionVecinaMejorada;
	int* mejorSolucion;

	solucionActual = generarSolucionInicial();
	solucionActual = busquedaLocal(solucionActual);

	do {
		solucionVecina = modificar(solucionActual, historia);
		solucionVecinaMejorada = busquedaLocal(solucionVecina);
		solucionActual = criterioAceptacion(solucionActual, solucionVecinaMejorada, historia);
		mejorSolucion = seleccionarMejorSolucion(solucionActual, mejorSolucion);

	} while (criterioDeParada);
}
