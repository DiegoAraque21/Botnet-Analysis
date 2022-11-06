//RETO 1
//Hecho por: DIEGO ARAQUE A01026037 Y OCTAVIO FENOLLOSA

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

//Clase que ajusta los valores y crea el vector final. Los datos estaran acmodados perfectamente.
class Record{
	public:
    string fecha;
    string hora;
    string ipFuente;
    int puertoFuente;
	string nombreFuente;
    string ipDestino;
    int puertoDestino;
    string nombreDestino;

	Record(string f, string h, string iF, string pF, string nF, string iD, string pD, string nD){
        this->fecha=f;
        this->hora=h;
        this->ipFuente=iF;
		if(pF=="-"){
			this->puertoFuente=0;
		}else{
			this->puertoFuente=stoi(pF);
		}
		this->nombreFuente=nF;
		this->ipDestino=iD;
        if(pD=="-"){
			this->puertoDestino=0;
		}else{
			this->puertoDestino=stoi(pD);
		}
        this->nombreDestino=nD;
	}
	void imprimirRecord(){
		cout<<fecha<<":"<<hora<<":"<<ipFuente<<":"<<puertoFuente<<":"<<nombreFuente<<":"<<ipDestino<<":"<<puertoDestino<<":"<<nombreDestino<<endl;
	}
};
//Funcion que lee el archivo csv y genera el vector data
vector<Record> data;
void cargarDatos(string path){
	ifstream in;
	in.open(path);
	string line, parte;
	vector<string> partes;
	while(getline(in, line)){
		if(line.find("\r")!=line.npos){
			    line=line.substr(0, line.size()-1);
		}
		istringstream inString(line);
		while(getline(inString, parte, ',')){
			partes.push_back(parte);
		}
		Record r(partes[0],partes[1],partes[2],partes[3], partes[4],partes[5],partes[6],partes[7]);
		data.push_back(r);
		partes.clear();
	    }
	in.close();
}
//Funcion que calcula el numero de registros que tiene el archivo csv
void numeroRegistros(vector <Record> data){
    cout<<"¿Cuántos registros tiene tu archivo?"<<endl;
    cout<<"La cantidad de registros en nuestro archivo es de: "<<data.size()<<endl;
}
//Funcion que compara un record con un valor en especifico en este caso es nombre de la fuente que es un string
int compararRecordNombreFuente(Record r, string nF){
	if(r.nombreFuente<nF){
		return -1;
	}else if (r.nombreFuente==nF){
		return 0;
	}else{
		return 1;
	}
}
//Funcion que compara 2 records en la misma posicion para de esa manera ordenarlo. En este caso se comparan strings
//por lo que se tiene un orden lexicografico. Esta funcion es la del nombre de la fuente
int compararDosRecordsNombreFuente(Record r1, Record r2){
	if(r1.nombreFuente<r2.nombreFuente){
		return -1;
	}else if (r1.nombreFuente==r2.nombreFuente){
		return 0;
	}else{
		return 1;
	}
}
//Funcion que compara un record con un valor en especifico en este caso es puerto de destino que es un numero entero
int compararRecordPuertoDestino(Record r, int pD){
	if(r.puertoDestino<pD){
		return -1;
	}else if (r.puertoDestino==pD){
		return 0;
	}else{
		return 1;
	}
}
//Funcion que compara un record con otro en la posicion del puerto de destino. En este caso compara numeros enteros
int compararDosRecordsPuertoDestino(Record r1, Record r2){
	if(r1.puertoDestino<r2.puertoDestino){
		return -1;
	}else if (r1.puertoDestino==r2.puertoDestino){
		return 0;
	}else{
		return 1;
	}
}
//Funcion que compara un record con un valor especifico en este caso el nombre del Destino
int compararRecordNombreDestino(Record r, string nD){
	if(r.nombreDestino<nD){
		return -1;
	}else if (r.nombreDestino==nD){
		return 0;
	}else{
		return 1;
	}
}
//Funcion que compara 2 records en la misma posicion para de esa manera ordenarlo. En este caso se comparan strings
//por lo que se tiene un orden lexicografico. ESta compara los nombres del destino
int compararDosRecordsNombreDestino(Record r1, Record r2){
	if(r1.nombreDestino<r2.nombreDestino){
		return -1;
	}else if (r1.nombreDestino==r2.nombreDestino){
		return 0;
	}else{
		return 1;
	}
}
// Comparador de la fecha de un record por una fecha en especifico
int compararRecordFecha(Record r, string fecha){
	if(r.fecha<fecha){
		return -1;
	}else if (r.fecha==fecha){
		return 0;
	}else{
		return 1;
	}
}
//Compaardor de la fecha de 2 records diferentes
int compararDosRecordsFecha(Record r1, Record r2){
	if(r1.fecha<r2.fecha){
		return -1;
	}else if (r1.fecha==r2.fecha){
		return 0;
	}else{
		return 1;
	}
}
//Clase general de ordenamiento la cual sera heredada por la de Insertion
template <class T>
class Sorter{
	public:
	virtual void Sort(vector<T> &data, int comparador(T a, T b))=0;
	
