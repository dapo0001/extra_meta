/**
 * @file Practica.h
 * @authors: Pablo Molina Gonzalez y Diego Alberto Pérez Ortega
 */

#ifndef PRACTICA_H
#define	PRACTICA_H

#include <string>
#include <vector>
using namespace std;

#include "QAP.h"

/**
 * Estructura para almacenar la solucion
 * vecina. Cambia las posiciones primero
 * y segundo de la solucion actual
 */
typedef struct {
	int primero;
	int segundo;
} CAMBIO;

/**
 * Clase que procesa todo el algoritmo de búsqueda.
 */
class Practica {
public:
	Practica (int _semilla = -1);
	virtual ~Practica();

	// Metodos del proceso
	void solucionInicial();
	void cambiarPosicion (int* v, unsigned int pos1,unsigned int pos2);
	void funcionObjetivo ();
	void factorizacion ();
	void aplicarVecindad ();
	
	// Algoritmos
	void greedy ();
	void busquedaLocal ();

	// Depuracion
	void imprimir ();

	// Adaptacion a la nueva practica
	void setSemilla (int semilla) { this->semilla = semilla; }
	void setQAP (QAP* qap) { this->matrices = qap; }
	int* getSolucionActual () { return solucionActual; }
	int getValorSolucionActual () { return valorActual; }
	int getValorSolucionVecina () { return valorSiguiente; }
	CAMBIO solucionVecina;	///< Valores a cambiar para obtener el vecino deseado
private:
	int semilla;			///< Valor usado para generar números aleatorios
	unsigned int n;			///< Tamaño de las matrices y la solucion
	int* solucionActual;	///< Solución actual
	QAP* matrices;			///< Matrices de flujo y distancia que determinan la calidad de la solución
	int valorActual;		///< Valor de la solución actual
	int valorSiguiente;		///< Valor de la solución actual tras aplicar la vecindad
};

#endif	/* PRACTICA_H */
