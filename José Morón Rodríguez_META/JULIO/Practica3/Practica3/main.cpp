#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <list>
#include <algorithm>  
#include <ctime>
using namespace std;

//Constantes
const int breast=9;
const int yeast=8;
const int r15=2;

const int c_breast=2;
const int c_yeast=10;
const int c_r15=15;

int semilla=77349558;
int semillas[]={77349558,73495587,34955877,49558773,95587734};//array de semillas

//Variables globales
int tam_elemnto=0;
int tam_cluster=0;
double solucion=0;
vector<double *> elementos;
/*Vector con pares con los gentes y su valor*/
vector<pair<vector<int>, double>> poblacion;

//FUNCIONES
bool cargarFichero(string nombre);
double funcFiness(vector<int> gen);
void generarPopInicial();
double calcular_dist(double* elem, double* centroide);
pair<vector<int>,vector<int> > cruce(vector<int> padre1, vector<int> padre2);
void gerenacional(int numeroGeneraciones, double probBL);
vector<int> algoritmo_BL(vector<int> cromosoma);
bool orderPoblacion(pair<vector<int>, double> cromosoma1, pair<vector<int>, double> cromosoma2){return cromosoma1.second<cromosoma2.second;};

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
			cout<<"1.- AM-(10,1.0)"<<endl;
			cout<<"2.- AM-(10,0.1)"<<endl;
			cout<<"3.- Salir "<<endl;
			opcion=0;
			semilla=semillas[posSemilla];
			while (opcion<1||opcion>4) cin>>opcion;
			start=clock();
			switch (opcion){
			case 1:
				algoritmoElegido="AM-(10,1.0)";
				gerenacional(10, 1.0);
				break;
			case 2:
				algoritmoElegido="AM-(10,0.1)";
				gerenacional(10, 0.1);
				break;
			case 3:
				salir=true;
				break;
			default:
				break;
			}
			duracion=(clock()-start)/(double)CLOCKS_PER_SEC;
			sort(poblacion.begin(), poblacion.end(), orderPoblacion);
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
/*La poblacion inicial se generara aleatoriamente, para cada gen se calculara su funccion objetivo.*/
void generarPopInicial(){
	srand(semilla);
	vector<int> cromosoma_modelo;
	for (int i=0; i<elementos.size();i++) cromosoma_modelo.push_back(i);
	poblacion.clear();
	for(int i=0; i<10; i++){
		vector<int> cromosoma=cromosoma_modelo;
		random_shuffle(cromosoma.begin(), cromosoma.end());
		double J=funcFiness(cromosoma);
		pair<vector<int>, double> cromosoma_final;
		cromosoma_final.first=cromosoma;
		cromosoma_final.second=J;
		poblacion.push_back(cromosoma_final);
		
	}
}
double funcFiness(vector<int> cromosoma){
	vector<int> P;
	vector<double *> centroides;
	vector<int> tams_clusters;
	for (int i=0; i<elementos.size();i++) P.push_back(-1);
	for (int i=0; i<tam_cluster; i++){
		double *cent=elementos[cromosoma[i]];
		centroides.push_back(cent);
		P[cromosoma[i]]=i;
		tams_clusters.push_back(1);
	}

	for (int i=0; i<cromosoma.size(); i++){
		if (P[cromosoma[i]]==-1){
			double dist_min=99999999;
			double* elem_i=elementos[cromosoma[i]];
			int centJ=-1;
			//calculamos el centroide mas cercano al elemento i del gen
			for (int j=0; j<tam_cluster; j++){
				double	*zj=centroides[j];
				double dist=calcular_dist(elem_i, zj);
				if (dist<dist_min){
					centJ=j;
					dist_min=dist;
				}
			}
			//Recaculamos los centroides
			/*double *zj=centroides[centJ]; 
			for (int j=0; j<tam_elemnto; j++){
				zj[j]=(double)((zj[j]*(double)tams_clusters[centJ])+(double)elem_i[j])/(double)(tams_clusters[centJ]+1.0);
			}*/
			tams_clusters[centJ]++;
			P[cromosoma[i]]=centJ;
			//centroides[centJ]=zj;
		}
	}

	//for (int i=0; i<tam_cluster; i++){
	//	double *cent=elementos[cromosoma[i]];
	//	centroides.push_back(cent);
	//	//P[cromosoma[i]]=i;
	//	//tams_clusters.push_back(1);
	//}
	double solucion=0;
	for (int i=0; i<elementos.size(); i++){
		double distancia=calcular_dist(elementos[i], centroides[P[i]]);
		solucion=solucion+pow(distancia,2);
	}
	return solucion;

	
}
double calcular_dist(double* elem, double* centroide){
	double dist=0;
	for (int i=0; i<tam_elemnto; i++){
		dist=dist+((centroide[i]-elem[i])*(centroide[i]-elem[i]));
	}
	dist=sqrt(dist);
	return dist;
}

