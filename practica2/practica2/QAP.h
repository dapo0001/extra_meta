/**
 * @file QAP.h
 * @authors: Pablo Molina González y Diego Alberto Pérez Ortega
 */

#ifndef QAP_H
#define	QAP_H

#include <string>
#include <vector>
using namespace std;

class QAP {
public:
	vector<vector<int> * > flujo;
    vector<vector<int> * > distancia;

	QAP();
	virtual ~QAP();
    
	void abrir(string nombreFich);
	void imprimirMatrizDistancia();
	int getNumComp() const { return numComp; };

private:
    int numComp;
};

#endif	/* QAP_H */
