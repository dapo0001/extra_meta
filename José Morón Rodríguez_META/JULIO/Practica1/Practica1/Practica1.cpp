// Practica1.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <list>
#include <ctime>

using namespace std;

//Constantes
const int breast=9;
const int yeast=8;
const int r15=2;

const int c_breast=2;
const int c_yeast=10;
const int c_r15=15;



//Variables globales
int tam_elemnto=0;
int tam_cluster=0;
vector<double *> elementos;
vector<double *> centroides;
vector<int> P;
vector<int> tams_clusters;
double solucion;
int semillas[]={77349558,73495587,34955877,49558773,95587734};//array de semillas

//Funciones
bool cargarFichero (string nombre);
void solInicial();
double incremento_J(double *elemento, int Ci, int Cj);
double calcular_dist(double* elem, double* centroide);
void factorizar(double* elem, int Ci, int Cj);
void busquedaLocal();
void grasp();
void solucion_greedy();
void imprime_Centroides();
void calcula_centroides();
void algoritmo_BT();
pair<int, bool> algoritmo_BL();
void kmedias();

int main(int argc, char* argv[]){
	clock_t start;
	double duracion=0;
	string conjuntoDatos="";
	string algoritmoElegido="";
	int posSemilla=0;
	bool salir=false;
	while (!salir){
		int opcion=0;
		system("CLS");
		int semilla=0;
		if (!salir){
			cout<<"Que semilla desea utilizar: "<<endl;
			cout<<"1.- 77349558"<<endl;
			cout<<"2.- 73495587"<<endl;
			cout<<"3.- 34955877"<<endl;
			cout<<"4.- 49558773"<<endl;
			cout<<"5.- 95587734"<<endl;
			cout<<"6.- Salir"<<endl;
			opcion=0;
			while (opcion<1||opcion>6) cin>>opcion;
			posSemilla=opcion-1;
			if (opcion==6) salir=true;
		}
		if (!salir){
			opcion=0;
			cout<<"Que fichero desea cargar: "<<endl;
			cout<<"1.- Breast"<<endl;
			cout<<"2.- R15: "<<endl;
			cout<<"3.- Yeas"<<endl;
			cout<<"4.- Salir "<<endl;		
			while (opcion<1||opcion>4) cin>>opcion;
			switch (opcion){
			case 1:
				tam_elemnto=breast;
				tam_cluster=c_breast;
				cargarFichero("breast.txt");
				conjuntoDatos="Breast";
				break;
			case 3:
				tam_elemnto=yeast;
				tam_cluster=c_yeast;
				cargarFichero("yeast.txt");
				conjuntoDatos="Yeast";
				break;
			case 2:
				tam_elemnto=r15;
				tam_cluster=c_r15;
				cargarFichero("R15-modificado.txt");
				conjuntoDatos="R15";
				break;
			default:
				salir=true;
				break;
			}
		}
		if (!salir){
			cout<<"Que algoritmo desea usar: "<<endl;
			cout<<"1.- Busqueda Local"<<endl;
			cout<<"2.- Busqueda Tabu: "<<endl;
			cout<<"3.- GRASP"<<endl;
			cout<<"4.- Kmedias"<<endl;
			cout<<"5.- Salir "<<endl;
			opcion=0;
			while (opcion<1||opcion>4) cin>>opcion;
			srand(semillas[posSemilla]);
			start=clock();
			switch (opcion){
			case 1:
				algoritmoElegido="Busqueda Local";
				busquedaLocal();
				break;
			case 2:
				algoritmoElegido="Busqueda Tabu";
				solInicial();
				algoritmo_BT();
				break;
			case 3:
				algoritmoElegido="Busqueda Grasp";
				grasp();
				break;
			case 4:
				algoritmoElegido="K-Medias";
				kmedias();
				break;
			case 5:
				salir=true;
				break;
			default:
				break;
			}
			duracion=(clock()-start)/(double)CLOCKS_PER_SEC;
			cout<<"Semilla Elegida: "<<semillas[posSemilla]<<endl;
			cout<<"Conjunto de Datos Elegido: "<<conjuntoDatos<<endl;
			cout<<"Algoritmo Elegido: "<<algoritmoElegido<<endl;
			cout<<"Solucion Final: "<<solucion<<endl;
			cout<<"Tiempo necesario: "<<duracion<<"s"<<endl;
			system("PAUSE");
		}
	}
	return 0;
}

