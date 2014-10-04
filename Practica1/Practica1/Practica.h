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

class Practica{
public:
	Practica ();
	void solInicial (int semilla);
	void cambiarPosicion (unsigned int pos1,unsigned int pos2);
	void imprimir ();
	void funcionObjetivo ();
	void factorizacion ();
	void menuFichero ();
	void cargarFich (int valor);
	void menuAlgoritmo ();
	virtual ~Practica();

private:
	vector<int> permutacion;
	QAP matrices;
	int valorMinimo;
};

#endif	/* PRACTICA_H */
