/**
 * @file Practica.h
 * @authors: Pablo Molina Gonzalez y Diego Alberto P�rez Ortega
 */

#include <string>
#include <vector>
using namespace std;

#include "QAP.h"

#ifndef PRACTICA_H
#define	PRACTICA_H

/**
 * Clase que procesa todo el algoritmo de b�squeda.
 * Para explorar el espacio de soluciones. Nuestro algoritmo
 * almacena los cambios que se van a hacer en la permutaci�n
 * (soluci�n) actual dentro de un vector de parejas, donde
 * los distintos valores indican la posici�n de la permutaci�n
 * y el valor que tendr� respectivamente.
 *
 * El m�todo aplicarVecindad se encargar� de aplicar estos cambios
 * a la soluci�n actual y de vaciar la lista de cambios para poder
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
	vector<int> permutacion; ///< Soluci�n actual
	vector<pair<unsigned int, int>*> cambios; ///< Valores a cambiar para obtener el vecino deseado
	
	QAP matrices; ///< Matrices de flujo y distancia que determinan la calidad de la soluci�n

	int valorActual; ///< Valor de la soluci�n actual
	int valorSiguiente; ///< Valor de la soluci�n actual tras aplicar el vector de cambios
};

#endif	/* PRACTICA_H */
