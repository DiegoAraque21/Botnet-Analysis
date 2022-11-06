//RETO 1
//Hecho por: DIEGO ARAQUE A01026037, OCTAVIO FENOLLOSA A01781042, YAREZZI GARCIA A01653133   

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

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
    //ipInterna como bien lo describe es la ip que tiene cada computadora pero sin el nuemro que las identifica
    string ipInterna;
    //Se utilizara Stack para las conexiones Entrantes
    vector<string> conexionesEntrantes;
    //Se utilizara Queue para las conexiones Salientes
    vector<string> conexionesSalientes;
    ConexionesComputadora(string ip, string name){
        this->ipInterna=ip;
        this->nombre=name;
    }
    ConexionesComputadora(){
        this->ipInterna="";
        this->nombre="";
    }
    void conexionesS(string ipDestino){
        conexionesSalientes.push_back(ipDestino);
    }
    void conexionesE(string ipFuente){
        conexionesEntrantes.push_back(ipFuente);
    }
    void imprimir(){
        if(nombre == "-"){
        } else if(nombre.size()<8){
        } else if(nombre.substr(nombre.size()-8,nombre.size())=="reto.com"){
            cout<<nombre<<":";
		    for(string ipDestino: conexionesSalientes){
			    cout<<ipDestino<<",";
		    }
		    cout<<endl;
        }
	}
};

int main(){
  //Cargar el archivo csv
  cargarDatos("datosEquipo2.csv");
  //Creacion del Diccionario
	unordered_map<string, ConexionesComputadora> cnx;
	for(Record r:data){
		if(cnx.find(r.ipFuente)==cnx.end()){
			ConexionesComputadora a(r.ipFuente, r.nombreFuente);
			cnx[r.ipFuente]=a;
		}
		cnx[r.ipFuente].conexionesS(r.ipDestino);
    
    if(cnx.find(r.ipDestino)==cnx.end()){
			ConexionesComputadora a(r.ipDestino, r.nombreDestino);
			cnx[r.ipDestino]=a;
		}
		cnx[r.ipDestino].conexionesE(r.ipFuente);
	}

  //Nombres que no pertenecen al dominio reto.com
    unordered_set<string> anomalyNames;
    unordered_set<string> ipAndNames;
    unordered_set<string> ipAnomaly;
    for(int i=0;i<data.size();i++){
       if(data[i].nombreFuente.substr(data[i].nombreFuente.size()-8,data[i].nombreFuente.size())!="reto.com" ){
            ipAndNames.insert(data[i].nombreFuente+":"+data[i].ipFuente);
            anomalyNames.insert(data[i].nombreFuente);
            ipAnomaly.insert(data[i].ipFuente);
        } else if(data[i].nombreDestino == "-"){
            
        } else if(data[i].nombreDestino.size()<8){
            ipAndNames.insert(data[i].nombreDestino+":"+data[i].ipDestino);
            anomalyNames.insert(data[i].nombreDestino);
            ipAnomaly.insert(data[i].ipDestino);
        } else if(data[i].nombreDestino.substr(data[i].nombreDestino.size()-8,data[i].nombreDestino.size())!="reto.com"){
            ipAndNames.insert(data[i].nombreDestino+":"+data[i].ipDestino);
            anomalyNames.insert(data[i].nombreDestino);
            ipAnomaly.insert(data[i].ipDestino);
        }
    }
    cout<<anomalyNames.size()<<endl;
    cout<<ipAnomaly.size()<<endl;
    cout<<ipAndNames.size()<<endl;

    for(string elemento:ipAndNames){
		  cout<<elemento<<endl;
	  }

    /*
    De las computadoras pertenecientes al dominio reto.com determina la cantidad de ips que tienen al menos una conexión entrante.
    */
    unordered_set<string> entrantesUnicas;
    for(int i=1;i<=254;i++){
      string si= to_string(i);
      for( string s:cnx["172.24.133."+si].conexionesEntrantes){ 
        entrantesUnicas.insert(s);
      }
    }

    cout<<"Determina la cantidad de ips que tienen al menos una conexión entrante: "<<endl<<entrantesUnicas.size()<<endl;


    /*Toma algunas computadoras internas que no sean server.reto.com o el servidor dhcp. 
    Obten las ip unicas de las conexiones entrantes.
    */
    unordered_set<string> ipUnicasAlexander;
    //Ip de Alexander.reto
    cout<<"IPs Unicas de Alexander (172.24.133.67): "<<endl;
    for(string s:cnx["172.24.133.67"].conexionesEntrantes){
      ipUnicasAlexander.insert(s);
    }
    for(string elemento:ipUnicasAlexander){
		  cout<<elemento<<endl;
	  }

    //Ip de Donna.reto 172.24.133.82
    cout<<"IPs Unicas de Donna (172.24.133.82): "<<endl;
    unordered_set<string> ipUnicasDonna;
    for( string s:cnx["172.24.133.82"].conexionesEntrantes){
      ipUnicasDonna.insert(s);
    }
    for(string elemento:ipUnicasDonna){
		  cout<<elemento<<endl;
	  }
    //Ip de Kathleen.reto
    cout<<"IPs Unicas de Kathleen (172.24.133.133): "<<endl;
    unordered_set<string> ipUnicasKathleen;
    for( string s:cnx["172.24.133.133"].conexionesEntrantes){
      ipUnicasKathleen.insert(s);
    }
    for(string elemento:ipUnicasKathleen){
		  cout<<elemento<<endl;
	  }

  
    cout<<"IPs Unicas de Jeff (172.24.133.96): "<<endl;
    unordered_set<string> ipUnicasJeff;
    for( string s:cnx["172.24.133.96"].conexionesEntrantes){
      ipUnicasJeff.insert(s);
    }
    for(string elemento:ipUnicasJeff){
		  cout<<elemento<<endl;
	  }
    /*Para las ips encontradas en el paso anterior, determina si se han 
    comunicado con los datos encontrados en la pregunta 1.
    */
    cout<<"Pregunta 6"<<endl;
    unordered_set<string> comDatos;
    for(string s:cnx["172.24.133.84"].conexionesSalientes){
      for(string elemento:ipAnomaly){
        if(s==elemento){
          comDatos.insert(s);
        }
      }
    }
    for(string elemento:comDatos){
		  cout<<elemento<<endl;
	  }
    cout<<comDatos.size()<<endl;
    return 0;
}