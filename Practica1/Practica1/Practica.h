/**
 * @file Practica.h
 * @authors: Pablo Molina Gonzalez y Diego Alberto Pérez Ortega
 */

#include <string>
#include <vector>
using namespace std;

#include "QAP.h"

#ifndef PRACTICA_H
#define	PRACTICA_H

/**
 * Clase que procesa todo el algoritmo de búsqueda.
 * Para explorar el espacio de soluciones. Nuestro algoritmo
 * almacena los cambios que se van a hacer en la permutación
 * (solución) actual dentro de un vector de parejas, donde
 * los distintos valores indican la posición de la permutación
 * y el valor que tendrá respectivamente.
 *
 * El método aplicarVecindad se encargará de aplicar estos cambios
 * a la solución actual y de vaciar la lista de cambios para poder
 * generar nuevos vecinos.
 *
 * Ejemplo:
 *  permutacion: [1, 0, 2]
 *  cambios: [[0, 2], [2, 1]]
 *  aplicarVecindad() -> futura permutacion: [2, 0, 1]
 */
class Practica {
public:
	Practica ();
	virtual ~Practica();

	// Metodos del proceso
	void solInicial (int semilla);
	void cambiarPosicion (unsigned int pos1,unsigned int pos2);
	void funcionObjetivo ();
	void addCambio(unsigned int posicion, int valor);
	void factorizacion ();
	void aplicarVecindad();
	void algoritmo();

	// Algoritmos
	void greedy();
	
	// Interfaz de la practica
	void menuFichero ();
	void cargarFich (int valor);
	void menuAlgoritmo ();
	void imprimir ();

private:
	vector<int> permutacion; ///< Solución actual
	vector<pair<unsigned int, int>*> cambios; ///< Valores a cambiar para obtener el vecino deseado
	
	QAP matrices; ///< Matrices de flujo y distancia que determinan la calidad de la solución

	int valorActual; ///< Valor de la solución actual
	int valorSiguiente; ///< Valor de la solución actual tras aplicar el vector de cambios
};

#endif	/* PRACTICA_H */