pair<vector<int>,vector<int> > cruce(vector<int> padre1, vector<int> padre2){
	vector<int> restantes1;
	vector<int> restantes2;
	vector<int> hijo1;
	vector<int> hijo2;
	for (int i=0; i<padre1.size(); i++){
		if (padre1[i]==padre2[i]){//conservamos los genes igualies de los padres			
			hijo1.push_back(padre1[i]);
			hijo2.push_back(padre1[i]);
		}else{
			hijo1.push_back(-1);
			hijo2.push_back(-1);
			restantes1.push_back(padre1[i]);
		}
	}
	restantes2=restantes1;
	random_shuffle(restantes1.begin(), restantes1.end());
	random_shuffle(restantes2.begin(), restantes2.end());
	int j=0;
	for (int i=0; i<padre1.size(); i++){
		if (hijo1[i]==-1){
			hijo1[i]=restantes1[j];
			hijo2[i]=restantes2[j];
			j++;
		}
	}
	pair<vector<int>,vector<int> > resultado;
	resultado.first=hijo1;
	resultado.second=hijo2;
	return resultado;
	
}
void gerenacional(int numeroGeneraciones, double probBL){
	generarPopInicial();
	int contador=0;
	vector<int> seleccionados;
	vector<int> posPadres;
	solucion=999999999999;
	vector<vector<int> > pobHijos;
	vector<pair<vector<int>, double>> padres;
	double probC=0.7;
	double probM=0.001;
	int numPobla=10;
	int numCruces=(int)(probC*(numPobla/2));
	int numGenes=elementos.size();
	vector<int> posMutaciones;
	for (int i=0; i<elementos.size(); i++) posMutaciones.push_back(i);
	random_shuffle(posMutaciones.begin(), posMutaciones.end());
	int contPosMutaciones=0;
	int contGeneraciones=0;
	while (contador<10000){
		//Generemamos la poblacion de hijos.
		sort(poblacion.begin(), poblacion.end(), orderPoblacion);
		if (poblacion[0].second<solucion){
			solucion=poblacion[0].second;
		}
		bool mejorMuerto=false;
		padres.clear();
		posPadres.clear();
		seleccionados.clear();
		for (int i=0; i<poblacion.size(); i++){
			posPadres.push_back(i);
			padres.push_back(poblacion[i]);
		}
		pobHijos.clear();
		random_shuffle(posPadres.begin(), posPadres.end());
		vector<pair<vector<int>, double>> poblacionInter=poblacion;
		for (int i=0; i<numCruces; i++){
			bool encontrado=false;
			int aleatorio1=posPadres[0];
			int aleatorio2=posPadres[1];
			int aleatorio3=posPadres[2];
			int aleatorio4=posPadres[3];
			
			//TORNEO BINARIO ESCOJEMOS LOS QUE MEJOR SOLUCION TIENEN.
			vector<int> padre1=padres[aleatorio1].first;
			int elegido1=aleatorio1;
			if (padres[aleatorio2].second<padres[aleatorio1].second){
				padre1=padres[aleatorio2].first;
				elegido1=aleatorio2;
			}
			if (elegido1==1&&!mejorMuerto){
				mejorMuerto=true;
			}
			
			vector<int> padre2=padres[aleatorio3].first;
			int elegido2=aleatorio3;
			if (padres[aleatorio4].second<padres[aleatorio3].second){
				padre2=padres[aleatorio4].first;
				elegido2=aleatorio4;
			}
			if (elegido2==1&&!mejorMuerto){
				mejorMuerto=true;
			}
			
						
			pair<vector<int>, vector<int> > hijos=cruce(padre1, padre2);
			pair<vector<int>, double> H;
			H.first=hijos.first;
			H.second=-1;
			poblacionInter[elegido1]=H;
			H.first=hijos.second;
			poblacionInter[elegido2]=H;
			for (int j=0;j<posPadres.size(); j++){
				if (posPadres[j]==elegido1){
					posPadres[j]=posPadres.back();
					posPadres.pop_back();
					break;
				}
			}
			for (int j=0;j<posPadres.size(); j++){
				if (posPadres[j]==elegido2){
					posPadres[j]=posPadres.back();
					posPadres.pop_back();
					break;
				}
			}
			
		}
		//MUTAMOS LA POBLACION INTERMEDIA
		int numMutacions=(int)(numPobla*numGenes*probM);
		for (int i=0; i<numMutacions; i++){
			int elegido=rand()%poblacionInter.size();
			vector<int> gen=poblacionInter[elegido].first;
			bool encotrado=false;
			int pos1=posMutaciones[contPosMutaciones++];
			int pos2=posMutaciones[contPosMutaciones++];
			if (contPosMutaciones+2>=posMutaciones.size()-1){
				posMutaciones.clear();
				for (int i=0; i<elementos.size(); i++) posMutaciones.push_back(i);
				random_shuffle(posMutaciones.begin(), posMutaciones.end());
				contPosMutaciones=0;
			}
			int aux=gen[pos1];
			gen[pos1]=gen[pos2];
			gen[pos2]=aux;
			poblacionInter[elegido].first=gen;
			poblacionInter[elegido].second=-1;
		}
		//CALULAMOS LA FUNCFINNES DE LOS HIJOS Y DE LOS QUE HAN MUTADO
		for (int i=0; i<poblacionInter.size(); i++){
			if(poblacionInter[i].second==-1){
				poblacionInter[i].second=funcFiness(poblacionInter[i].first);
				contador++;
				//cout<<contador<<endl;
			}
		}
		contGeneraciones++;
		//CADA X GENERACIONES USAMOS LA BUSQUEDA LOCAL SEGUN LA PROB
		if (contGeneraciones==numeroGeneraciones){
			vector<int> numPoblacion;
			for (int i=0; i<numPobla; i++) numPoblacion.push_back(i);
			random_shuffle(numPoblacion.begin(), numPoblacion.end());
			int numBL=(int)(numPobla*probBL);
			for (int i=0; i<numBL; i++){
				vector<int> cromosoma=poblacionInter[numPoblacion[i]].first;
				cromosoma=algoritmo_BL(cromosoma);
				double J=funcFiness(cromosoma);
				contador++;
				poblacionInter[numPoblacion[i]].first=cromosoma;
				poblacionInter[numPoblacion[i]].second=J;
			}
		}
		sort(poblacionInter.begin(), poblacionInter.end(), orderPoblacion);
		if (mejorMuerto){
			poblacionInter.pop_back();
			poblacionInter.push_back(poblacion[0]);
		}
		poblacion.clear();
		poblacion=poblacionInter;
		cout<<contador<<endl;
	}

}

