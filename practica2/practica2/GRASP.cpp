#include "GRASP.h"
#include <ctime>
#include <iostream>
using namespace std;

#define DEBUG

int* GRASP::generarSolucionGreedyAleatorizada () {

	//Inicializaciones
	int nComp = qap->getNumComp();
	int* LCun = new int[nComp];
	int* LCloc = new int[nComp];
	int flujo=0,distancia=0,numSol=0;

	//Generamos una solución inicial
	practica->solucionInicial();
	int* solucion = practica->getSolucionActual();

	//Calculamos el coste
	for(int i=0;i<nComp;i++){			
		for(int j=0;j<nComp;j++){
			flujo += (qap->flujo[solucion[i]]->at(j) + qap->flujo[solucion[j]]->at(i));
			distancia += (qap->distancia[solucion[i]]->at(j) + qap->distancia[solucion[j]]->at(i));			
		}
	}
	/*
	while(numSol!= nComp){
		double umbral=0;

	}
	*/
	



		return solucion;
}

int* GRASP::seleccionarMejorSolucion (int* solucion1, int* solucion2) {
	return 0;
}

GRASP::GRASP(QAP& qap, int semilla) :
	semilla(semilla),
	qap(&qap),
	practica(new Practica(semilla))
{
	practica->setQAP(&qap);
	bool criterioParada = true;
	int* solucionActual = 0;
	int* mejorSolucionVecina = 0;
	int* mejorSolucion = 0;

	//while (criterioParada) {
		solucionActual = generarSolucionGreedyAleatorizada();
		//mejorSolucionVecina = busquedaLocal(solucionActual);
		//mejorSolucion = seleccionarMejorSolucion(mejorSolucionVecina, mejorSolucion);
	//}
}
