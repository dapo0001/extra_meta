#include <iostream>
using namespace std;

#include "QAP.h"
#include "GRASP.h"
#include "ILS.h"

void cargarFichero (int fichero, QAP& qap) {
	switch(fichero){
		case 1: cout << "(bur26a)" << endl; qap.abrir("ficheros/bur26a.dat"); break;
		case 2: cout << "(bur26b)" << endl; qap.abrir("ficheros/bur26b.dat"); break;
		case 3: cout << "(chr20a)" << endl; qap.abrir("ficheros/chr20a.dat"); break;
		case 4: cout << "(chr25a)" << endl; qap.abrir("ficheros/chr25a.dat"); break;
		case 5: cout << "(els19)" << endl; qap.abrir("ficheros/els19.dat"); break;
		case 6: cout << "(esc32a)" << endl; qap.abrir("ficheros/esc32a.dat"); break;
		case 7: cout << "(kra32)" << endl; qap.abrir("ficheros/kra32.dat"); break;
		case 8: cout << "(lipa90a)" << endl; qap.abrir("ficheros/lipa90a.dat"); break;
		case 9: cout << "(nug25)" << endl; qap.abrir("ficheros/nug25.dat"); break;
		case 10: cout << "(sko42)" << endl; qap.abrir("ficheros/sko42.dat"); break;
		case 11: cout << "(sko49)" << endl; qap.abrir("ficheros/sko49.dat"); break;
		case 12: cout << "(tai30a)" << endl; qap.abrir("ficheros/tai30a.dat"); break;
		case 13: cout << "(tai30b)" << endl; qap.abrir("ficheros/tai30b.dat"); break;
		case 14: cout << "(tai35a)" << endl; qap.abrir("ficheros/tai35a.dat"); break;
		case 15: cout << "(tai35b)" << endl; qap.abrir("ficheros/tai35b.dat"); break;
		case 16: cout << "(tai40a)" << endl; qap.abrir("ficheros/tai40a.dat"); break;
		case 17: cout << "(tai50a)" << endl; qap.abrir("ficheros/tai50a.dat"); break;
		case 18: cout << "(tai50b)" << endl; qap.abrir("ficheros/tai50b.dat"); break;
		case 19: cout << "(tai60a)" << endl; qap.abrir("ficheros/tai60a.dat"); break;
		case 20: cout << "(tho40)" << endl; qap.abrir("ficheros/tho40.dat"); break;
	}
}

int main () {
	QAP qap;
	int semilla;
	int algoritmo;
	int fichero;

	const int numSemillas = 25;
	int semillas[numSemillas];
	float mediaTiempoEjecucion = 0;
	long int mediaValorSolucion = 0;

	semillas[0] = 5538;
	semillas[1] = 912373;
	semillas[2] = 984359;
	semillas[3] = 1923312;
	semillas[4] = 7891237;
	semillas[5] = 7129323;
	semillas[6] = 870345;
	semillas[7] = 123784;
	semillas[8] = 49785;
	semillas[9] = 983495;
	semillas[10] = 89454;
	semillas[11] = 47895;
	semillas[12] = 34;
	semillas[13] = 12398;
	semillas[14] = 349834;
	semillas[15] = 12393;
	semillas[16] = 34983;
	semillas[17] = 23832;
	semillas[18] = 12398;
	semillas[19] = 12093;
	semillas[20] = 8540;
	semillas[21] = 934;
	semillas[22] = 2;
	semillas[23] = 12323;
	semillas[24] = 4592;

	// Paso 1: semilla
	cout << "Semilla (-1 para usar las " << numSemillas << " predeterminadas): ";
	cin >> semilla;
	if (semilla != -1) { srand(semilla); }
	cout << endl;

	// Paso 2: algoritmo
	cout << "Algoritmo: " << endl
		<< "1. GRASP" << endl
		<< "2. ILS" << endl
		<< "0. Todos" << endl;
	cin >> algoritmo;

	// Paso 3: ficheros
	cout << endl << "Fichero: " << endl
		<< "1. bur26a" << endl
		<< "2. bur26b" << endl
		<< "3. chr20a" << endl
		<< "4. chr25a" << endl
		<< "5. els19" << endl
		<< "6. esc32a" << endl
		<< "7. kra32" << endl
		<< "8. lipa90a" << endl
		<< "9. nug25" << endl
		<< "10. sko42" << endl
		<< "11. sko49" << endl
		<< "12. tai30a" << endl
		<< "13. tai30b" << endl
		<< "14. tai35a" << endl
		<< "15. tai35b" << endl
		<< "16. tai40a" << endl
		<< "17. tai50a" << endl
		<< "18. tai50b" << endl
		<< "19. tai60a" << endl
		<< "20. tho40" << endl
		<< "0. Todos" << endl;
	cin >> fichero;
	cout << endl;

	if (semilla == -1) {
		for (int j = 0; j < numSemillas; j++) {
			srand(semillas[j]);
			cout <<endl << "---- Semilla " << semillas[j] << " ----" << endl;
			if (fichero == 0) {
				for (int i = 1; i <= 20; i++) {
					cout << endl << "-- Fichero " << i << " ";
					cargarFichero(i, qap);
					if (algoritmo == 0 || algoritmo == 1) {
						cout << "Algoritmo GRASP" << endl;
						GRASP grasp(qap, semillas[j]);
						cout << endl;
					}
					if (algoritmo == 0 || algoritmo == 2) {
						cout << "Algoritmo ILS" << endl;
						ILS ils(qap, semillas[j]);
						cout << endl;
					}
				}
				system("pause");
				system("cls");
			} else {
				cargarFichero(fichero, qap);
				if (algoritmo == 0 || algoritmo == 1) {
					cout << "Algoritmo GRASP" << endl;
					GRASP grasp(qap, semillas[j]);
					cout << endl;
				}
				if (algoritmo == 0 || algoritmo == 2) {
					cout << "Algoritmo ILS" << endl;
					ILS ils(qap, semillas[j]);

					mediaTiempoEjecucion += ils.getTiempoEjecucion();
					mediaValorSolucion += ils.getValorSolucion();
					cout << endl;
				}
			}
		}

		cout << "Media tiempo ejecucion: " << mediaTiempoEjecucion / numSemillas << endl;
		cout << "Media valor solución: " << mediaValorSolucion / numSemillas << endl;

	} else {
		if (fichero == 0) {
			for (int i = 1; i <= 20; i++) {
				cout << endl << "-- Fichero " << i << " ";
				cargarFichero(i, qap);
				if (algoritmo == 0 || algoritmo == 1) {
					cout << "Algoritmo GRASP" << endl;
					GRASP grasp(qap, semilla);
					cout << endl;
				}
				if (algoritmo == 0 || algoritmo == 2) {
					cout << "Algoritmo ILS" << endl;
					ILS ils(qap, semilla);
					cout << endl;
				}
			}
		} else {
			cargarFichero(fichero, qap);
			if (algoritmo == 0 || algoritmo == 1) {
				cout << "Algoritmo GRASP" << endl;
				GRASP grasp(qap, semilla);
				cout << endl;
			}
			if (algoritmo == 0 || algoritmo == 2) {
				cout << "Algoritmo ILS" << endl;
				ILS ils(qap, semilla);
				cout << endl;
			}
		}
	}

	system("pause");
	return 0;
}
