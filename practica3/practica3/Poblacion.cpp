#include "Poblacion.h"
#include <iostream>
using namespace std;

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
	// Calculamos la esperanza de cruce y la esperanza de mutacion
	crucesEsperados = _probabilidadCruce * (_tamPoblacion / 2);
	mutacionesEsperadas = _probabilidadMutacion * _tamPoblacion * _tamIndividuo;

	// Generamos una poblacion aleatoria y buscamos el mejor individuo
	individuos.resize(_tamPoblacion);
	individuos[0] = new Solucion();
	individuos[0]->setQAP(qap);
	individuos[0]->solucionInicial();
	individuos[0]->getSolucionActual();
	mejorIndividuo = individuos[0];
	for (unsigned int i = 1; i < _tamPoblacion; i++) {
		individuos[i] = new Solucion();
		individuos[i]->setQAP(qap);
		individuos[i]->solucionInicial();
		if (mejorIndividuo->getValorSolucionActual() > individuos[i]->getValorSolucionActual()) {			
			mejorIndividuo = individuos[i];
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
	clon->individuos[0] = new Solucion();
	clon->individuos[0]->setQAP(qap);
	clon->individuos[0]->setSolucionActual(individuos[0]->getSolucionActual(), individuos[0]->getValorSolucionActual());
	clon->mejorIndividuo = clon->individuos[0];
	for (unsigned int i = 1; i < individuos.size(); i++) {
		clon->individuos[i] = new Solucion();
		clon->individuos[i]->setQAP(qap);		
		clon->individuos[i]->setSolucionActual(individuos[i]->getSolucionActual(), individuos[i]->getValorSolucionActual());
		
		if (clon->mejorIndividuo->getValorSolucionActual() > clon->individuos[i]->getValorSolucionActual()) {
			clon->mejorIndividuo = clon->individuos[i];
		}
		
	}
	return clon;
}

void Poblacion::seleccion(){
	for(unsigned int i=0;i<individuos.size();i++){
		vector<Solucion*>::iterator it = individuos.begin();
		if(individuos[i]->getValorSolucionActual() > individuos[i+1]->getValorSolucionActual()){			
			it+=i+1;	
			delete individuos[i+1];
		}else{
			it+=i;
			delete individuos[i];
		}		
		individuos.erase(it);
	}
}

Poblacion* Poblacion::combinar (Poblacion* p1) {
	// Combinamos dos poblaciones creando una tercera
	Poblacion* nuevaPoblacion = this->clonar();

	for(unsigned int i=0;i<p1->individuos.size();i++){
		Solucion* nuevaSolucion = new Solucion();
		nuevaSolucion->setQAP(qap);
		nuevaSolucion->setSolucionActual(individuos[i]->getSolucionActual(),individuos[i]->getValorSolucionActual());
		nuevaPoblacion->individuos.push_back(nuevaSolucion);
		if(mejorIndividuo->getValorSolucionActual() > nuevaSolucion->getValorSolucionActual()){
			mejorIndividuo = nuevaSolucion;
		}
	}

	while(nuevaPoblacion->individuos.size() > 50){
		int numAl1 = rand() % nuevaPoblacion->individuos.size();
		int numAl2 = rand() % nuevaPoblacion->individuos.size();
		vector<Solucion*>::iterator it = nuevaPoblacion->individuos.begin();
		if(nuevaPoblacion->individuos[numAl1]->getValorSolucionActual() < nuevaPoblacion->individuos[numAl2]->getValorSolucionActual()){			
			it+=numAl2;	
			if (nuevaPoblacion->individuos[numAl2] == nuevaPoblacion->mejorIndividuo) {
				nuevaPoblacion->mejorIndividuo = nuevaPoblacion->individuos[numAl1];
			}
			delete nuevaPoblacion->individuos[numAl2];
		}else{
			it+=numAl1;
			if (nuevaPoblacion->individuos[numAl1] == nuevaPoblacion->mejorIndividuo) {
				nuevaPoblacion->mejorIndividuo = nuevaPoblacion->individuos[numAl2];
			}
			delete nuevaPoblacion->individuos[numAl1];
		}
		nuevaPoblacion->individuos.erase(it);
	}


	return nuevaPoblacion;
}

void Poblacion::cruzar() {
	// Cruzamos individuos de la poblacion actual segun la esperanza de cruce
	for (unsigned int i=0;i<crucesEsperados;i++){
		Solucion* hijo = individuos[i]->cruzarPosicion(individuos[rand()%individuos.size()]);
		individuos.push_back(hijo);
	}
}

void Poblacion::mutar() {
	// Mutamos individuos de la poblacion actual segun la esperanza de mutacion
	for (unsigned int i = 0; i < mutacionesEsperadas; i++) {
		Solucion* individuoMutado = individuos[rand() % individuos.size()];
		individuoMutado->cambiarPosicion(individuoMutado->getSolucionActual(), rand() % tamIndividuo, rand() % tamIndividuo);
	}
}

Poblacion::~Poblacion(){

	for(int i=0;i<individuos.size();i++){
		delete individuos[i];
	}

}