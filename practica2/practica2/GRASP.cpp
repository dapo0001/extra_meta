#include "GRASP.h"
#include <ctime>
#include <iostream>
using namespace std;

#define DEBUG

vector<CASILLA> GRASP::etapa1(){

	//Inicializaciones
	int nComp = qap->getNumComp();
	int flujo=0,distancia=0;
	vector<CASILLA> solucion;
	vector<float> vecflujo;
	vector<float> vecdistan;
	vector<int> LCun;
	vector<int> LCloc;
	int flujomin=999999,flujomax=0,distanciamin=99999,distanciamax=0;
	float alpha = 0.3,umbralFlujo=0,umbralDistancia=0;

	//Calculamos el coste e introducimos en el vector correspondiente
	for(int i=0;i<nComp;i++){	
		flujo = 0;
		for(int j=0;j<nComp;j++){
			flujo += (qap->flujo[i]->at(j) + qap->flujo[j]->at(i));
			distancia += (qap->distancia[i]->at(j) + qap->distancia[j]->at(i));			
		}
		vecflujo.push_back(flujo);
		vecdistan.push_back(distancia);
	}

	/*
	cout<<"flujo"<<endl;
	for(int i=0;i<vecflujo.size();i++){
		cout<<vecflujo[i]<<" ";
	}
	cout<<endl;
	cout<<"distancia"<<endl;
	for(int i=0;i<vecdistan.size();i++){
		cout<<vecdistan[i]<<" ";
	}
	cout<<endl;
	*/
	//Calculamos el rango minimo y máximo de los flujos y distancias
	for(int i=0;i<vecflujo.size();i++){
		//Para Flujo
		if(vecflujo[i] < flujomin){
			flujomin = vecflujo[i];
		}
		if(vecflujo[i] > flujomax){
			flujomax = vecflujo[i];
		}
		//Para distancia
		if(vecdistan[i] < distanciamin){
			distanciamin = vecdistan[i];
		}
		if(vecdistan[i] > distanciamax){
			distanciamax = vecdistan[i];
		}
	}

	//Calculamos el umbral
	umbralFlujo = flujomax - alpha*(flujomax - flujomin);
	umbralDistancia = distanciamin + alpha*(distanciamax - distanciamin);
	/*
	cout<<"umbral flujo "<<umbralFlujo<<endl;
	cout<<"umbral distancia "<<umbralDistancia<<endl;
	*/

	//insertamos en la lista de candidatos los elementos que superan el umbral
	for(int i=0;i<vecflujo.size();i++){
		if(vecflujo[i] > umbralFlujo){
			LCun.push_back(i);
		}
	}
	for(int i=0;i<vecdistan.size();i++){
		if(vecdistan[i] < umbralDistancia){
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

int* GRASP::etapa2(){
	int nComp = qap->getNumComp();
	//Realizamos la etapa 1
	vector<CASILLA> solucionParcial = etapa1();
	vector<CASILLA> LC;
	float costeMinimo=99999,costeMaximo=0,alpha=0.3;

	//Se rellena la lista de candidatos con todos las combinaciones posibles menos las que ya están en la solución
	for(int i=0;i<nComp;i++){
		for(int j=0;j<nComp;j++){
			for(int k=0;k<solucionParcial.size();k++){
				if(i!=solucionParcial[k].i && j!=solucionParcial[k].j){
					CASILLA casilla;
					casilla.i=i;
					casilla.j=j;
					LC.push_back(casilla);
				}
			}
		}
	}

	//Calculamos el coste de cada uno de la LC
	for(int i=0;i<LC.size();i++){
		for(int j=0;j<nComp;j++){
			for(int k=0;k<nComp;k++){
				int valor=
				qap->flujo[LC[i].i]->at(j) *
				qap->distancia[LC[i].j]->at(k);	
				if(valor < costeMinimo){
					costeMinimo = valor;
				}
				if(costeMaximo < valor){
					costeMaximo = valor;
				}
			}
		}
	}



	return 0;

}

int* GRASP::generarSolucionGreedyAleatorizada () {



	return 0;
	
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
	valorActual = 0;
	int* mejorSolucionVecina = 0;
	int* mejorSolucion = 0;


	//while (criterioParada) {
		solucionActual = generarSolucionGreedyAleatorizada();
		//mejorSolucionVecina = busquedaLocal(solucionActual);
		//mejorSolucion = seleccionarMejorSolucion(mejorSolucionVecina, mejorSolucion);
	//}
}
