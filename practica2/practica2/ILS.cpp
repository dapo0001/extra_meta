#include "ILS.h"
#include <iostream>
using namespace std;

void ILS::clonarSolucion (int* destino, int* origen) {
	for (int i = 0; i < qap->getNumComp(); i++) {
		destino[i] = origen[i];
	}
}

void ILS::mutarSolucionActual (void* historia) {
	int n = qap->getNumComp();
	int _n = (int)(n * 0.25);

	// Generamos _n mutaciones
	for (int i = 0; i < _n; i++) {
		practica->solucionVecina.primero = rand() % qap->getNumComp();
		practica->solucionVecina.segundo = rand() % qap->getNumComp();
		practica->aplicarVecindad();
	}
}

void ILS::escogerSolucionActual (int* candidata, int valorCandidata, void* historia) {
	if (valorCandidata < practica->getValorSolucionActual()) {
		practica->setSolucionActual(candidata, valorCandidata);
	}
}

ILS::ILS(QAP& qap, int semilla):
	semilla(semilla),
	qap(&qap),
	practica(new Practica(semilla))
{
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

	do {
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
	} while (++iteraciones < 1000);

	cout << "Solucion encontrada (" << valorMejorSolucion << ")" << endl;
	for (int i = 0; i < qap.getNumComp(); i++) {
		cout << mejorSolucion[i] << " ";
	}
	cout << endl;

	delete solucionVecina;
	delete mejorSolucion;
}
