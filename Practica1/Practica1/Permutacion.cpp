/*
@authors: Pablo Molina Gonzalez y Diego Alberto Pérez Ortega
*/

#include "Permutacion.h"
#include <math.h>
#include <iostream>
using namespace std;

//Constructor por defecto
Permutacion::Permutacion(int tama){
	for(int i=0;i<tama;i++){
		permutacion.push_back(i);
	}
}

//Cambia 2 posiciones del vector
void Permutacion::cambiarPosicion(unsigned int pos1,unsigned int pos2){
	int valor = permutacion[pos1];
	permutacion[pos1] = permutacion[pos2];
	permutacion[pos2] = valor;
}

//Se encarga de permutar valores de forma aleatoria según la semilla asignada
void Permutacion::solInicial(int semilla){
	srand(semilla);
	for(int i=0;i<permutacion.size()/2;i++){
		int pos1 = rand()%permutacion.size();
		int pos2 = rand()%permutacion.size();
		cambiarPosicion(pos1,pos2);
	}
}

//imprime el vector permutacion
void Permutacion::imprimir(){
	for(int i=0;i<permutacion.size();i++){
		cout<<permutacion[i]<<" ";
	}
	cout<<endl;
}

Permutacion::~Permutacion(){
}