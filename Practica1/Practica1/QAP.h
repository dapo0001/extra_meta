/*
@authors: Pablo Molina Gonzalez y Diego Alberto Pérez Ortega
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
    void abrir(string nombreFich);
    QAP(const QAP& orig);
	void imprimirMatrizDistancia();
	int getNumComp(){return numComp;};
    virtual ~QAP();
private:
    int numComp;

};

#endif	/* CARGAFICHERO_H */