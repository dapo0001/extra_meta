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
class Practica {
public:
	Practica ();
	virtual ~Practica();

	// Metodos del proceso
	void solucionInicial (int semilla);
	void cambiarPosicion (int* v, unsigned int pos1,unsigned int pos2);
	void funcionObjetivo ();
	void factorizacion ();
	void aplicarVecindad ();
	
	// Algoritmos
	void algoritmo (unsigned int valor);
	void greedy ();
	void busquedaLocal ();
	void tabu ();
	
	// Interfaz de la practica
	void menuFichero ();
	void cargarFich (int valor);
	void menuAlgoritmo ();
	void imprimir ();

private:
	int semilla;			///< Valor usado para generar n�meros aleatorios
	unsigned int n;			///< Tama�o de las matrices y la solucion
	int* solucionActual;	///< Soluci�n actual
	CAMBIO solucionVecina;	///< Valores a cambiar para obtener el vecino deseado
	QAP matrices;			///< Matrices de flujo y distancia que determinan la calidad de la soluci�n
	int valorActual;		///< Valor de la soluci�n actual
	int valorSiguiente;		///< Valor de la soluci�n actual tras aplicar la vecindad
};

#endif	/* PRACTICA_H */
