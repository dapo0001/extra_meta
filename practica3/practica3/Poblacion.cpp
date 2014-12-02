#include "Poblacion.h"

Poblacion::Poblacion ():
	mejorIndividuo(0),
	tamIndividuo(0),
	probabilidadCruce(0),
	probabilidadMutacion(0),
	mutacionesEsperadas(0),
	crucesEsperados(0)
{};

Poblacion::Poblacion(
	unsigned int _tamIndividuo,
	unsigned int _tamPoblacion = 50,
	float _probabilidadCruce = 0.7,
	float _probabilidadMutacion = 0.01):

	mejorIndividuo(0),
	tamIndividuo(_tamIndividuo),
	probabilidadCruce(_probabilidadCruce),
	probabilidadMutacion(_probabilidadMutacion),
	mutacionesEsperadas(0),
	crucesEsperados(0)
{
	// Calculamos la esperanza de cruce y la esperanza de mutacion
	// TODO

	// Generamos una poblacion aleatoria y buscamos el mejor individuo
	individuos.resize(_tamPoblacion);
	// TODO
}

Poblacion* Poblacion::clonar () {
	// Clonamos la poblacion actual (soluciones incluidas)
	Poblacion* clon = new Poblacion();
	clon->tamIndividuo = tamIndividuo;
	clon->probabilidadCruce = probabilidadCruce;
	clon->probabilidadMutacion = probabilidadMutacion;
	clon->crucesEsperados = crucesEsperados;
	clon->mutacionesEsperadas = mutacionesEsperadas;
	clon->individuos.resize(individuos.size());

	for (unsigned int i = 0; i < individuos.size(); i++) {
		clon->individuos[i] = individuos[i];
	}

	// TODO buscar mejor individuo en el clon
}

Poblacion* Poblacion::combinar (Poblacion* p1, Poblacion* p2) {
	// Combinamos dos poblaciones creando una tercera
}

void Poblacion::cruzar() {
	// Cruzamos individuos de la poblacion actual segun la esperanza de cruce
}

void Poblacion::mutar() {
	// Mutamos individuos de la poblacion actual segun la esperanza de mutacion
}
