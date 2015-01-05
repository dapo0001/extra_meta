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

	//Cruce PMX común
	void crucePMX(Solucion* padre1,Solucion* padre2,Solucion* hijo_1,Solucion* hijo_2);

	//Para algoritmo generacional
	void cruzar();
	void mutar();
	void seleccion();
	void cruzarPMX();

	//Para algoritmo estacionario
	void seleccioncrucemutacion();
	void seleccioncrucePMXmutacion();

	// Para algoritmo memetico
	void busquedaLocal(double probabilidadCromosoma, bool buscarMejores);

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
	vector<Solucion*> candidatos;
};

#endif
