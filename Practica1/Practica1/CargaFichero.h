#include <string>
#include <vector>
using namespace std;

#ifndef CARGAFICHERO_H
#define	CARGAFICHERO_H

class CargaFichero {
public:
    CargaFichero();
    void abrir(string nombreFich);
    CargaFichero(const CargaFichero& orig);
	void imprimirMatrizDistancia();
    virtual ~CargaFichero();
private:
    int numComp;
    vector<vector<int> * > matrizFlujo;
    vector<vector<int> * > matrizDistancia;
};

#endif	/* CARGAFICHERO_H */