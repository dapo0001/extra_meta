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
	int semillas[25];

	semillas[0] = 0;
	semillas[1] = 1;
	semillas[2] = 2;
	semillas[3] = 3;
	semillas[4] = 4;
	semillas[5] = 5;
	semillas[6] = 6;
	semillas[7] = 7;
	semillas[8] = 8;
	semillas[9] = 9;
	semillas[10] = 10;
	semillas[11] = 11;
	semillas[12] = 12;
	semillas[13] = 13;
	semillas[14] = 14;
	semillas[15] = 15;
	semillas[16] = 16;
	semillas[17] = 17;
	semillas[18] = 18;
	semillas[19] = 19;
	semillas[20] = 20;
	semillas[21] = 21;
	semillas[22] = 22;
	semillas[23] = 23;
	semillas[24] = 24;

	// Paso 1: semilla
	cout << "Semilla (-1 para usar las 25 predeterminadas): ";
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
		for (int j = 0; j < 25; j++) {
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
					cout << endl;
				}
			}
		}

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
