#include "ILS.h"
#include <ctime>
#include <iostream>
using namespace std;

// Depuración
#define DEBUG

ILS::ILS ():
	semilla(0),
	qap(0),
	practica(0),
	solucion(0)
{}

void ILS::ejecutar(QAP& qap, int semilla) {
	delete this->practica;
	this->semilla = semilla;
	this->qap = &qap;
	this->practica = new Practica(semilla);
	this->solucion = 0;
	this->valorSolucion = -1;
	this->tiempoEjecucion = -1;

#ifdef DEBUG
	clock_t inicio, fin;
	inicio = clock();
#endif

	int iteraciones = 0;
	void* historia = 0;
	int* solucionVecina = new int[qap.getNumComp()];
	int valorSolucionVecina = 999999999;
	int* mejorSolucion = new int[qap.getNumComp()];
	int valorMejorSolucion = 999999999;

	// Generamos una solución incial aleatoria
	// y le aplicamos la busqueda local
	practica->setQAP(&qap);
	practica->solucionInicial();
	practica->busquedaLocal();

	// Nuestra primera solución es la mejor hasta el momento
	clonarSolucion(mejorSolucion, practica->getSolucionActual());
	valorMejorSolucion = practica->getValorSolucionActual();

	do {
#ifdef DEBUG
		cout << ".";
#endif

		// Generamos un vecino a partir de la historia y lo almacenamos
		// copiando el vector por si tenemos que deshacer
		mutarSolucionActual(historia);
		clonarSolucion(solucionVecina, practica->getSolucionActual());
		valorSolucionVecina = practica->getValorSolucionActual();

		// Mejoramos la solucion vecina con la busqueda local
		practica->busquedaLocal();

		// Comprobamos si nos quedamos con la nueva solucion o con la version anterior
		// (la obtenida antes de aplicar la busqueda local)
		escogerSolucionActual(solucionVecina, valorSolucionVecina, historia);

		// Finalmente nos quedamos con la mejor solucion hasta el momento
		if (practica->getValorSolucionActual() < valorMejorSolucion) {
			clonarSolucion(mejorSolucion, practica->getSolucionActual());
			valorMejorSolucion = practica->getValorSolucionActual();
		}
	} while (++iteraciones < 24);

#ifdef DEBUG
	cout << endl << "Solucion encontrada: " << valorMejorSolucion << endl;
	fin = clock();
	this->tiempoEjecucion = (float)(fin - inicio) / CLOCKS_PER_SEC;
	cout << "Tiempo de ejecución: " << this->tiempoEjecucion << "s" << endl;
	//for (int i = 0; i < qap.getNumComp(); i++) {
	//	cout << mejorSolucion[i] << " ";
	//}
	//cout << endl;
#endif

	delete solucionVecina;
	this->valorSolucion = valorMejorSolucion;
}

void ILS::clonarSolucion (int* destino, int* origen) {
	for (int i = 0; i < qap->getNumComp(); i++) {
		destino[i] = origen[i];
	}
}

ILS::~ILS () {
	delete solucion;
}

void ILS::mutarSolucionActual (void* historia) {
	const int n = qap->getNumComp();
	const int t = n / 4;
	int inicioMutacion = rand() % (n - t);
	int finMutacion = inicioMutacion + t;

	for (int i = inicioMutacion; i < finMutacion; i++) {
		// Cambiamos el elemento actual
		practica->solucionVecina.primero = i;
		// Por uno al azar de la sublista mutada
		practica->solucionVecina.segundo = (rand() % t) + inicioMutacion;
		practica->aplicarVecindad();
	}
}

void ILS::escogerSolucionActual (int* candidata, int valorCandidata, void* historia) {
	if (valorCandidata < practica->getValorSolucionActual()) {
		practica->setSolucionActual(candidata, valorCandidata);
	}
}
