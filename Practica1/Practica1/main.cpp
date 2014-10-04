/*
@authors: Pablo Molina Gonzalez y Diego Alberto Pérez Ortega
*/


#include <cstdlib>
#include <iostream>
#include "QAP.h"
#include "Permutacion.h"

using namespace std;

/*
 * 
 */

//Menú para la lectura de ficheros
int menuFichero(){
    int val = 0;
	cout<<endl;
    cout<<"Escoja el fichero a leer"<<endl;
    cout<<"1. bur26a"<<endl;
    cout<<"2. bur26b"<<endl;
    cout<<"3. chr20a"<<endl;
    cout<<"4. chr25a"<<endl;
    cout<<"5. els19"<<endl;
    cout<<"6. esc32a"<<endl;
    cout<<"7. kra32"<<endl;
    cout<<"8. lipa90a"<<endl;
    cout<<"9. nug25"<<endl;
    cout<<"10. sko42"<<endl;
    cout<<"11. sko49"<<endl;
    cout<<"12. tai30a"<<endl;
    cout<<"13. tai30b"<<endl;
    cout<<"14. tai35a"<<endl;
    cout<<"15. tai35b"<<endl;
    cout<<"16. tai40a"<<endl;
    cout<<"17. tai50a"<<endl;
    cout<<"18. tai50b"<<endl;
    cout<<"19. tai60a"<<endl;
    cout<<"20. tho40"<<endl;    
    cout<<"21. salir"<<endl;
    do{
        cin>>val;
    }while (val < 1 || val > 21);
    
    return val;
}

//Menú para seleccionar el algoritmo que se desea ejecutar
int menuAlgoritmo(){
	int val = 0;
	cout<<endl;
	cout<<"Selecciona el algoritmo que deseas usar"<<endl;
	cout<<"1. Busqueda local"<<endl;
	cout<<"2. Busqueda tabu"<<endl;
    do{
        cin>>val;
    }while (val < 1 || val > 2);
    
    return val;
}

//Método que carga el fichero seleccionado
void cargarFich(int valor,QAP &fichero){
    switch(valor){
        case 1:
            fichero.abrir("ficheros/bur26a.dat");
            break;
        case 2:
            fichero.abrir("ficheros/bur26b.dat");
            break;
        case 3:
            fichero.abrir("ficheros/chr20a.dat");
            break;
        case 4:
            fichero.abrir("ficheros/chr25a.dat");
            break;
        case 5:
            fichero.abrir("ficheros/els19.dat");
            break;
        case 6:
            fichero.abrir("ficheros/esc32a.dat");
            break;
        case 7:
            fichero.abrir("ficheros/kra32.dat");
            break;
        case 8:
            fichero.abrir("ficheros/lipa90a.dat");
            break;
        case 9:
            fichero.abrir("ficheros/nug25.dat");
            break;
        case 10:
            fichero.abrir("ficheros/sko42.dat");
            break;
        case 11:
            fichero.abrir("ficheros/sko49.dat");
            break;
        case 12:
            fichero.abrir("ficheros/tai30a.dat");
            break;
        case 13:
            fichero.abrir("ficheros/tai30b.dat");
            break;
        case 14:
            fichero.abrir("ficheros/tai35a.dat");
            break;
        case 15:
            fichero.abrir("ficheros/tai35b.dat");
            break;
        case 16:
            fichero.abrir("ficheros/tai40a.dat");
            break;
        case 17:
            fichero.abrir("ficheros/tai50a.dat");
            break;
        case 18:
            fichero.abrir("ficheros/tai50b.dat");
            break;
        case 19:
            fichero.abrir("ficheros/tai60a.dat");
            break;
        case 20:
            fichero.abrir("ficheros/tho40.dat");
            break;
        case 21:
            system("EXIT");
    }
}




int main(int argc, char** argv) {
	int semilla = 0;
	cout<<"Introduzca la semilla ";
	cin>>semilla;
    int val = menuFichero();
    QAP fichero;
	cargarFich(val,fichero);
	int algoritmo = menuAlgoritmo();
	Permutacion permuta(fichero.getNumComp());
	permuta.solInicial(semilla);


	//fichero.imprimirMatrizDistancia();
	system("PAUSE");
    return 0;
}
