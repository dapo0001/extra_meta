#include "GRASP.h"
#include <ctime>
#include <iostream>
using namespace std;

#define DEBUG

vector<CASILLA> GRASP::etapa1(){
	//Inicializaciones
	int nComp = qap->getNumComp();
	float
		flujo = 0,
		distancia = 0;
	vector<CASILLA> solucion;
	vector<float> vecflujo;
	vector<float> vecdistan;
	vector<int> LCun;
	vector<int> LCloc;
	
	float
		flujomin = 99999999.0f,
		flujomax = 0,
		distanciamin = 99999999.0f,
		distanciamax = 0;
	
	float
		alpha = 0.3f,
		umbralFlujo = 0,
		umbralDistancia = 0;

	//Calculamos el coste e introducimos en el vector correspondiente
	for(int i=0;i<nComp;i++){	
		flujo = 0;
		distancia = 0;
		
		for(int j=0;j<nComp;j++){
			flujo += (qap->flujo[i]->at(j) + qap->flujo[j]->at(i));
			distancia += (qap->distancia[i]->at(j) + qap->distancia[j]->at(i));			
		}

		vecflujo.push_back(flujo);
		vecdistan.push_back(distancia);

		// Guardamos el flujo/distancia minimo/maximo

		if (flujo < flujomin) { flujomin = flujo; }
		if (flujo > flujomax) { flujomax = flujo; }
		if (distancia < distanciamin) { distanciamin = distancia; }
		if (distancia > distanciamax) { distanciamax = distancia; }
	}

	//Calculamos el umbral
	umbralFlujo = flujomin + alpha * (flujomax - flujomin);
	umbralDistancia = distanciamax - alpha * (distanciamax - distanciamin);

	//insertamos en la lista de candidatos los elementos que superan el umbral
	for(int i=0;i<nComp;i++){
		if(vecflujo[i] >= umbralFlujo){
			LCun.push_back(i);
		}

		if(vecdistan[i] <= umbralDistancia){
			LCloc.push_back(i);
		}
	}

	//Construimos la solución parcial y la retornamos
	CASILLA c1,c2;
	c1.i = rand()%LCun.size();
	c1.j = rand()%LCloc.size();
	c2.i = rand()%LCun.size();
	c2.j = rand()%LCloc.size();
	solucion.push_back(c1);
	solucion.push_back(c2);
	return solucion;

}

vector<CASILLA> GRASP::etapa2(){
	int nComp = qap->getNumComp();
	//Realizamos la etapa 1
	vector<CASILLA> solucionParcial = etapa1();
	vector<CASILLA> LC;
	vector<CASILLA> LRC;
	float
		costeMinimo,
		costeMaximo,
		alpha=0.3f;

	do{
		costeMinimo = 99999999.0f;
		costeMaximo = 0.0f;

		//Se rellena la lista de candidatos con todos las combinaciones posibles menos las que ya están en la solución
		for(int i=0;i<nComp;i++){
			for(int j=0;j<nComp;j++){
				bool esta=false;
				for(unsigned int k=0;k<solucionParcial.size();k++){
					if(i==solucionParcial[k].i ){
						esta=true;
					}
				}
				if(!esta){
					CASILLA casilla;
					casilla.i=i;
					casilla.j=j;
					LC.push_back(casilla);
				}
			}
		}

		//Calculamos el coste de cada uno de la LC
		for(unsigned int i = 0; i < LC.size(); i++){
			float valor = LC_valores[LC[i].i][LC[i].j];
			if (valor < costeMinimo) { costeMinimo = valor; }
			if (valor > costeMaximo) { costeMaximo = valor; }
		}

		//Creamos la LRC con las restricciones
		float umbral = costeMinimo + alpha * (costeMaximo - costeMinimo);
		
		for (unsigned int i = 0; i < LC.size(); i++){
			if(LC_valores[LC[i].i][LC[i].j] <= umbral){
				LRC.push_back(LC[i]);
			}
		}

		//Se inserta en la solución parcial una nueva parte
		int posAlea = rand() % LRC.size();
		solucionParcial.push_back(LRC[posAlea]);

		LC.clear();
		LRC.clear();
	}while(solucionParcial.size() != nComp);

	return solucionParcial;

}

