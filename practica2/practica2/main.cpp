#include <iostream>
using namespace std;

#include "QAP.h"
#include "GRASP.h"
#include "ILS.h"

void cargarFichero (int fichero, QAP& qap) {
	switch(fichero){
		case 1: qap.abrir("ficheros/bur26a.dat"); break;
		case 2: qap.abrir("ficheros/bur26b.dat"); break;
		case 3: qap.abrir("ficheros/chr20a.dat"); break;
		case 4: qap.abrir("ficheros/chr25a.dat"); break;
		case 5: qap.abrir("ficheros/els19.dat"); break;
		case 6: qap.abrir("ficheros/esc32a.dat"); break;
		case 7: qap.abrir("ficheros/kra32.dat"); break;
		case 8: qap.abrir("ficheros/lipa90a.dat"); break;
		case 9: qap.abrir("ficheros/nug25.dat"); break;
		case 10: qap.abrir("ficheros/sko42.dat"); break;
		case 11: qap.abrir("ficheros/sko49.dat"); break;
		case 12: qap.abrir("ficheros/tai30a.dat"); break;
		case 13: qap.abrir("ficheros/tai30b.dat"); break;
		case 14: qap.abrir("ficheros/tai35a.dat"); break;
		case 15: qap.abrir("ficheros/tai35b.dat"); break;
		case 16: qap.abrir("ficheros/tai40a.dat"); break;
		case 17: qap.abrir("ficheros/tai50a.dat"); break;
		case 18: qap.abrir("ficheros/tai50b.dat"); break;
		case 19: qap.abrir("ficheros/tai60a.dat"); break;
		case 20: qap.abrir("ficheros/tho40.dat"); break;
	}
}

int main () {
	QAP qap;
	int semilla;
	int algoritmo;
	int fichero;

	// Paso 1: semilla
	cout << "Semilla: ";
	cin >> semilla;
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

	if (fichero == 0) {
		for (int i = 1; i <= 20; i++) {
			cout << endl << "Fichero " << i << endl;
			cargarFichero(i, qap);
			if (algoritmo == 0 || algoritmo == 1) {
				cout << "Algoritmo GRASP" << endl;
				GRASP grasp(qap, semilla);
			}
			if (algoritmo == 0 || algoritmo == 2) {
				cout << "Algoritmo ILS" << endl;
				ILS ils(qap, semilla);
			}
		}
	} else {
		cargarFichero(fichero, qap);
		if (algoritmo == 0 || algoritmo == 1) {
			cout << "Algoritmo GRASP" << endl;
			GRASP grasp(qap, semilla);
		}
		if (algoritmo == 0 || algoritmo == 2) {
			cout << "Algoritmo ILS" << endl;
			ILS ils(qap, semilla);
		}
	}

	system("pause");
	return 0;
}