void imprime_Centroides(){
	for (int i=0; i<centroides.size(); i++){
		cout<<"Centroide "<<i<<":"<<endl;
		double* centro=centroides[i];
		for (int j=0; j<tam_elemnto; j++){
			cout<<centro[j]<<" ";
		}
		cout<<endl;
	}
}
void solInicial(){
	
	//int* num_elem=new int[tam_cluster];
	tams_clusters.clear();
	for (int i=0; i<tam_cluster; i++){
		//num_elem[i]=0;
		tams_clusters.push_back(0);
	}
	P.clear();
	for (int i=0; i<elementos.size(); i++){
		P.push_back(0);
	}
	for (int i=0; i<elementos.size(); i++){
		int al=rand()%tam_cluster;
		P[i]=al;
		//num_elem[al]++;
		tams_clusters[al]++;
	}
	calcula_centroides();
	
}
void calcula_centroides(){
	//Calculamos los centroides
	centroides.clear();
	tams_clusters.clear();
	for (int i=0; i<tam_cluster; i++){
		double* centro=new double[tam_elemnto];
		for (int j=0; j<tam_elemnto; j++){
			centro[j]=0;
		}
		centroides.push_back(centro);
		tams_clusters.push_back(0);
	}
	for (int i=0; i<elementos.size(); i++){
		double* elem=elementos[i];
		int cluster=P[i];
		double *centro=centroides[cluster];
		for (int j=0; j<tam_elemnto; j++){
			centro[j]=centro[j]+elem[j];
		}
		centroides[cluster]=centro;
		tams_clusters[cluster]++;
		
	}
	for (int i=0; i<tam_cluster; i++){
		double* centro=centroides[i];
		for (int j=0; j<tam_elemnto; j++){
			centro[j]=(centro[j]/(double)tams_clusters[i]);
		}
		centroides[i]=centro;
	}
	solucion=0;
	for (int i=0; i<elementos.size(); i++){
		double distancia=calcular_dist(elementos[i], centroides[P[i]]);
		solucion=solucion+pow(distancia,2);
	}
}
bool cargarFichero(string nombre){
	cout<<"Cargando fichero: "<<nombre<<endl;
	ifstream fich;	
    fich.open(nombre);
	elementos.clear();
	int numElem=0;
    if (fich) {
        while (!fich.eof()) {
			double* f=new double[tam_elemnto];
            for (int i=0; i<tam_elemnto; i++){
				float aux=0;
                fich>>aux;
				f[i]=aux;
            }
			elementos.push_back(f);
			numElem++;
        }
		fich.close();
		cout<<"FICHERO CARGADO CON EXITO"<<endl;
		return	true;
	}else{
		cout<<"NO SE PUEDE ABRIR EL FICHERO"<<endl;
		return false;
	}
}

double incremento_J(double *elemento, int Ci, int Cj){
	//TAMAÑO DE LOS CLUSTER
	int mi=tams_clusters[Ci];
	int mj=tams_clusters[Cj];
	
	double disi=pow(calcular_dist(elemento, centroides[Ci]),2);
	double disj=pow(calcular_dist(elemento, centroides[Cj]),2);

	double incr_j=(((double)mj/(double)(mj+1))*disj)-(((double)mi/(double)(mi-1))*disi);
	//cout<<"Incre J "<<incr_j<<endl;
	return incr_j;
}

double calcular_dist(double* elem, double* centroide){
	double dist=0;
	for (int i=0; i<tam_elemnto; i++){
		dist=dist+((centroide[i]-elem[i])*(centroide[i]-elem[i]));
	}
	dist=sqrt(dist);
	return dist;
}

