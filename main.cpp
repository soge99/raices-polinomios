#include <stdio.h> 
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Polinomio{
  private:
    int grado;
    string pol; //string del polinomio
    int largo; //largo entero, considerando signos como (**)
    vector<string> terminos;//vector de monomios
    vector<string> terminosF;
  private:
    string invertirCadena(string);
    void formatUnTermino(string);
    void formatTerminos();
    void obtenerTerminos();
  public:
    Polinomio(char* _pol[], int);
    int obtenerRaices();
    void showPol();
};

Polinomio::Polinomio(char* _pol[], int argc){
  for(int i = 1; i < argc; i++){
    pol += _pol[i];
  }
  largo = pol.length();
  grado = 0;

};

string Polinomio::invertirCadena(string cadena){
  int largo = cadena.length();
  string invert = "";
  for(int i = largo -1; i>= 0; i--){
    invert += cadena[i]; 
  }
  return(invert);
}
void Polinomio::obtenerTerminos(){
  string termino = "";
  int largoPol = pol.length();
  for(int i = largoPol-1; i >= 0; i--){
    if(pol[i] == '+'){
      terminos.push_back(invertirCadena(termino));
      termino = "";
    }else if(pol[i] =='-'){
      terminos.push_back(invertirCadena(termino + '-'));
      termino = "";
    }else if(i==0 && pol[i] !='-'){
      terminos.push_back(invertirCadena(termino + pol[0] ));
      termino = "";
    }else if(pol[i] !='+' && pol[i] !='-'){
      termino+=pol[i];
    }
  }
};
//falta contemplar terminos tipo {x,-x,n, nx,-nx}
void Polinomio::formatUnTermino(string cadena){
  string tempBase = "";
  string tempExp = "";
  //int numTerminos = terminos.size();
  int largoCadena = cadena.length();
  if(largoCadena == 1){
    if(cadena[0] == 'x'){
      tempBase = '1';
      tempExp = '1';
      grado = 1;
    }else{
      tempBase = cadena[0];
      tempExp = '0';
      grado = 0;
    }
  }else{
    for(int i =largoCadena -1; i>=0; i--){
      if(cadena[i] != '*' ){
        tempExp += cadena[i];
    
      }else{
        if(grado< stoi(tempExp)){
          grado = stoi(tempExp);
          terminosF.resize(grado+1);
        }
        break; 
      }
    }
    for(int i = 0; i < largoCadena; i++){
      if(cadena[i] != 'x'){
        tempBase += cadena[i];
      }else{
        break;
      }
    }
  }
  terminosF[stoi(tempExp)]=tempBase;
};

void Polinomio::formatTerminos(){
  int numTerminos = terminos.size();
  int numTerminosF = terminosF.size();
  cout<<"N terminos:"<<numTerminos<<endl;
  
  for (int i =0; i < numTerminos; i++){
    formatUnTermino(terminos[i]);
  }
  for (int i =0; i < numTerminosF; i++){
    cout<<terminosF[i]<<endl;
  }
};

void Polinomio::showPol(){
  obtenerTerminos();
  formatTerminos();
  cout<<"polinomio: "<<pol<<endl;
  //cout<<"Largo string: "<<largo<<endl;
  cout<<"grado: "<<grado<<endl;
  int largo = terminos.size();
  int largo2 = terminosF.size();
  cout<<"terminos-------------------------"<<endl;
  for(int i = 0; i<largo; i++){
    cout<<terminos[i]<<endl;
  }
  cout<<"format test---------------------"<<endl;
  for(int i = 0; i<largo2; i++){
    cout<<terminosF[i]<<endl;
  }
  
};

int main(int argc, char* argv[]) {
  Polinomio p1 = Polinomio(argv,argc);
  p1.showPol();
  return 0;
}