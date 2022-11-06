//RETO 1
//Hecho por: DIEGO ARAQUE A01026037 Y OCTAVIO FENOLLOSA

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>

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

//Clase que nos permitira manipular atritbutos nuevos, es decir, Conexiones entrantes y salientes
class ConexionesComputadora {
    public:
    string nombre;
    //ipEspecializada es la uqe incluye el numero dado por el usuario
    string ipEspecializada;
    //ipInterna como bien lo describe es la ip que tiene cada computadora pero sin el nuemro que las identifica
    string ipInterna;
    //Se utilizara Stack para las conexiones Entrantes
    stack<Record> conexionesEntrantes;
    //Se utilizara Queue para las conexiones Salientes
    queue<Record> conexionesSalientes;
    ConexionesComputadora(string ip, string name, string num){
        ipEspecializada=ip+num;
        ipInterna=ip;
        nombre=name;
    }
    void redInterna(){
        cout<<ipEspecializada<<endl;
    }
    void conexionesS(Record cS){
        conexionesSalientes.push(cS);
    }
    void conexionesE(Record cE){
        conexionesEntrantes.push(cE);
    }
    void tipoDeIpConexionEntrante(){
        if(ipInterna==conexionesEntrantes.top().ipFuente.substr(0,10)){
            cout<<"La ultima ip de las conexiones entrantes es interna, la ip interna es: "<<conexionesEntrantes.top().ipFuente<<endl;
        }else{
            cout<<"La ultima ip de las conexiones entrantes es externa, la ip externa es: "<<conexionesEntrantes.top().ipFuente<<endl;
        }
    }
    void tipoDeIpConexionSaliente(){
        if(ipInterna==conexionesSalientes.back().ipFuente.substr(0,10)){
            cout<<"La ultima ip de las conexiones salientes es externa, la ip interna es: "<<conexionesSalientes.back().ipFuente<<endl;
        }else{
            cout<<"La ultima ip de las conexiones entrantes es externa, la ip externa es: "<<conexionesSalientes.back().ipFuente<<endl;
        }
    }
};

int main(){
    cargarDatos("datosEquipo2.csv");
    int num;
    cout<<"Ingrese un numero entre 1-150: ";
    cin>>num;
    stringstream ss;  
    ss<<num;  
    string sNum;  
    ss>>sNum;  
    string ipInterna= data[1].ipFuente.substr(0,10);
    string sUpdate="."+sNum;
    cout<<"La red interna es: "<<ipInterna<<endl;
    string name;
    for(int i=0; i<data.size(); i++){
        if(data[i].ipFuente==ipInterna+sUpdate){
            name=data[i].nombreFuente;
            break;
        }
    }
    ConexionesComputadora ej1(ipInterna, name, sUpdate);
    for(int i=0; i<data.size();i++){
        if(data[i].ipFuente==ej1.ipEspecializada){
            ej1.conexionesS(data[i]);
        } else if(data[i].ipDestino==ej1.ipEspecializada){
            ej1.conexionesE(data[i]);
        }
    }
    cout<<"La ip utilizada por el numero dado es: ";
    ej1.redInterna();
    cout<<"La cantidad de conexiones salientes es: "<<ej1.conexionesSalientes.size()<<endl;
    cout<<"La cantidad de conexioens entrantes es: "<<ej1.conexionesEntrantes.size()<<endl;
    ej1.tipoDeIpConexionEntrante();
    ej1.tipoDeIpConexionSaliente();
    return 0;
}