void factorizar(double* elem, int Ci, int Cj){
	//TAMAÑO DE LOS CLUSTER
	int mi=tams_clusters[Ci];
	int mj=tams_clusters[Cj];
	double* zi=centroides[Ci];
	double* zj=centroides[Cj];
	for (int i=0; i<tam_elemnto; i++){
		zi[i]= ((mi*zi[i])-elem[i])/(double)(mi-1);
		zj[i]= ((mj*zj[i])+elem[i])/(double)(mj+1);
	}
	tams_clusters[Ci]--;
	tams_clusters[Cj]++;
	
}
pair<int, bool> algoritmo_BL(){
	pair<int, bool> sol;
	sol.first=0;
	sol.second=false;
	for (int i=0; i<elementos.size(); i++){
		double *elem_i=elementos[i];
		int Ci=P[i];
		sol.second=false;
		sol.first++;
		for (int j=0; ((j<tam_cluster)&&(!sol.second)); j++){
			if (j!=Ci){
				double incrJ=incremento_J(elem_i,Ci,j);
				if (incrJ<0){
					factorizar(elem_i,Ci,j);
					sol.second=true;
					P[i]=j;
					solucion=solucion+incrJ;
				}
			}
		}
	}

	return sol;
}
void busquedaLocal(){
	int iteraciones=0;
	bool cambios=true;
	solInicial();
	while (cambios&&iteraciones<10000){
		pair<int, bool> BT=algoritmo_BL();
		cambios=BT.second;
		iteraciones+=BT.first;
	}

}


void solucion_greedy(){
	double* ganancias=new double[elementos.size()];//ARRAY CON LAS GANANCIAS DE LOS ELEMENTOS
	//ARRAY CON LA POSICION DE LOS ELEMENTOS SELECCIONADOS COMO CENTROIDES
	int* seleccionados=new int[tam_cluster];
	for (int i=0; i<tam_cluster; i++){
		seleccionados[i]=-1;
	}

	//INICIALIZAMOS LOS CENTROIDES A 0
	centroides.clear();
	for (int i=0; i<tam_cluster; i++){
		double* centro=new double[tam_elemnto];
		for (int j=0; j<tam_elemnto; j++){
			centro[j]=0;
		}
		centroides.push_back(centro);
	}
	double* media=new double[tam_elemnto];
	for (int j=0; j<tam_elemnto; j++){
			media[j]=0;
	}
	//SACAMOS LA MEDIA DE LOS ELEMENTOS
	
	for (int i=0; i<elementos.size(); i++){
		double* elem=elementos[i];
		for (int j=0; j<tam_elemnto; j++){
			media[j]+=elem[j];
		}
		
	}
	for (int j=0; j<tam_elemnto; j++){
		media[j]=media[j]/elementos.size();
	}
	//AVERIGUAMOS CUAL ES EL ELEMENTO MAS CENTRICO, EL QUE MAS SE ACERQUE A LA MEDIA.
	double dis_min=numeric_limits<double>::infinity();
	double* centro=new double[tam_elemnto];
	int pos=0;
	for (int i=0; i<elementos.size();i++){
		double distancia=calcular_dist(elementos[i],media);
		if (distancia<dis_min){
			centro=elementos[i];
			pos=i;
		}
	}
	centroides[0]=centro;
	seleccionados[0]=pos;
	for(int k=1; k<tam_cluster; k++){
		int i=0;
		double c_mejor=-numeric_limits<double>::infinity();
		double c_peor=numeric_limits<double>::infinity();
		//CALCULAMOS EL ARRAY DE GANANCIAS
		for (int i=0; i<elementos.size(); i++){
			//COMPROBAMOS QUE EL ELEMENTO i NO ESTE SELECCIONADO COMO CENTROIDE
			double* elem_i=elementos[i];
			bool seleccionado=false;
			for (int j=0; j<k; j++){
				if (seleccionados[j]==i) seleccionado=true;
			}
			if (seleccionado){
				ganancias[i]=numeric_limits<double>::infinity();
			}else{
				ganancias[i]=0;
				for (int j=0; j<elementos.size(); j++){
					seleccionado=false;
					for (int l=0; l<k; l++){
						if (seleccionados[l]==j) seleccionado=true;
					}
					if ((!seleccionado)&&i!=j){
						dis_min=numeric_limits<double>::infinity();
						//SACAMOS LA MINIMA DISTANCIA ENTRE EL ELEMENTO j Y LOS CENTROIDES SELECCIONADOS HASTA AHORA
						double* elem_j=elementos[j];
						for (int k2=0; k2<k; k2++){
							double dist_act=calcular_dist(elem_j, centroides[k2]);
							if (dist_act<dis_min){
								dis_min=dist_act;
							}
						}
						double valor=dis_min-calcular_dist(elem_i, elem_j);
						//SUMAMOS LOS Cij segun Cij=MAX(Dj-dji,0) DONDE:
						//Dj es la mimina distacina entre el elemento j y los centroides seleccionados hasta ahora
						//dji es la distancia entre el elemento j y el elemeno i al cuadrado
						if (valor>0){
							ganancias[i]+=valor;
						}
					}
				}
				if (ganancias[i]>c_mejor){//se elige el de mayor ganancia
					c_mejor=ganancias[i];
				}
				if (ganancias[i]<c_peor){//se elige el de peor ganancia
					c_peor=ganancias[i];
				}
			}
		}
		vector<int> LRC;
		double calidad=(c_mejor) -(0.3*(c_mejor-c_peor));
		for (int l=0; l<elementos.size(); l++){
			if (ganancias[l]!=numeric_limits<double>::infinity()){
				if (ganancias[l]>calidad){
					LRC.push_back(l);
				}
			}
		}
		int al=rand()%LRC.size();
		centroides[k]=elementos[LRC[al]];

	}
	//SELECCIONAMOS LOS ELEMENTO SEGUN SU CERCANIA A LOS CENTROIDES SELECCIONADOS
	P.clear();
	solucion=0;
	tams_clusters.clear();
	for (int k=0; k<tam_cluster; k++){
		tams_clusters.push_back(0);
	}
	for (int i=0; i<elementos.size(); i++){
		P.push_back(0);
	}
	for (int i=0; i<elementos.size();i++){
		dis_min=numeric_limits<double>::infinity();
		int cluster_sel=0;
		for (int k=0; k<tam_cluster; k++){
			double distancia=calcular_dist(elementos[i],centroides[k]);
			if (distancia<dis_min){
				dis_min=distancia;
				cluster_sel=k;
			}
		}
		P[i]=cluster_sel;
		tams_clusters[cluster_sel]++;
		solucion=solucion+pow(dis_min,1);
	}
	
}

