#include <iostream>
using namespace std;

#include "QAP.h"
#include "Algoritmo.h"
#include "GRASP.h"
#include "ILS.h"

int seleccionarSemilla (const int semillas[], const int numSemillas) {
	int semilla;
	do {
		cout << "Selecciona una semilla: ";
		cin >> semilla;
	} while (semilla < -1);

	return semilla;
}

int seleccionarFichero (const char* ficheros[], const int numFicheros) {
	int fichero;
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
	int algoritmo;
	do {
		cout << "Selecciona un algoritmo:" << endl;
		for (int i = 0; i < numAlgoritmos; i++) {
			cout << "  " << i << ". " << nombresAlgoritmos[i] << endl;
		}
		cin >> algoritmo;
	} while (algoritmo < -1 || algoritmo >= numAlgoritmos);
	return algoritmo;
}

void ejecutar (int semilla, const char* fichero, Algoritmo* algoritmo, QAP* qap) {
	qap->abrir(("ficheros/" + string(fichero) + ".dat").c_str());
	algoritmo->ejecutar(*qap, semilla);
}

int main () {
	QAP qap;

	const int numSemillas = 25;
	int semilla = 0;
	int inicioSemilla = 0;
	int finSemilla = numSemillas;
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
		34,
		12398,
		349834,
		12393,
		34983,
		23832,
		12398,
		12093,
		8540,
		934,
		2,
		12323,
		4592
	};

	const int numFicheros = 20;
	int fichero = 0;
	int inicioFichero = 0;
	int finFichero = numFicheros;
	const char* ficheros[] = {
		"bur26a",
		"bur26b",
		"chr20a",
		"chr25a",
		"els19",
		"esc32a",
		"kra32",
		"lipa90a",
		"nug25",
		"sko42",
		"sko49",
		"tai30a",
		"tai30b",
		"tai35a",
		"tai35b",
		"tai40a",
		"tai50a",
		"tai50b",
		"tai60a",
		"tho40"
	};

	const int numAlgoritmos = 2;
	int algoritmo = 0;
	int inicioAlgoritmo = 0;
	int finAlgoritmo = numAlgoritmos;
	char* nombresAlgoritmos[] = {
		"ILS",
		"GRASP"
	};
	Algoritmo* algoritmos[] = {
		new ILS(),
		new GRASP()
	};

	semilla = seleccionarSemilla(semillas, numSemillas);
	if (semilla != -1) { inicioSemilla = semilla; finSemilla = semilla + 1; }
	fichero = seleccionarFichero(ficheros, numFicheros);
	if (fichero != -1) { inicioFichero = fichero; finFichero = fichero + 1; }
	algoritmo = seleccionarAlgoritmo((const char**)nombresAlgoritmos, numAlgoritmos);
	if (algoritmo != -1) { inicioAlgoritmo = algoritmo; finAlgoritmo = algoritmo + 1; }

	for (int i = inicioFichero; i < finFichero; i++) {
		for (int j = inicioAlgoritmo; j < finAlgoritmo; j++) {
			system("cls");
			cout << nombresAlgoritmos[j] << " | " << ficheros[i];

			if (semilla == -1) {
				cout << endl << endl;

				float mediaTiempoEjecucion = 0;
				int mediaValorSolucion = 0;

				for (int k = inicioSemilla; k < finSemilla; k++) {
					cout << semillas[k] << endl;

					ejecutar(semillas[k], ficheros[i], algoritmos[j], &qap);
					mediaTiempoEjecucion += algoritmos[j]->getTiempoEjecucion();
					mediaValorSolucion += algoritmos[j]->getValorSolucion();

					cout << endl;
				}

				cout << endl
					<< "Algoritmo: " << nombresAlgoritmos[j] << endl
					<< "Fichero: " << ficheros[j] << endl
					<< "Tiempo medio: " << (mediaTiempoEjecucion / numSemillas) << "s" << endl
					<< "Valor medio: " << (mediaValorSolucion / numSemillas) << endl;
			} else {
				cout << " | " << semilla << endl;
				ejecutar(semilla, ficheros[i], algoritmos[j], &qap);
			}

			cout << endl;
			system("pause");
		}
	}

	return 0;
}
