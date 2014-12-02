#ifndef _POBLACION_H_
#define _POBLACION_H_

#include <vector>
using namespace std;

#include "Solucion.h"

class Poblacion {
public:
	Poblacion();
	Poblacion(
		unsigned int tamIndividuo,
		unsigned int tamPoblacion = 50,
		float probabilidadCruce = 0.7,
		float probabilidadMutacion = 0.01);

	static Poblacion* combinar(Poblacion* p1, Poblacion* p2);

	Poblacion* clonar();
	void cruzar();
	void mutar();
	Solucion* getMejorIndividuo() const { return mejorIndividuo; }

private:
	unsigned int tamIndividuo;

	float probabilidadCruce;
	unsigned int crucesEsperados;

	float probabilidadMutacion;
	unsigned int mutacionesEsperadas;

	Solucion* mejorIndividuo;
	vector<Solucion> individuos;
};

#endif
