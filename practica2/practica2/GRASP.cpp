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
		distancia = 0;
		for(int j=0;j<nComp;j++){
			flujo += (qap->flujo[i]->at(j) + qap->flujo[j]->at(i));
			distancia += (qap->distancia[i]->at(j) + qap->distancia[j]->at(i));			
		}
		vecflujo.push_back(flujo);
		vecdistan.push_back(distancia);
	}
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


float GRASP::calcularCoste(vector<CASILLA> vector){
	float valor = 0;
	for(int i=0;i<vector.size();i++){		
		for(int j=0;j<vector.size();j++){
			for(int k=0;k<vector.size();k++){
				valor=
				qap->flujo[vector[i].i]->at(j) *
				qap->distancia[vector[i].j]->at(k);	

			}
		}
	}
	return valor;
}




vector<CASILLA> GRASP::etapa2(){
	int nComp = qap->getNumComp();
	//Realizamos la etapa 1
	vector<CASILLA> solucionParcial = etapa1();
	vector<CASILLA> LC;
	vector<CASILLA> LRC;
	vector<pair<CASILLA,float> > vecCostes;
	float costeMinimo=99999,costeMaximo=0,alpha=0.3;
	do{
		//Se rellena la lista de candidatos con todos las combinaciones posibles menos las que ya están en la solución
		for(int i=0;i<nComp;i++){
			for(int j=0;j<nComp;j++){
				bool esta=false;
				for(int k=0;k<solucionParcial.size();k++){
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
		for(int i=0;i<LC.size();i++){
			float valor = 0;
			for(int j=0;j<nComp;j++){
				for(int k=0;k<nComp;k++){
					valor=
					qap->flujo[LC[i].i]->at(j) *
					qap->distancia[LC[i].j]->at(k);	

				}
			}
			pair<CASILLA,float> p(LC[i],valor);
			vecCostes.push_back(p);
			if(valor < costeMinimo){
				costeMinimo = valor;
			}
			if(costeMaximo < valor){
				costeMaximo = valor;
			}
		}

		//Creamos la LRC con las restricciones
		float umbral = costeMinimo + alpha*(costeMaximo-costeMinimo);
		for(int i=0;i<vecCostes.size();i++){
			if(vecCostes[i].second <= umbral){
				LRC.push_back(vecCostes[i].first);
			}
		}
		//Se inserta en la solución parcial una nueva parte
		int posAlea = rand() % LRC.size();
		solucionParcial.push_back(LRC[posAlea]);

		LC.clear();
		LRC.clear();
		vecCostes.clear();
	}while(solucionParcial.size() != nComp);

	return solucionParcial;

}

int* GRASP::generarSolucionGreedyAleatorizada () {
	vector<CASILLA> et = etapa2();
	int* solActual = new int[et.size()];
	for(int i=0;i<et.size();i++){
		solActual[i] = et[i].i;
	}
	return solActual;
}

void GRASP::seleccionarMejorSolucion (int* candidata, float valorCandidata) {
	if (valorCandidata < practica->getValorSolucionActual()) {
		practica->setSolucionActual(candidata, valorCandidata);
	}
}

GRASP::GRASP(QAP& qap, int semilla) :
	semilla(semilla),
	qap(&qap),
	practica(new Practica(semilla))
{
	practica->setQAP(&qap);
	bool criterioParada = true;
	int* solucionVecina = 0;
	float valorSolVecina = 0;
	int* mejorSolucion = new int[qap.getNumComp()];
	int valorMejorSolucion = 999999999;
	int numEjec = 0;

		solucionActual = generarSolucionGreedyAleatorizada();


	cout<<"Solucion Acutal"<<endl;
	for(int i=0;i<qap.getNumComp();i++){
		cout<<solucionActual[i]<<" ";
	}
	cout<<endl;


		solucionVecina = solucionActual;
		mejorSolucion = solucionActual;
		valorSolVecina = practica->getValorSolucionActual();
		valorMejorSolucion = valorSolVecina;
		practica->setSolucionActual(solucionActual,valorSolVecina);
		practica->busquedaLocal();
		seleccionarMejorSolucion(solucionVecina, valorSolVecina);

	while (numEjec < 24) {
		cout<<"NUMERO DE EJECUCIONES "<<numEjec<<endl;
		solucionActual = generarSolucionGreedyAleatorizada();
		solucionVecina = solucionActual;
		valorSolVecina = practica->getValorSolucionActual();
		practica->busquedaLocal();
		seleccionarMejorSolucion(solucionVecina, valorSolVecina);
		if(valorMejorSolucion > practica->getValorSolucionActual()){
			mejorSolucion = practica->getSolucionActual();
			valorMejorSolucion = practica->getValorSolucionActual();
		}
		numEjec++;
	}

	cout<<"Valor de la mejor solucion " <<valorMejorSolucion<<endl;
	cout<<"Solucion"<<endl;
	for(int i=0;i<qap.getNumComp();i++){
		cout<<mejorSolucion[i]<<" ";
	}
	cout<<endl;
}
