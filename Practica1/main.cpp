/* 
 * File:   main.cpp
 * Author: DiegoAlberto
 *
 * Created on 1 de octubre de 2014, 17:23
 */

#include <cstdlib>
#include <iostream>
#include "CargaFichero.h"

using namespace std;

/*
 * 
 */


int menuFichero(){
    int val = 0;
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

CargaFichero cargarFich(int valor){
    CargaFichero fich;
    switch(valor){
        case 1:
            fich.abrir("ficheros/bur26a.dat");
            break;
        case 2:
            fich.abrir("ficheros/bur26b.dat");
            break;
        case 3:
            fich.abrir("ficheros/chr20a.dat");
            break;
        case 4:
            fich.abrir("ficheros/chr25a.dat");
            break;
        case 5:
            fich.abrir("ficheros/els19.dat");
            break;
        case 6:
            fich.abrir("ficheros/esc32a.dat");
            break;
        case 7:
            fich.abrir("ficheros/kra32.dat");
            break;
        case 8:
            fich.abrir("ficheros/lipa90a.dat");
            break;
        case 9:
            fich.abrir("ficheros/nug25.dat");
            break;
        case 10:
            fich.abrir("ficheros/sko42.dat");
            break;
        case 11:
            fich.abrir("ficheros/sko49.dat");
            break;
        case 12:
            fich.abrir("ficheros/tai30a.dat");
            break;
        case 13:
            fich.abrir("ficheros/tai30b.dat");
            break;
        case 14:
            fich.abrir("ficheros/tai35a.dat");
            break;
        case 15:
            fich.abrir("ficheros/tai35b.dat");
            break;
        case 16:
            fich.abrir("ficheros/tai40a.dat");
            break;
        case 17:
            fich.abrir("ficheros/tai50a.dat");
            break;
        case 18:
            fich.abrir("ficheros/tai50b.dat");
            break;
        case 19:
            fich.abrir("ficheros/tai60a.dat");
            break;
        case 20:
            fich.abrir("ficheros/tho40.dat");
            break;
        case 21:
            system("EXIT");
    }
    return fich;
}




int main(int argc, char** argv) {
    int val = menuFichero();
    cargarFich(val);
    return 0;
}

