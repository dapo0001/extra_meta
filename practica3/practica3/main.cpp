#include <iostream>
#include <fstream>
using namespace std;

#include "QAP.h"
#include "Algoritmo.h"
#include "AlgoritmoGeneticoGeneracional.h"
#include "AlgoritmoGeneticoEstacionario.h"

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

	const int numAlgoritmos = 2;
	int algoritmo = 0;
	int inicioAlgoritmo = 0;
	int finAlgoritmo = numAlgoritmos;
	char* nombresAlgoritmos[] = {
		"Algoritmo genético generacional",
		"Algoritmo genético estacionario"
	};
	Algoritmo* algoritmos[] = {
		new AlgoritmoGeneticoGeneracional(),
		new AlgoritmoGeneticoEstacionario()
	};

	semilla = seleccionarSemilla(semillas, numSemillas);
	if (semilla != -1) { inicioSemilla = semilla; finSemilla = semilla + 1; }
	fichero = seleccionarFichero(ficheros, numFicheros);
	if (fichero != -1) { inicioFichero = fichero; finFichero = fichero + 1; }
	algoritmo = seleccionarAlgoritmo((const char**)nombresAlgoritmos, numAlgoritmos);
	if (algoritmo != -1) { inicioAlgoritmo = algoritmo; finAlgoritmo = algoritmo + 1; }

	for (int i = inicioAlgoritmo; i < finAlgoritmo; i++) {
		ofstream outputFile;
		string	 outputName("resultados/");
		outputName += nombresAlgoritmos[i];
		outputName += ".csv";
		outputFile.open(outputName, ios::out);

		for (int j = inicioFichero; j < finFichero; j++) {
			system("cls");
			cout << nombresAlgoritmos[i] << " | " << ficheros[j];

			float mediaTiempoEjecucion = 0;
			long double mediaValorSolucion = 0;

			if (semilla == -1) {
				cout << endl << endl;

				for (int k = inicioSemilla; k < finSemilla; k++) {
					cout << semillas[k] << endl;

					ejecutar(semillas[k], ficheros[j], algoritmos[i], &qap);
					mediaTiempoEjecucion += algoritmos[i]->getTiempoEjecucion() / numSemillas;
					mediaValorSolucion += algoritmos[i]->getValorSolucion() / numSemillas;

					cout << endl;
				}

				cout << endl
					<< "Algoritmo: " << nombresAlgoritmos[i] << endl
					<< "Fichero: " << ficheros[j] << endl
					<< "Tiempo medio: " << (mediaTiempoEjecucion) << "s" << endl
					<< "Valor medio: " << (int)(mediaValorSolucion) << endl;

			} else {
				cout << " | " << semilla << endl;
				ejecutar(semilla, ficheros[j], algoritmos[i], &qap);
				mediaTiempoEjecucion = algoritmos[i]->getTiempoEjecucion();
				mediaValorSolucion = algoritmos[i]->getValorSolucion();
			}

			outputFile
				<< ficheros[j] << ";"
				<< (int)(mediaValorSolucion) << ";"
				<< (mediaTiempoEjecucion) << endl;

			cout << endl;
			system("pause");
		}

		outputFile.close();
	}

	return 0;
}