vector<int> algoritmo_BL(vector<int> cromosoma){
	vector<int> solu=cromosoma;
	vector<int> P;
	vector<double *> centroides;
	vector<int> tams_clusters;
	for (int i=0; i<elementos.size();i++) P.push_back(-1);
	for (int i=0; i<tam_cluster; i++){
		double *cent=elementos[cromosoma[i]];
		centroides.push_back(cent);
		P[cromosoma[i]]=i;
		tams_clusters.push_back(1);
	}
	for (int i=0; i<cromosoma.size(); i++){
		if (P[cromosoma[i]]==-1){
			double dist_min=99999999;
			double* elem_i=elementos[cromosoma[i]];
			int centJ=-1;
			//calculamos el centroide mas cercano al elemento i del gen
			for (int j=0; j<tam_cluster; j++){
				double	*zj=centroides[j];
				double dist=calcular_dist(elem_i, zj);
				if (dist<dist_min){
					centJ=j;
					dist_min=dist;
				}
			}
			tams_clusters[centJ]++;
			P[cromosoma[i]]=centJ;
		}
	}
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
	for (int i=0; i<elementos.size(); i++){
		double *elem_i=elementos[i];
		int Ci=P[i];
		double dist_min=9999999999;
		int Cj=-1;
		for (int j=0; ((j<tam_cluster)); j++){
			if (j!=Ci){
				double dist=calcular_dist(elem_i, centroides[j]);
				if (dist<dist_min){
					dist_min=dist;
					Cj=j;	
				}
			}
		}
		if (Cj>-1){
			int mi=tams_clusters[Ci];
			int mj=tams_clusters[Cj];
			double* zi=centroides[Ci];
			double* zj=centroides[Cj];
			for (int i=0; i<tam_elemnto; i++){
				zi[i]= ((mi*zi[i])-elem_i[i])/(double)(mi-1);
				zj[i]= ((mj*zj[i])+elem_i[i])/(double)(mj+1);
			}
			centroides[Ci]=zi;
			centroides[Cj]=zj;
			tams_clusters[Ci]--;
			tams_clusters[Cj]++;
			P[i]=Cj;
		
		}
	}
	for (int i=0; i<tam_cluster; i++){
		double *zi=centroides[i];
		double *mi=elementos[solu[i]];
		double distancia_min=calcular_dist(mi, zi);
		int medoide=-1;
		int posMed=-1;
		for (int j=i+1; j<solu.size(); j++){
			double *mj=elementos[solu[j]];
			double distancia=calcular_dist(mj, zi);
			if (distancia<distancia_min){
				medoide=solu[j];
				posMed=j;
			}
			
		}
		if (medoide>0){
			int aux=solu[i];
			solu[i]=solu[posMed];
			solu[posMed]=aux;
		}
	}

	return solu;
}