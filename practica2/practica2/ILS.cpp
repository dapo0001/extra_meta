#include "ILS.h"

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

ILS::ILS(QAP& qap, int semilla):
	semilla(semilla),
	qap(&qap),
	practica(new Practica())
{
	bool criterioDeParada = false;
	void* historia = 0;
	int* solucionActual = 0;
	int valorSolucionActual = 0;
	int* solucionVecina = 0;
	int valorSolucionVecina = 0;
	int* solucionVecinaMejorada = 0;
	int valorSolucionVecinaMejorada = 0;
	int* mejorSolucion = 0;
	int valorMejoraSolucion = 0;

	// Generamos una solución incial aleatoria
	// y le aplicamos la busqueda local
	practica->solucionInicial();
	practica->busquedaLocal();
	solucionActual = practica->getSolucionActual();
	valorSolucionActual = practica->getValorSolucionActual();

	do {
		// Generamos una solucion vecina con el historial
		solucionVecina = modificar(solucionActual, historia);

		solucionVecinaMejorada = busquedaLocal(solucionVecina);
		solucionActual = criterioAceptacion(solucionActual, solucionVecinaMejorada, historia);
		mejorSolucion = seleccionarMejorSolucion(solucionActual, mejorSolucion);
	} while (criterioDeParada);

	delete solucionActual;
	delete solucionVecina;
	delete solucionVecinaMejorada;
	delete mejorSolucion;
}
