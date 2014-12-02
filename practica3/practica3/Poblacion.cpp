#include "Poblacion.h"

Poblacion::Poblacion (QAP* _qap):
	qap(_qap),
	mejorIndividuo(0),
	tamIndividuo(0),
	probabilidadCruce(0),
	probabilidadMutacion(0),
	mutacionesEsperadas(0),
	crucesEsperados(0)
{};

Poblacion::Poblacion(
	QAP* _qap,
	unsigned int _tamIndividuo,
	unsigned int _tamPoblacion,
	float _probabilidadCruce,
	float _probabilidadMutacion):

	qap(_qap),
	mejorIndividuo(0),
	tamIndividuo(_tamIndividuo),
	probabilidadCruce(_probabilidadCruce),
	probabilidadMutacion(_probabilidadMutacion),
	mutacionesEsperadas(0),
	crucesEsperados(0)
{
	// TODO Calculamos la esperanza de cruce y la esperanza de mutacion

	// Generamos una poblacion aleatoria y buscamos el mejor individuo
	individuos.resize(_tamPoblacion);
	individuos[0].setQAP(qap);
	individuos[0].solucionInicial();
	mejorIndividuo = &(individuos[0]);
	for (unsigned int i = 1; i < _tamPoblacion; i++) {
		individuos[i].setQAP(qap);
		individuos[i].solucionInicial();

		if (mejorIndividuo->getValorSolucionActual() > individuos[i].getValorSolucionActual()) {
			mejorIndividuo = &(individuos[i]);
		}
	}
}

Poblacion* Poblacion::clonar () {
	// Clonamos la poblacion actual (soluciones incluidas)
	Poblacion* clon = new Poblacion(qap);
	clon->tamIndividuo = tamIndividuo;
	clon->probabilidadCruce = probabilidadCruce;
	clon->probabilidadMutacion = probabilidadMutacion;
	clon->crucesEsperados = crucesEsperados;
	clon->mutacionesEsperadas = mutacionesEsperadas;
	clon->individuos.resize(individuos.size());

	// Clonamos los individuos y nos quedamos con el mejor elemento
	clon->individuos[0].setQAP(qap);
	clon->individuos[0].setSolucionActual(individuos[0].getSolucionActual(), individuos[0].getValorSolucionActual());
	mejorIndividuo = &(clon->individuos[0]);
	for (unsigned int i = 1; i < individuos.size(); i++) {
		clon->individuos[i].setQAP(qap);
		clon->individuos[i].setSolucionActual(individuos[i].getSolucionActual(), individuos[i].getValorSolucionActual());
		if (clon->mejorIndividuo->getValorSolucionActual() > clon->individuos[i].getValorSolucionActual()) {
			clon->mejorIndividuo = &(clon->individuos[i]);
		}
	}

	return clon;
}

Poblacion* Poblacion::combinar (Poblacion* p1, Poblacion* p2) {
	// Combinamos dos poblaciones creando una tercera
	return p1->clonar();
}

void Poblacion::cruzar() {
	// Cruzamos individuos de la poblacion actual segun la esperanza de cruce
}

void Poblacion::mutar() {
	// Mutamos individuos de la poblacion actual segun la esperanza de mutacion
}
