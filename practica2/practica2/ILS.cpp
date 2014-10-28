#include "ILS.h"

int* ILS::generarSolucionInicial () {
	return 0;
}

int* ILS::busquedaLocal (int* solucionInicial) {
	return 0;
}

int* ILS::modificar (int* solucionActual, void* historia) {
	return 0;
}

int* ILS::criterioAceptacion (int* solucionActual, int* solucionVecinaMejorada, void* historia) {
	return 0;
}

int* ILS::seleccionarMejorSolucion (int* solucionActual, int* mejorSolucion) {
	return 0;
}

ILS::ILS(QAP& qap) {
	bool criterioDeParada = false;
	void* historia = 0;

	int* solucionActual = 0;
	int* solucionVecina = 0;
	int* solucionVecinaMejorada = 0;
	int* mejorSolucion = 0;

	solucionActual = generarSolucionInicial();
	solucionActual = busquedaLocal(solucionActual);

	do {
		solucionVecina = modificar(solucionActual, historia);
		solucionVecinaMejorada = busquedaLocal(solucionVecina);
		solucionActual = criterioAceptacion(solucionActual, solucionVecinaMejorada, historia);
		mejorSolucion = seleccionarMejorSolucion(solucionActual, mejorSolucion);

	} while (criterioDeParada);
}
