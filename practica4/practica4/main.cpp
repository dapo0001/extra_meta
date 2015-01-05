#include <iostream>
#include <fstream>
using namespace std;

#include "QAP.h"
#include "Algoritmo.h"
#include "AlgoritmoMemetico.h"

int seleccionarSemilla (const int semillas[], const int numSemillas) {
	int semilla = -2;
	do {
		cout << "Selecciona una semilla: ";
		cin >> semilla;
	} while (semilla < -1);

	return semilla;
}

int seleccionarFichero (const char* ficheros[], const int numFicheros) {
	int fichero = -2;
	do {
		cout << "Selecciona un fichero:" << endl;
		for (int i = 0; i < numFicheros; i++) {
			cout << "  " << i << ". " << ficheros[i] << endl;
		}
		cin >> fichero;
	} while (fichero < -1 || fichero >= numFicheros);
	return fichero;
}

int seleccionarAlgoritmo (const char* nombresAlgoritmos[], const int numAlgoritmos) {
	int algoritmo = -2;
	do {
		cout << "Selecciona un algoritmo:" << endl;
		for (int i = 0; i < numAlgoritmos; i++) {
			cout << "  " << i << ". " << nombresAlgoritmos[i] << endl;
		}
		cin >> algoritmo;
	} while (algoritmo < -1 || algoritmo >= numAlgoritmos);
	return algoritmo;
}

int seleccionarTipoAlgoritmo (const char* tipoAlgoritmo[], const int numTipos) {
	int tipo = -2;
	do {
		cout << "Selecciona un tipo de cruce:" << endl;
		for (int i = 0; i < numTipos; i++) {
			cout << "  " << i << ". " << tipoAlgoritmo[i] << endl;
		}
		cin >> tipo;
	} while (tipo < -1 || tipo >= numTipos);
	return tipo;
}

int seleccionarHibridacion (const char* hibridaciones[], const int numHibridaciones) {
	int hibridacion = -2;
	do {
		cout << "Selecciona un tipo de hibridación:" << endl;
		for (int i = 0; i < numHibridaciones; i++) {
			cout << "  " << i << ". " << hibridaciones[i] << endl;
		}
		cin >> hibridacion;
	} while (hibridacion < -1 || hibridacion >= numHibridaciones);
	return hibridacion;
}

void ejecutar (int semilla, const char* fichero, Algoritmo* algoritmo, int tipo, int hibridacion, QAP* qap) {
	qap->abrir(("ficheros/" + string(fichero) + ".dat").c_str());
	((AlgoritmoMemetico*) algoritmo)->setHibridacion(hibridacion);
	algoritmo->ejecutar(*qap, semilla, tipo);
}

