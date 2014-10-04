/**
 * @file QAP.h
 * @authors: Pablo Molina González y Diego Alberto Pérez Ortega
 */

#include <string>
#include <vector>
using namespace std;

#ifndef QAP_H
#define	QAP_H

class QAP {
public:
	vector<vector<int> * > matrizFlujo;
    vector<vector<int> * > matrizDistancia;

	QAP();
	QAP(const QAP& orig);
    
	void abrir(string nombreFich);
	void imprimirMatrizDistancia();
	int getNumComp(){return numComp;};
    virtual ~QAP();

private:
    int numComp;
};

#endif	/* CARGAFICHERO_H */
