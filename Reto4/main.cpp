// Reto 4
//Hecho por: DIEGO ARAQUE A01026037, OCTAVIO FENOLLOSA A01781042, YAREZZI GARCIA A01653133
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

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

unordered_map<string, int> conexionesPorDia(string fecha){
  unordered_map<string, int> anomalyNames;
    for(int i=0;i<data.size();i++){
       if(fecha == data[i].fecha && data[i].ipDestino.substr(0,10) != "172.24.133" && data[i].nombreDestino != "-"){
         if(anomalyNames.find(data[i].nombreDestino) == anomalyNames.end()){
          anomalyNames[data[i].nombreDestino]= 1;
         } else{
           int it=anomalyNames[data[i].nombreDestino];
           it++;
           anomalyNames[data[i].nombreDestino]= it;
         } 
      }
    }
    //for(auto c:anomalyNames){
      //cout<<c.first<<":"<<c.second<<endl;
	  //}
    return anomalyNames;
}

void top(int n, string f){
  map<int, vector<string> > topCNX;
  unordered_map<string, int> cnx = conexionesPorDia(f);
  cout<<"Para la fecha "<<f<<" el top "<<n<<" es:"<<endl;
  for(auto c:cnx){
    topCNX[c.second].push_back(c.first);
  }
  int i=0;
  for(auto it=topCNX.rbegin(); it!=topCNX.rend(); it++){
    if(i<n){
      cout<<it->first<<":";
      for(auto c:it->second){
        cout<<c<<", ";
      }
      cout<<endl;
    }
    i++;
  }
  cout<<endl;
}

int main(){
  cargarDatos("datosEquipo2.csv");
  /*for(auto c:conexionesPorDia("10-8-2020")){
    cout<<c.first<<":"<<c.second<<endl;
  }*/
  top(5,"10-8-2020");
  top(5,"11-8-2020");
  top(5,"12-8-2020");
  top(5,"13-8-2020");
  top(5,"14-8-2020");
  top(5,"17-8-2020");
  top(5,"18-8-2020");
  top(5,"19-8-2020");
  top(5,"20-8-2020");
  top(5,"21-8-2020");
	return 0;
}
