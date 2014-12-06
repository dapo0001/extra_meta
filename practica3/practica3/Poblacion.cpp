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
	for(unsigned int i=0;i<individuos.size();i+=2){
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
		nuevaSolucion->setSolucionActual(p1->individuos[i]->getSolucionActual(),p1->individuos[i]->getValorSolucionActual());
		nuevaPoblacion->individuos.push_back(nuevaSolucion);
		
		//cout<<"Mejor ind "<<mejorIndividuo->getValorSolucionActual()<<" nueva sol "<<nuevaSolucion->getValorSolucionActual()<<endl;
		if(mejorIndividuo->getValorSolucionActual() > nuevaSolucion->getValorSolucionActual()){
			mejorIndividuo = nuevaSolucion;
		}		
	}

	//Se eliminan individuos aleatoriamente enfrentandolos entre sí
	while(nuevaPoblacion->individuos.size() > 50){
		int numAl1 = rand() % nuevaPoblacion->individuos.size();
		int numAl2 = rand() % nuevaPoblacion->individuos.size();
		vector<Solucion*>::iterator it = nuevaPoblacion->individuos.begin();
		if(nuevaPoblacion->individuos[numAl1]->getValorSolucionActual() < nuevaPoblacion->individuos[numAl2]->getValorSolucionActual()){			
			it+=numAl2;	
			delete nuevaPoblacion->individuos[numAl2];
		}else{
			it+=numAl1;
			delete nuevaPoblacion->individuos[numAl1];
		}
		nuevaPoblacion->individuos.erase(it);
	}

	//Se busca el mejor individuo de nuevo por si se ha perdido en el anterior proceso
	nuevaPoblacion->mejorIndividuo = nuevaPoblacion->individuos[0];
	for(unsigned int i=1;i<nuevaPoblacion->individuos.size();i++){
		if(nuevaPoblacion->mejorIndividuo->getValorSolucionActual() > nuevaPoblacion->individuos[i]->getValorSolucionActual()){
			nuevaPoblacion->mejorIndividuo = nuevaPoblacion->individuos[i];
		}	
	}	

	return nuevaPoblacion;
}

void Poblacion::cruzar() {
	// Cruzamos individuos de la poblacion actual segun la esperanza de cruce
	for (unsigned int i=0;i<crucesEsperados;i++){
		int alea = rand()%individuos.size();
		Solucion* hijo = individuos[i]->cruzarPosicion(individuos[alea]);
		individuos.push_back(hijo);
	}
}



void Poblacion::cruzarPMX(){
	//Cruzamos los 2 padres y generamos 2 hijos
	int numIndividuos = individuos.size(); //El número de padres, ya que el vector se va incrementadon y puede ser que el hijo sea padre

	for(unsigned int i=0;i<crucesEsperados;i++){
		int alea = rand()%numIndividuos;
		int* padre1 = individuos[i]->getSolucionActual();
		int* padre2 = individuos[alea]->getSolucionActual();
		int* hijo1 = new int[tamIndividuo];
		int* hijo2 = new int[tamIndividuo];

		Solucion* hijo_1 = new Solucion();
		Solucion* hijo_2 = new Solucion();
		hijo_1->setQAP(qap);
		hijo_2->setQAP(qap);


		//Se calcula el corte intermedio
		int corte1 = rand()%tamIndividuo;
		int corte2 = rand()%tamIndividuo;
		if(corte1 > corte2){
			int c = corte1;
			corte1 = corte2;
			corte2 = c;
		}

		//Se guardan las correspondencias dentro del corte
		vector<pair<int,int> > correspondencias;
		int corte = corte1;
		while(corte<=corte2){
			hijo1[corte] = padre2[corte];
			hijo2[corte] = padre1[corte];
			correspondencias.push_back(pair<int,int>(padre1[corte],padre2[corte]));
			corte++;
		}


		//hijo1
		for(unsigned int j=0;j<tamIndividuo;j++){
			if(j<corte1 || j>corte2){
				int valor = padre1[j];
				for(int k=0;k<correspondencias.size();k++){
					if(correspondencias[k].second == valor){
						valor = correspondencias[k].first;
					}
				}
				hijo1[j] = valor;
			}
		}

		//hijo2
		for(unsigned int j=0;j<tamIndividuo;j++){
			if(j<corte1 || j>corte2){
				int valor = padre2[j];
				for(int k=0;k<correspondencias.size();k++){
					if(correspondencias[k].first == valor){
						valor = correspondencias[k].second;
					}
				}
				hijo2[j] = valor;
			}
		}

		//Se guardan los hijos
		hijo_1->setSolucionActual(hijo1);
		hijo_2->setSolucionActual(hijo2);
		individuos.push_back(hijo_1);
		individuos.push_back(hijo_2);
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