void grasp(){
	int iteraGrasp=0;
	int iteraBT=0;
	bool terminar=false;
	double mejor_sol=999999;
	while(!terminar){
		solucion_greedy();
		//Recalculamos los centroides
		calcula_centroides();
		pair<int, bool> BT= algoritmo_BL();
		iteraBT+=BT.first;
		iteraGrasp++;
		if (solucion<mejor_sol){
			mejor_sol=solucion;
		}
		if (iteraGrasp>=25&&iteraBT>=10000){
			terminar=true;
		}
	}
	solucion=mejor_sol;
}

void algoritmo_BT(){
	/*
	DURANTE 10000 Iteraciones HACER{
		PARA CADA CLUSTER CON TAMAÑO MAYOR QUE 20{
			BUSCAR 20 MOVIMIENTOS DE UN ELEMENTO DEL Ci al Cj siendo Ci!=Cj{
				SE ACEPATARA LOS MOVIENTOS CON UNA PROBABILDAD DEL 5% EXCEPTO EN EL CASO DE QUE MEJORE LA SOLUCION MAS DE LO QUE HAY YA ELEGIDO.
				NO SE GUARDARA EN ARRAY LOS MOVIMIENTO SE VERAN SI MEJORAN LO CONSEGUIDO ACTUALMENTE
			} 
			ESCOJER LA MEJOR SOLUCION DEL VENCIDARIO, COMPROBAR QUE NO ESTE EN LA LISTA TABU.
			SI ESTA EN LA LISTA TABU Y SUPERA EL CRITERIO DE ASPIRACION HACER O NO ESTA EN LA LISTA TABU{
				INSERTAR EL PAR s (Numero de ELEMENTO) Y Ci en la lista TABU.
				REALIZAR EL MOVIMIENTO de s a Cj.
				Actualizar la matriz de frecuencias
				Aumentar el contador
			}
			//NOTA: EN EL CASO DE QUE ESTA EN LA LISTA TABU Y NO SUPERO EL CRITERO DE ASPIRACION ESE MOVIMENTO NO SE REALIZA YA QUE ES EL MEJOR DEL VENCINDARIO Y NO VA A MEJORAR LA SOLUCION. Y NINGUN OTRO MOVIENTO LO MEJORA
			SI CONTADOR REINICIO>2000{
				BORRAR LISTA TABU
				ALEATORIO DE 0-99;
				SI ALEATORIO<25 REINICIO ALEATORIO
				SI ALEATORIO>=25 Y ALEATORIO<50 REINICIO LA MEJOR SOLUCION
				SI ALEATORIO>=50 REINICIO A PARTIR DE LA MATRIZ DE FRECUENCIAS.
			}
		}
	
	
	}
	
	*/

	/*vector de vectores que guarda cada elemento en su cluster*/
	vector<vector <int> > cluster_elementos;
	for (int i=0; i<tam_cluster; i++){
		vector <int> v;
		cluster_elementos.push_back(v);
	}
	for (int i = 0; i < P.size(); i++){
		cluster_elementos[P[i]].push_back(i);
	}
	list<pair<int, int> > lista_tabu;
	int tam_LT=elementos.size()/3;
	int** matriz_frecuencias=new int*[elementos.size()];
	for (int i=0; i<elementos.size(); i++){
		matriz_frecuencias[i]=new int[tam_cluster];
		for(int j=0; j<tam_cluster; j++){
			if (P[i]==j){
				matriz_frecuencias[i][j]=1;
			}else{
				matriz_frecuencias[i][j]=0;
			}
		}
	}
	int contador=0;
	double mejor_solu=solucion;
	vector<int> copiaP=P;
	int contador_reinicio=0;
	while (contador<10000){
		for (int k=0; (k<tam_cluster); k++){
			if (cluster_elementos[k].size()>20){
				int veces=0;
				double mejorJ=9999999;
				int mejorCj=-1;
				int mejorElem=-1;
				int mejorPos=-1;
				while (veces<20){
					int posElemSelec=rand()%cluster_elementos[k].size();
					int elemSelec=cluster_elementos[k].at(posElemSelec);//SELECCIONAMOS ALEATORIAMENTE EL ELEMENTO DENTRO DEL CLUSTER k
					bool elegido=false;
					int clustSelec=-1;
					//ELEGIMOS EL CLUSTER Cj
					if (tam_cluster>2){
						while(!elegido){
							clustSelec=rand()%tam_cluster;
							if (clustSelec!=k){
								elegido=true;
							}
						}
					}else{
						clustSelec=0;
						if (k==0) clustSelec=1;
						elegido=true;
					}
					double* elem=elementos[elemSelec];
					double incrJ=incremento_J(elem,k,clustSelec);
					elegido=false;
					int aleatorio=rand()%100;
					if (aleatorio<5){
						veces++;
						if (incrJ<mejorJ){
							mejorElem=elemSelec;
							mejorCj=clustSelec;
							mejorPos=posElemSelec;
							mejorJ=incrJ;
							elegido=true;						
						}
					}
				}

				//MIRAMOS SI LA MEJOR SOLUCION DEL VENCIDARIO GENERADO ESTA EN LA LISTA TABU.
				bool tabu=false;
				list<pair<int, int>>::iterator it=lista_tabu.begin();
				while(it!=lista_tabu.end()){
					pair<int, int> elemLT=*it;
					if (elemLT.first==mejorElem&&elemLT.second==k){
						tabu=true;
						break;
					}
					it++;
				}
				bool seleccionado=true;
				if (tabu){
					if (mejorJ>0){
						seleccionado=false;
					}
				}
				if (seleccionado&&mejorElem>0){
					//ACTUALIZAMOS LA LISTA TABU
					if (lista_tabu.size()==tam_LT){
						lista_tabu.pop_front();
					}	
					pair<int, int> tabu;
					tabu.first=mejorElem;
					tabu.second=k;
					lista_tabu.push_back(tabu);
					//ACTUALIZAMOS LA MATRIZ DE FRECUENCIAS
					matriz_frecuencias[mejorElem][mejorCj]++;
					double* elem=elementos[mejorElem];
					double incrJ=incremento_J(elem,k,mejorCj);
					factorizar(elem,k,mejorCj);
					cluster_elementos[k].at(mejorPos)=cluster_elementos[k].back();
					cluster_elementos[k].pop_back();
					cluster_elementos[mejorCj].push_back(mejorElem);
					P[mejorElem]=mejorCj;
					solucion=solucion+incrJ;
					contador++;
					//cout<<"Iteracion: "<<contador<<endl;
					contador_reinicio++;
				}
				if (solucion<mejor_solu){
					mejor_solu=solucion;
					copiaP=P;					
				}
				if (contador_reinicio>2000){
					lista_tabu.clear();
					contador_reinicio=0;
					int aleatorio=rand()%100;
					//REINICIO ALEATORIO
					if(aleatorio<25){
						cout<<"REINICIO ALEATORIO"<<endl;
						solInicial();
					}
					//REINICO A LA MEJOR SOLUCION
					if (aleatorio>=25&&aleatorio<50){
						cout<<"REINICIO LA MEJOR SOLUCION"<<endl;
						P.clear();
						P=copiaP;
						calcula_centroides();
						cout<<"Mejor solucion: "<<solucion<<endl;
					}
					//REINICIO MEMORIA A LARGO PLAZO
					if (aleatorio>=50){
						cout<<"REINICIO FRECUENCIAS"<<endl;
						for(int i=0; i<elementos.size(); i++){
							int clusterEle=-1;
							int veces=999999;
							for (int j=0; j<tam_cluster; j++){
								if (matriz_frecuencias[i][j]<veces){
									veces=matriz_frecuencias[i][j];
									clusterEle=j;
								}
							} 
							P[i]=clusterEle;
						}
						calcula_centroides();
					}	
					aleatorio=rand()%100;
					if (aleatorio<50){
						tam_LT=tam_LT+(tam_LT/4);
					}else{
						tam_LT=tam_LT-(tam_LT/4);
					}
					//REINICIAMOS LOS CLUSTERS
					for(int i=0; i<tam_cluster; i++){
						cluster_elementos[i].clear();
					}
					for(int i=0; i<elementos.size(); i++){
						cluster_elementos[P[i]].push_back(i);
					}
				}
			}
		}
	}
	solucion=mejor_solu;
}

void kmedias(){
	solInicial();//SOLUCION ALEATORIA
	bool cambio=true;
	bool cambios=true;
	while (cambios){
		cambio=false;
		cambios=false;
		calcula_centroides();//SE SACA UNA MEDIA DE TODOS LOS PATRONES PERTENCIENTES A LOS CLUSTER Y ESE ES EL CENTRODIDE DEL CLUSTER.
		for (int i=0; i<elementos.size(); i++){
			double distaciaMin=99999999;
			double *elem_i=elementos[i];
			int Cjelegido=-1;
			for (int j=0; j<tam_cluster; j++){
				//if (j!=P[i]){
					double *Cj=centroides[j];
					double distacia=calcular_dist(elem_i, Cj);
					if (distacia<distaciaMin){
						distaciaMin=distacia;
						if (j!=P[i]){
							Cjelegido=j;
							cambio=true;
						}else{//Si la distancia minima pertenece al cluster al que esta no hay cambio
							cambio=false;
						}
					}
				//}
			}
			if (cambio&&Cjelegido>-1){
				P[i]=Cjelegido;
				cambios=true;
			}
		}

	}

}