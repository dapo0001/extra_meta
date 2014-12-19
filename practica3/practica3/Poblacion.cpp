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
{
	//mejorIndividuo = new Solucion();
};

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

	//Buscamos el mejor individuo de la población
	mejorIndividuo = new Solucion();
	mejorIndividuo->setSolucionActual(individuos[0]->getSolucionActual(),individuos[0]->getValorSolucionActual());
	for (unsigned int i = 1; i < _tamPoblacion; i++) {
		individuos[i] = new Solucion();
		individuos[i]->setQAP(qap);
		individuos[i]->solucionInicial();
		if (mejorIndividuo->getValorSolucionActual() > individuos[i]->getValorSolucionActual()) {			
			mejorIndividuo->setSolucionActual(individuos[i]->getSolucionActual(),individuos[i]->getValorSolucionActual());
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

//Se seleccionan los mejores individuos en torneos
void Poblacion::seleccion(){
	candidatos.clear();
	for(unsigned int i=0;i<individuos.size();i++){
		if(individuos[i]->getValorSolucionActual() > individuos[(i+1)%individuos.size()]->getValorSolucionActual()){	
			Solucion *s = new Solucion();
			s->setQAP(qap);
			s->setSolucionActual(individuos[(i+1)%individuos.size()]->getSolucionActual(),individuos[(i+1)%individuos.size()]->getValorSolucionActual());
			candidatos.push_back(s);
		}else{
			Solucion *s = new Solucion();
			s->setQAP(qap);
			s->setSolucionActual(individuos[(i)%individuos.size()]->getSolucionActual(),individuos[(i)%individuos.size()]->getValorSolucionActual());
			candidatos.push_back(s);
		}		
	}
}


//Cruce por posición para algoritmo genético generacional
void Poblacion::cruzar() {
	// Cruzamos individuos de la poblacion actual segun la esperanza de cruce
	int numPadres = crucesEsperados*2;
	for (unsigned int i=0;i<numPadres;i+=2){
		Solucion* hijo = candidatos[i]->cruzarPosicion(candidatos[i+1]);
		Solucion* hijo2 = candidatos[i+1]->cruzarPosicion(candidatos[i]);
		delete candidatos[i];
		delete candidatos[i+1];
		candidatos[i] = hijo;
		candidatos[i+1] = hijo2;
	}
}

//Método para algoritmo genético generacional
void Poblacion::cruzarPMX(){
	//Cruzamos los 2 padres y generamos 2 hijos
	int numPadres = crucesEsperados*2;
	for(unsigned int i=0;i<numPadres;i+=2){
		Solucion* hijo_1 = new Solucion();
		Solucion* hijo_2 = new Solucion();
		hijo_1->setQAP(qap);
		hijo_2->setQAP(qap);

		crucePMX(individuos[i],individuos[i+1],hijo_1,hijo_2);
		delete candidatos[i];
		delete candidatos[i+1];
		candidatos[i] = hijo_1;
		candidatos[i+1] = hijo_2;
	}
}

//Operador de mutación para algoritmo genético generacional
void Poblacion::mutar() {
	// Mutamos individuos de la poblacion actual segun la esperanza de mutacion
	for (unsigned int i = 0; i < mutacionesEsperadas; i++) {
		Solucion* individuoMutado = candidatos[rand() % candidatos.size()];
		individuoMutado->cambiarPosicion(individuoMutado->getSolucionActual(), rand() % tamIndividuo, rand() % tamIndividuo);
	}

	for(int i=0;i<individuos.size();i++){
		delete individuos[i];
		individuos[i] = candidatos[i];
	}
	
	for(unsigned int i=0;i<individuos.size();i++){
		if(mejorIndividuo->getValorSolucionActual() > individuos[i]->getValorSolucionActual()) {
			mejorIndividuo->setSolucionActual(individuos[i]->getSolucionActual(),individuos[i]->getValorSolucionActual());
		}		
	}

}

//Se combina una población con otra
Poblacion* Poblacion::combinar (Poblacion* p1) {
	// Combinamos dos poblaciones creando una tercera
	Poblacion* nuevaPoblacion = this->clonar();

	for(unsigned int i=0;i<p1->individuos.size();i++){
		Solucion* nuevaSolucion = new Solucion();
		nuevaSolucion->setQAP(qap);
		nuevaSolucion->setSolucionActual(p1->individuos[i]->getSolucionActual(),p1->individuos[i]->getValorSolucionActual());
		nuevaPoblacion->individuos.push_back(nuevaSolucion);

		if(mejorIndividuo->getValorSolucionActual() > nuevaSolucion->getValorSolucionActual()) {
			mejorIndividuo->setSolucionActual(nuevaSolucion->getSolucionActual(),nuevaSolucion->getValorSolucionActual());
		}		
	}

	return nuevaPoblacion;
}




//Método general para ambos algoritmos
//Dados los padres se devuelven los hijos
void Poblacion::crucePMX(Solucion* padre1,Solucion* padre2,Solucion* hijo_1,Solucion* hijo_2){
		int* padre_1 = padre1->getSolucionActual();
		int* padre_2 = padre2->getSolucionActual();
		int* hijo1 = new int[tamIndividuo];
		int* hijo2 = new int[tamIndividuo];
	
		//Se calcula el corte intermedio
		int corte1 = rand()%tamIndividuo;
		int corte2 = rand()%tamIndividuo;
		if(corte1 > corte2){
			int c = corte1;
			corte1 = corte2;
			corte2 = c;
		}

		//Se guardan las correspondencias dentro del corte
		int corte = corte1;
		while(corte<=corte2){
			hijo1[corte] = padre_2[corte];
			hijo2[corte] = padre_1[corte];
			corte++;
		}

		//Se rellenan los extremos de los cortes del hijo 1
		for(unsigned int j=0;j<tamIndividuo;j++){
			if(j<corte1 || j>corte2){
				int valor = padre_1[j];

				//Como se pueden generar ciclos, se comprueba el valor obtenido hasta el final del ciclo
				bool valorRepetido;
				do {
					valorRepetido = false;
					for (unsigned int _i = corte1; _i <= corte2; _i++) {
						if (valor == padre_2[_i]) {
							valorRepetido = true;
							valor = padre_1[_i];
						}
					}
				} while (valorRepetido);

				hijo1[j] = valor;
			}
		}

		//Se rellenan los extremos de los cortes del hijo 2
		for(unsigned int j=0;j<tamIndividuo;j++){
			if(j<corte1 || j>corte2){
				int valor = padre_2[j];

				//Como se pueden generar ciclos, se comprueba el valor obtenido hasta el final del ciclo
				bool valorRepetido;
				do {
					valorRepetido = false;
					for (unsigned int _i = corte1; _i <= corte2; _i++) {
						if (valor == padre_1[_i]) {
							valorRepetido = true;
							valor = padre_2[_i];
						}
					}
				} while (valorRepetido);
				hijo2[j] = valor;
			}
		}

		//Se guardan los hijos
		hijo_1->setSolucionActual(hijo1);
		hijo_2->setSolucionActual(hijo2);

		//Se borran los arrays creados localmente
		delete hijo1;
		delete hijo2;
}




//Método de selección, cruce por posición y mutación para el algoritmo genético estacionario
void Poblacion::seleccioncrucemutacion(){

	//Se seleccionan 2 padres aleatoriamente
	int alea1 = rand()%individuos.size();
	int alea2 = rand()%individuos.size();

	Solucion* hijo1;
	Solucion* hijo2;

	//cruce
	individuos[alea1]->cruzarPosicion(individuos[alea2],hijo1,hijo2);
	
	//mutacion
	//Se escoge uno de los hijos aleatoriamente y se muta un cromosoma suyo
	for (unsigned int i = 0; i < mutacionesEsperadas; i++) {
		int alea = rand()%2;
		if(alea == 0){
			hijo1->cambiarPosicion(hijo1->getSolucionActual(), rand() % tamIndividuo, rand() % tamIndividuo);
		}else{
			hijo2->cambiarPosicion(hijo2->getSolucionActual(), rand() % tamIndividuo, rand() % tamIndividuo);
		}
	}
	//Se calcula el valor actual de cada hijo
	hijo1->funcionObjetivo();
	hijo2->funcionObjetivo();

	//Se buscan los 2 peores individuos para enfrentarlos con los hijos
	Solucion* peorIndiviuo1 = individuos[0];
	Solucion* peorIndiviuo2 = individuos[1];
	for(unsigned int i=2;i<individuos.size();i+=2){
		if(individuos[i]->getValorSolucionActual() > peorIndiviuo1->getValorSolucionActual()){
			peorIndiviuo1 = individuos[i];
			alea1 = i;
		}else if(individuos[i]->getValorSolucionActual() > peorIndiviuo2->getValorSolucionActual()){
			peorIndiviuo2 = individuos[i];
			alea2 = i;
		}
		if(individuos[i+1]->getValorSolucionActual() > peorIndiviuo1->getValorSolucionActual()){
			peorIndiviuo1 = individuos[i+1];
			alea1 = i+1;
		}else  if(individuos[i+1]->getValorSolucionActual() > peorIndiviuo2->getValorSolucionActual()){
			peorIndiviuo2 = individuos[i+1];
			alea2 = i+1;
		}
	}

	//Los 2 peores individuos compiten con los hijos generados
	bool padre1borrado = false,padre2borrado = false,hijo1insertado=false,hijo2insertado=false;
	
	//Para el hijo1
	if(individuos[alea1]->getValorSolucionActual() > hijo1->getValorSolucionActual()){		
		delete individuos[alea1];
		individuos[alea1] = hijo1;
		padre1borrado = true;
		hijo1insertado = true;
	}else if(individuos[alea2]->getValorSolucionActual() > hijo1->getValorSolucionActual()){
		delete individuos[alea2];
		individuos[alea2] = hijo1;
		padre2borrado = true;
		hijo1insertado = true;
	}

	//Para el hijo2
	if(!padre1borrado && individuos[alea1]->getValorSolucionActual() > hijo2->getValorSolucionActual()){		
		delete individuos[alea1];
		individuos[alea1] = hijo2;
		hijo2insertado = true;
	}else if(!padre2borrado && individuos[alea2]->getValorSolucionActual() > hijo2->getValorSolucionActual()){
		delete individuos[alea2];
		individuos[alea2] = hijo2;
		hijo2insertado = true;
	}

	if(!hijo1insertado) delete hijo1;
	if(!hijo2insertado) delete hijo2;

	//Se busca el mejor individuo
	mejorIndividuo = individuos[0];
	for(unsigned int i=1;i<individuos.size();i++){
		if(mejorIndividuo->getValorSolucionActual() > individuos[i]->getValorSolucionActual()){
			mejorIndividuo = individuos[i];		
		}
	}

}


//Selección, cruce PMX y mutación para algoritmo genético estacionario
void Poblacion::seleccioncrucePMXmutacion(){

	//Se seleccionan 2 padres aleatoriamente
	int alea1 = rand()%individuos.size();
	int alea2 = rand()%individuos.size();

	Solucion* hijo_1 = new Solucion();
	Solucion* hijo_2 = new Solucion();
	hijo_1->setQAP(qap);
	hijo_2->setQAP(qap);

	//cruce
	crucePMX(individuos[alea1],individuos[alea2],hijo_1,hijo_2);

	//mutacion
	//Se escoge uno de los hijos aleatoriamente y se muta un cromosoma suyo
	for (unsigned int i = 0; i < mutacionesEsperadas; i++) {
		int alea = rand()%2;
		if(alea == 0){
			hijo_1->cambiarPosicion(hijo_1->getSolucionActual(), rand() % tamIndividuo, rand() % tamIndividuo);
		}else{
			hijo_2->cambiarPosicion(hijo_1->getSolucionActual(), rand() % tamIndividuo, rand() % tamIndividuo);
		}
	}
	hijo_1->funcionObjetivo();
	hijo_2->funcionObjetivo();

	//Se buscan los 2 peores individuos para enfrentarlos con los hijos
	Solucion* peorIndiviuo1 = individuos[0];
	Solucion* peorIndiviuo2 = individuos[1];
	for(unsigned int i=2;i<individuos.size();i+=2){
		if(individuos[i]->getValorSolucionActual() > peorIndiviuo1->getValorSolucionActual()){
			peorIndiviuo1 = individuos[i];
			alea1 = i;
		}else if(individuos[i]->getValorSolucionActual() > peorIndiviuo2->getValorSolucionActual()){
			peorIndiviuo2 = individuos[i];
			alea2 = i;
		}
		if(individuos[i+1]->getValorSolucionActual() > peorIndiviuo1->getValorSolucionActual()){
			peorIndiviuo1 = individuos[i+1];
			alea1 = i+1;
		}else  if(individuos[i+1]->getValorSolucionActual() > peorIndiviuo2->getValorSolucionActual()){
			peorIndiviuo2 = individuos[i+1];
			alea2 = i+1;
		}
	}

	//Los 2 peores individuos compiten con los hijos generados
	bool padre1borrado = false,padre2borrado = false,hijo1insertado=false,hijo2insertado=false;

	//Para el hijo1
	if(individuos[alea1]->getValorSolucionActual() > hijo_1->getValorSolucionActual()){		
		delete individuos[alea1];
		individuos[alea1] = hijo_1;
		padre1borrado = true;
		hijo1insertado = true;
	}else if(individuos[alea2]->getValorSolucionActual() > hijo_1->getValorSolucionActual()){
		delete individuos[alea2];
		individuos[alea2] = hijo_1;
		padre2borrado = true;
		hijo1insertado = true;
	}

	//Para el hijo2
	if(!padre1borrado && individuos[alea1]->getValorSolucionActual() > hijo_2->getValorSolucionActual()){		
		delete individuos[alea1];
		individuos[alea1] = hijo_2;
		hijo2insertado = true;
	}else if(!padre2borrado && individuos[alea2]->getValorSolucionActual() > hijo_2->getValorSolucionActual()){
		delete individuos[alea2];
		individuos[alea2] = hijo_2;
		hijo2insertado = true;
	}

	if(!hijo1insertado) delete hijo_1;
	if(!hijo2insertado) delete hijo_2;

	//Se busca el mejor individuo
	mejorIndividuo = individuos[0];
	for(unsigned int i=1;i<individuos.size();i++){
		if(mejorIndividuo->getValorSolucionActual() > individuos[i]->getValorSolucionActual()){
			mejorIndividuo = individuos[i];		
		}
	}

}




Poblacion::~Poblacion(){

	for(int i=0;i<individuos.size();i++){
		if (individuos[i] == mejorIndividuo) {
			mejorIndividuo = 0;
		}
		delete individuos[i];
		individuos[i] = 0;
	}


	delete mejorIndividuo;
}
