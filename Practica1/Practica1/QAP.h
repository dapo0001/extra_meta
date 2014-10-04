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
    QAP();
    void abrir(string nombreFich);
    QAP(const QAP& orig);
	void imprimirMatrizDistancia();
	int getNumComp(){return numComp;};
    virtual ~QAP();
private:
    int numComp;
    vector<vector<int> * > matrizFlujo;
    vector<vector<int> * > matrizDistancia;
};

#endif	/* CARGAFICHERO_H */