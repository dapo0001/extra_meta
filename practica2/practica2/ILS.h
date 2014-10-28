#ifndef ILS_H
#define ILS_H

#include "QAP.h"

class ILS {
public:
	ILS (QAP& qap);
private:
	int* generarSolucionInicial();
	int* busquedaLocal (int* solucionInicial);
	int* modificar (int* solucionActual, void* historia);
	int* criterioAceptacion (int* solucionActual, int* solucionVecinaMejorada, void* historia);
	int* seleccionarMejorSolucion (int* solucionActual, int* mejorSolucion);
};

#endif /* ILS_H */
