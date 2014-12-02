/**
 * @file Solucion.h
 * @authors: Pablo Molina Gonzalez y Diego Alberto P�rez Ortega
 */

#ifndef Solucion_H
#define	Solucion_H

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
 * Clase que procesa todo el algoritmo de b�squeda.
 */
class Solucion {
public:
	Solucion (int _semilla = -1);
	virtual ~Solucion();

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

	// Adaptacion a la nueva Solucion
	void setSemilla (int semilla) { this->semilla = semilla; }
	void setQAP (QAP* qap);
	int* getSolucionActual () { return solucionActual; }
	void setSolucionActual (int* _s, int valor);
	void setSolucionActual (int* _s);
	int getValorSolucionActual () { return valorActual; }
	int getValorSolucionVecina () { return valorSiguiente; }
	CAMBIO solucionVecina;	///< Valores a cambiar para obtener el vecino deseado
private:
	int semilla;			///< Valor usado para generar n�meros aleatorios
	unsigned int n;			///< Tama�o de las matrices y la solucion
	int* solucionActual;	///< Soluci�n actual
	QAP* matrices;			///< Matrices de flujo y distancia que determinan la calidad de la soluci�n
	int valorActual;		///< Valor de la soluci�n actual
	int valorSiguiente;		///< Valor de la soluci�n actual tras aplicar la vecindad
};

#endif	/* Solucion_H */
