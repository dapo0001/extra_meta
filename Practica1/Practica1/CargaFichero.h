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
    virtual ~CargaFichero();
private:
    int numComp;
    vector<vector<int> * > matrizDistancia;
    vector<vector<int> * > matrizLocalizacion;
};

#endif	/* CARGAFICHERO_H */