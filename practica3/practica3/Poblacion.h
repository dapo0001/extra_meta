#ifndef _POBLACION_H_
#define _POBLACION_H_

#include <vector>
using namespace std;

#include "Solucion.h"

class Poblacion {
public:
	Poblacion(QAP* _qap);
	Poblacion(
		QAP* _qap,
		unsigned int tamIndividuo,
		unsigned int tamPoblacion = 50,
		float probabilidadCruce = 0.7,
		float probabilidadMutacion = 0.01);
	virtual ~Poblacion();

	Poblacion* combinar(Poblacion* p1);


	Poblacion* clonar();

	//Para algoritmo generacional
	void cruzar();
	void mutar();
	void seleccion();
	void cruzarPMX();

	//Para algoritmo estacionario
	void seleccioncrucemutacion();

	Solucion* getMejorIndividuo() const { return mejorIndividuo; }


private:
	QAP* qap;
	unsigned int tamIndividuo;

	float probabilidadCruce;
	unsigned int crucesEsperados;

	float probabilidadMutacion;
	unsigned int mutacionesEsperadas;

	Solucion* mejorIndividuo;
	vector<Solucion*> individuos;
};

#endif