int* GRASP::generarSolucionGreedyAleatorizada () {
	vector<CASILLA> et = etapa2();
	int* solActual = new int[et.size()];
	for(unsigned int i=0;i<et.size();i++){
		solActual[i] = et[i].i;
	}
	return solActual;
}

void GRASP::seleccionarMejorSolucion (int* candidata, float valorCandidata) {
	if (valorCandidata < practica->getValorSolucionActual()) {
		practica->setSolucionActual(candidata, (int) valorCandidata);
	}
}

GRASP::~GRASP(){
	delete solucionActual;

	unsigned int n = (unsigned int) this->qap->getNumComp();
	for (unsigned int i = 0; i < n; i++) {
		delete LC_valores[i];
	}
	delete LC_valores;
}

GRASP::GRASP(QAP& qap, int semilla) :
	semilla(semilla),
	qap(&qap),
	practica(new Practica(semilla))
{
#ifdef DEBUG
	clock_t inicio, fin;
	inicio = clock();
#endif
	practica->setQAP(&qap);
	bool criterioParada = true;
	int* solucionVecina = 0;
	float valorSolVecina = 0;
	int* mejorSolucion = new int[qap.getNumComp()];
	float valorMejorSolucion = 999999999.0f;
	int numEjec = 0;

	this->generarValoresComponentes();

	solucionActual = generarSolucionGreedyAleatorizada();
	practica->setSolucionActual(solucionActual);

	solucionVecina = solucionActual;
	mejorSolucion = solucionActual;
	valorSolVecina = (float) practica->getValorSolucionActual();
	valorMejorSolucion = valorSolVecina;
	practica->setSolucionActual(solucionActual, (int) valorSolVecina);
	practica->busquedaLocal();
	seleccionarMejorSolucion(solucionVecina, valorSolVecina);

	while (numEjec < 24) {
#ifdef DEBUG
		cout << ".";
#endif
		solucionActual = generarSolucionGreedyAleatorizada();
		solucionVecina = solucionActual;
		valorSolVecina = (float) practica->getValorSolucionActual();
		practica->busquedaLocal();
		seleccionarMejorSolucion(solucionVecina, valorSolVecina);
		if(valorMejorSolucion > practica->getValorSolucionActual()){
			mejorSolucion = practica->getSolucionActual();
			valorMejorSolucion = (float) practica->getValorSolucionActual();
		}
		numEjec++;
	}

#ifdef DEBUG
	cout << endl << "Solución encontrada: " << (int) valorMejorSolucion << endl;
	fin = clock();
	cout << "Tiempo de ejecución: " << (float)(fin - inicio) / CLOCKS_PER_SEC << "s" << endl;
	//for (int i = 0; i < qap.getNumComp(); i++) {
	//	cout << mejorSolucion[i] << " ";
	//}
	//cout << endl;
#endif
}

/**
 * Genera todos los valores para todos los componentes una sola vez
 */
void GRASP::generarValoresComponentes () {
	unsigned int n = (unsigned int) this->qap->getNumComp();
	LC_valores = new float*[n];
	for (unsigned int i = 0; i < n; i++) {
		LC_valores[i] = new float[n];
		for (unsigned int j = 0; j < n; j++) {
			LC_valores[i][j] = 0;

			for (unsigned int k = 0; k < n; k++) {
				for (unsigned int l = 0; l < n; l++) {
					LC_valores[i][j] +=
						qap->flujo[i]->at(k) *
						qap->distancia[j]->at(l);
				}
			}
		}
	}
}