	void Imprimir(vector<T> &data){
		for(int i=0; i<data.size(); i++){
			cout<<data[i]<<",";
		}
		cout<<endl;
	}
	
	void Intercambiar(vector<T> &data, int posI, int posJ){
		T temp=data[posI];
		data[posI]=data[posJ];
		data[posJ]=temp;
	}
};
// Ordenamiento de cualquier variable gracias los comapradores a traves de MergeSort. MergeSort es una de las formas mas rapidas 
// de ordenar, en este caso un archivo csv. 
template<class T>
class QuickSort: public Sorter<T>{
    public:
    void Sort(vector<T> &data,  int comparador(T a, T b)){
        sortAux(data,0,data.size()-1,comparador);
    }

    private:
    void sortAux(vector<T> &data, int lo, int hi, int comparador(T a, T b)){
        if(lo>=hi){
            return;
        }
        int posOrdenado=partition(data,lo,hi,comparador);
        sortAux(data,lo,posOrdenado-1,comparador);
        sortAux(data,posOrdenado+1,hi,comparador);
    }
    int partition(vector<T> &data, int lo, int hi,  int comparador(T a, T b)){
        int p=lo;
        int i=lo+1;
        int j=hi;
        while(true){
            while(comparador(data[i],data[p])<1 && i<hi){
                i++;
            }
            while(comparador(data[j],data[p])==1 && j>lo){
                j--;
            }
            if(i<j){
                this->Intercambiar(data,i,j);
            }else{
                this->Intercambiar(data,p,j);
                break;
            }
        }
        return j;
    }
};
// Busqueda Binaria, esta solo son funciona cuando nuestro arreglo se encuentra ordenado. Pero es muy beneficiosa, 
// debido a que es las mas rapida
template <class T, class B>
int busquedaBinaria(vector<T> data, B buscado, int comparador(T a, B b)){
    int inicio=0;
    int fin=data.size()-1;
    while(inicio<=fin){
        int medio=(fin+inicio)/2;
        if(comparador(data[medio],buscado)==0){
            return medio;
        }else if(comparador(data[medio],buscado)==-1){
            inicio=medio+1;
        }else{
            fin=medio-1;
        }
    }
    return -1;
}
//Metodo para encontrar la segunda fecha.
template<class T>
string busquedaFecha(vector<T> data){
	for(int i=0;i<data.size();i++){
		string fecha2;
		if(data[i].fecha==data[0].fecha){
			fecha2="";
		}else if(data[i].fecha!=data[0].fecha){
			return fecha2=data[i].fecha;
		}
	}
    return "no existe una segunda fecha";
}
//Funcion que calcula la cantidad de veces que la fecha se repite
template <class T>
int repeticiones2Fecha(vector<T> data, string buscado){
	int contador=0;
	for(int i=0; i<data.size(); i++){
		if(data[i].fecha==buscado){
			contador++;
		}
	}
	return contador;
}
//Funcion que imprime cada puerto de desttino menor que 1000
template <class T>
void puertoDestinoMenor1000(vector<T> data){
	int anterior=0;
	for(int i=0;i<data.size();i++){
		if(data[i].puertoDestino<=1000 && data[i].puertoDestino!=anterior){
			cout<<data[i].puertoDestino<<endl;
			anterior=data[i].puertoDestino;
		}else{
			anterior=data[i].puertoDestino;
		}
	}
}
//Funcion que encuentra imprime la red interna de la comapñia
template <class T>
void redInternaCompania(vector<T> data){
	for(int i=0; i<data.size(); i++){
		if(data[i].ipFuente != "-"){
			cout<<"La red interna de la compañia es: "<<data[i].ipFuente.substr(0,10)<<".0"<<endl;
			break;
		}
	}
}

