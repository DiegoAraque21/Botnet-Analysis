#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <stack>
using namespace std;

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

template <class T>
class Nodo{
	public:
	T id;
	bool visitado;
	unordered_map<Nodo<T> *, int> siguientes;
	
	Nodo(T id){
		this->id=id;
		visitado=false;
	}
	
	void agregarArcoConPeso(Nodo<T> *sig, int peso){
		siguientes[sig]=peso;
	}
	
	void imprimirNodo(){
		cout<<this->id<<":";
		for(auto it=siguientes.begin(); it!=siguientes.end(); it++){
			cout<<it->first->id<<","<<it->second<<";";
		}
		cout<<endl;
	}
};

template <class T>
class Grafo{
	unordered_map<T,Nodo<T>*> nodos;
	
	public:

  void conexB(T B){
    int cont=0;
    for(auto n:nodos){
      for(auto s:nodos[n.first]->siguientes){
        if(s.first->id==B){
          cont++;
      }
      }
    }
    cout<<"Las conexiones B son :"<<cont<<endl;
  }

  void conexC(T C){
    int cont=0;
    for(auto n:nodos){
      for (auto s:nodos[n.first]->siguientes){
       if(s.first->id==C){
          cont++;
      }
      }
    }
    cout<<"Las conexiones C son :"<<cont<<endl;

  }


	void agregarNodo(T id){
		if(nodos.find(id)!=nodos.end()){

		} else{
			Nodo<T> *nuevo=new Nodo<T>(id);
			nodos[id]=nuevo;
		}
	}
  
	void agregarArcoDirigidoConPeso(T fuente, T destino){
    	int nuevoPeso = calcularPeso(nodos[fuente], nodos[destino]);
		nodos[fuente]->agregarArcoConPeso(nodos[destino], nuevoPeso);
	}
	
	int calcularPeso(Nodo<T> *fuente, Nodo<T> *destino){
    	for(auto it= fuente->siguientes.begin(); it!=fuente->siguientes.end(); it++){
      		if(it->first->id==destino->id){
        		int peso=it->second;
        		peso++;
        		return peso;
      			}
    		}
    	return 1;
  	}
  
	void imprimir(){
		for(auto it:nodos){
			it.second->imprimirNodo();
		}
	}

  void numeroCNX(T fuente){
    cout<<nodos[fuente]->siguientes.size()<<endl;
    int pesoMax=0;
    string m;
    for(auto c:nodos[fuente]->siguientes){
      if(c.second>pesoMax){
        pesoMax=c.second;
        m=c.first->id;
      }
    }
    cout<<"Se conecta mas ves a "<<m<<" unas "<<pesoMax<<" veces."<<endl;
  }

};


int main(){
  cargarDatos("datosEquipo2.csv");
  string fecha1="10-8-2020";
  string fecha2="11-8-2020";
  string fecha3="12-8-2020";
  string fecha4="13-8-2020";
  string fecha5="14-8-2020";
  string fecha6="17-8-2020";
  string fecha7="18-8-2020";
  string fecha8="19-8-2020";
  string fecha9="20-8-2020";
  string fecha10="21-8-2020";
  string A="172.24.133.84"; //Computadora de debra, que se conecta a otras internas
  string B="213.197.181.214"; // Sitio con nombre anomala
  string C="68.76.127.243";// Ip de bank of america
  //Preeguntas 1, 2, 3, 4
  Grafo<string> gInternas; //Grafo Internas
  Grafo<string> conexSitios; //Grafo a sitios web
  for (int i=0; i<data.size();i++){
    if((data[i].nombreFuente.substr(data[i].nombreFuente.size()-8,data[i].nombreFuente.size())=="reto.com") && 
	(data[i].nombreDestino.size()>8) && (data[i].nombreDestino.substr(data[i].nombreDestino.size()-8,data[i].nombreDestino.size())=="reto.com") && 
	(fecha4==data[i].fecha)){
	  gInternas.agregarNodo(data[i].ipFuente);
      gInternas.agregarNodo(data[i].ipDestino);
	  gInternas.agregarArcoDirigidoConPeso(data[i].ipFuente, data[i].ipDestino);
    }
    
    if((data[i].nombreFuente.substr(data[i].nombreFuente.size()-8,data[i].nombreFuente.size())=="reto.com") && 
	(data[i].nombreDestino.size()>8) && (data[i].nombreDestino.substr(data[i].nombreDestino.size()-8,data[i].nombreDestino.size())!="reto.com") && (data[i].nombreDestino.size()>8) && (data[i].nombreDestino.substr(data[i].nombreDestino.size()-8,data[i].nombreDestino.size())!="-") &&
	(fecha10==data[i].fecha)){
	  conexSitios.agregarNodo(data[i].ipFuente);
      conexSitios.agregarNodo(data[i].ipDestino);
	  conexSitios.agregarArcoDirigidoConPeso(data[i].ipFuente, data[i].ipDestino);
    //cout<<conexSitios.DFSnuevo(data[i].ipFuente,"213.197.181.214")<<endl;
    }
    
  }


  //Respuestas
  gInternas.numeroCNX(A); //Solo sirve si A tiene conexiones siguientes, de lo contrario marca error
  cout<<"-------------------------------------"<<endl;
  gInternas.imprimir();
  cout<<"-------------------------------------"<<endl;
  cout<<fecha10<<endl;
  conexSitios.conexB(B);
  conexSitios.conexC(C);

  
  
  return 0;
};
