/*
@authors: Pablo Molina Gonzalez y Diego Alberto Pérez Ortega
*/

#include <string>
#include <vector>
using namespace std;

#ifndef PERMUTACION_H
#define	PERMUTACION_H

class Permutacion{
public:
	Permutacion(int tama);
	void solInicial(int semilla);
	void cambiarPosicion(unsigned int pos1,unsigned int pos2);
	void imprimir();
	virtual ~Permutacion();

private:
	vector<int> permutacion;

};



#endif	/* PERMUTACION_H */