int main () {
	QAP qap;
	const int numSemillas = 25;
	const int numFicheros = 20;
	const int numAlgoritmos = 1;
	const int numTipos = 2;
	const int numHibridaciones = 3;

	const int semillas[] = {
		5538,
		912373,
		984359,
		1923312,
		7891237,
		7129323,
		870345,
		123784,
		49785,
		983495,
		89454,
		47895,
		77304,
		12398,
		349834,
		12393,
		34983,
		23832,
		12398,
		12093,
		8540,
		934,
		97754,
		17594,
		972347
	};

	const char* ficheros[] = {
		"els19",
		"chr20a",
		"chr25a",
		"nug25",
		"bur26a",
		"bur26b",
		"tai30a",
		"tai30b",
		"esc32a",
		"kra32",
		"tai35a",
		"tai35b",
		"tho40",
		"tai40a",
		"sko42",
		"sko49",
		"tai50a",
		"tai50b",
		"tai60a",
		"lipa90a"
	};
	
	int semilla = 0;
	int fichero = 0;
	int algoritmo = 0;
	int tipoAlg = 0;
	int hibridacion = 0;
	
	int inicioFichero = 0;
	int inicioSemilla = 0;
	int inicioAlgoritmo = 0;
	int inicioTipo = 0;
	int inicioHibridacion = 0;

	int finFichero = numFicheros;
	int finSemilla = numSemillas;
	int finAlgoritmo = numAlgoritmos;
	int finTipo = numTipos;
	int finHibridacion = numHibridaciones;

	char* nombresAlgoritmos[] = {
		"Algoritmo memético"
	};
	
	char* tipoAlgoritmo[] = {
		"Cruce por posicion",
		"Cruce PMX"
	};

	char* hibridaciones[] = {
		"(10, 1.0)",
		"(10, 0.1)",
		"(10, 0.1 mejores)"
	};

	Algoritmo* algoritmos[] = {
		new AlgoritmoMemetico()
	};

	semilla = seleccionarSemilla(semillas, numSemillas);
	fichero = seleccionarFichero(ficheros, numFicheros);
	//algoritmo = seleccionarAlgoritmo((const char**)nombresAlgoritmos, numAlgoritmos);
	algoritmo = -1;
	tipoAlg = seleccionarTipoAlgoritmo((const char**)tipoAlgoritmo, numTipos);
	hibridacion = seleccionarHibridacion((const char**) hibridaciones, numHibridaciones);

	if (semilla != -1) { inicioSemilla = semilla; finSemilla = semilla + 1; }
	if (fichero != -1) { inicioFichero = fichero; finFichero = fichero + 1; }
	if (algoritmo != -1) { inicioAlgoritmo = algoritmo; finAlgoritmo = algoritmo + 1; }
	if (tipoAlg != -1) { inicioTipo = tipoAlg; finTipo = tipoAlg + 1; }
	if (hibridacion != -1) { inicioHibridacion = hibridacion; finHibridacion = hibridacion + 1; }

	for (int i = inicioAlgoritmo; i < finAlgoritmo; i++) {
		for (int l = inicioTipo; l < finTipo; l++) {
			for (int m = inicioHibridacion; m < finHibridacion; m++) {
				ofstream outputFile;
				string	 outputName("resultados/");
				outputName += nombresAlgoritmos[i];
				outputName += " _ ";
				outputName += tipoAlgoritmo[l];
				outputName += " _ ";
				outputName += hibridaciones[m];
				outputName += ".csv";
				outputFile.open(outputName.c_str(), ios::out);
				for (int j = inicioFichero; j < finFichero; j++) {
//					system("cls");
					cout << nombresAlgoritmos[i] <<" | "<< tipoAlgoritmo[l] << " | " << hibridaciones[m] << " | " << ficheros[j];

					float mediaTiempoEjecucion = 0;
					long double mediaValorSolucion = 0;

					if (semilla == -1) {
						cout << endl << endl;

						for (int k = inicioSemilla; k < finSemilla; k++) {
							cout << "Semilla:\t\t" << semillas[k] << endl;
							ejecutar(semillas[k], ficheros[j], algoritmos[i], l, m, &qap);
							mediaTiempoEjecucion += algoritmos[i]->getTiempoEjecucion() / numSemillas;
							mediaValorSolucion += algoritmos[i]->getValorSolucion() / numSemillas;
							cout << endl;
						}

						cout << endl
							<< "Algoritmo:\t" << nombresAlgoritmos[i] <<" "<<tipoAlgoritmo[l]<< endl
							<< "Fichero:\t" << ficheros[j] << endl
							<< "Tiempo medio:\t" << (mediaTiempoEjecucion) << "s" << endl
							<< "Valor medio:\t" << (int)(mediaValorSolucion) << endl;

					} else {
						cout << " | " << semilla << endl;
						ejecutar(semilla, ficheros[j], algoritmos[i], l, m, &qap);
						mediaTiempoEjecucion = algoritmos[i]->getTiempoEjecucion();
						mediaValorSolucion = algoritmos[i]->getValorSolucion();
					}

					outputFile
						<< ficheros[j] << ";"
						<< (int)(mediaValorSolucion) << ";"
						<< (mediaTiempoEjecucion) << endl;

					cout << endl;
					//system("pause");
				}
		

				outputFile.close();
			}
		}
	}

	return 0;
}