int main(){
    cargarDatos("datosEquipo2.csv");
    //Numero de registros de el archivo
    numeroRegistros(data);
    //Para realizar el ordenamiento tenemos que definir un ob jeto, debido a que tenemos una clase
	QuickSort<Record> s;
    //¿Cuántos récords hay del segundo día registrado? ¿Qué día es este?
	s.Sort(data, compararDosRecordsFecha);
	cout<<"¿Cuántos récords hay del segundo día registrado? ¿Qué día es este?"<<endl;
	string fecha2=busquedaFecha<Record>(data);
	cout<<"La segunda fecha es: "<<fecha2<<endl;
	int repeticiones=repeticiones2Fecha<Record>(data,fecha2);
	cout<<"La segunda fecha se repite: "<<repeticiones<<" veces"<<endl;   
    //Existencia de las computadoras de Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond
    s.Sort(data, compararDosRecordsNombreFuente);
    cout<<"¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?"<<endl;
    int pos=busquedaBinaria<Record, string>(data, "jeffrey.reto.com", compararRecordNombreFuente);
	cout<<"jeffrey.reto.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos<<endl;
    int pos2=busquedaBinaria<Record, string>(data, "betty.reto.com", compararRecordNombreFuente);
	cout<<"betty.reto.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos2<<endl;
    int pos3=busquedaBinaria<Record, string>(data, "katherine.reto.com", compararRecordNombreFuente);
	cout<<"katherine.reto.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos3<<endl;
    int pos4=busquedaBinaria<Record, string>(data, "scott.reto.com", compararRecordNombreFuente);
	cout<<"scott.reto.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos4<<endl;
    int pos5=busquedaBinaria<Record, string>(data, "benjamin.reto.com", compararRecordNombreFuente);
	cout<<"benjamin.reto.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos5<<endl;
    int pos6=busquedaBinaria<Record, string>(data, "samuel.reto.com", compararRecordNombreFuente);
	cout<<"samuel.reto.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos6<<endl;
    int pos7=busquedaBinaria<Record, string>(data, "raymond.reto.com", compararRecordNombreFuente);
	cout<<"raymond.reto.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos7<<endl;
    // Alguna computadora se llama server reto
    cout<<"¿Alguna computadora se llama server.reto.com?"<<endl;
    int pos8=busquedaBinaria<Record, string>(data, "server.reto.com", compararRecordNombreFuente);
	cout<<"server.reto.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos8<<endl;
    //¿Qué servicio de mail utilizan de todos estos: gmail.com, outlook.com, protonmail.com, freemailserver.com?
    s.Sort(data, compararDosRecordsNombreDestino);
    cout<<"¿Qué servicio de mail utilizan de todos estos: gmail.com, outlook.com, protonmail.com, freemailserver.com?"<<endl;
    int pos9=busquedaBinaria<Record, string>(data, "gmail.com", compararRecordNombreDestino);
	cout<<"gmail.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos9<<endl;
    int pos10=busquedaBinaria<Record, string>(data, "outlook.com", compararRecordNombreDestino);
	cout<<"outlook.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos10<<endl;
    int pos11=busquedaBinaria<Record, string>(data, "protonmail.com", compararRecordNombreDestino);
	cout<<"protonmail.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos11<<endl;
    int pos12=busquedaBinaria<Record, string>(data, "freemailserver.com", compararRecordNombreDestino);
    cout<<"freemailserver.com se encuentra en la posicion (si la posicion es -1 no se encuetra en el arreglo): "<<pos12<<endl;
    //¿Cuál es la dirección de la red interna de la compañía?
	cout<<"¿Cuál es la dirección de la red interna de la compañía?"<<endl;
	redInternaCompania(data);
    //Considerando solamente los puertos destino ¿Qué puertos abajo del 1000 se están usando? Lista los puertos e investiga que aplicación/servicio lo utiliza generalmente.
	s.Sort(data,compararDosRecordsPuertoDestino);
	cout<<"Considerando solamente los puertos destino ¿Qué puertos abajo del 1000 se están usando? Lista los puertos e investiga que aplicación/servicio lo utiliza generalmente."<<endl;
	cout<<"Los puertos de destino menores a 1000 son los siguientes: "<<endl;
	puertoDestinoMenor1000(data);
    return 0;
}