#include <stdio.h> 
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

#include "Polinomio.hpp"

#define delta 0.000001


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
};

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
      terminosF.resize(grado+1);
    }else{
      tempBase = cadena[0];
      tempExp = '0';
      grado = 0;
      terminosF.resize(grado+1);
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
  //int numTerminosF = terminosF.size();
  cout<<"N terminos:"<<numTerminos<<endl;
  
  for (int i =0; i < numTerminos; i++){
    formatUnTermino(terminos[i]);
  }
  /*
  for (int i =0; i < numTerminosF; i++){
    cout<<terminosF[i]<<endl;
  }
  */
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

void Polinomio::mostrarTerminos(){
  int largo = terminosF.size();
  for (int i=0; i < largo ; i++){
    if(terminosF[i] == "") cout << "termino " << i << ": " << "0" << endl;
    else{
    cout << "termino " << i << ": " << terminosF[i] << endl;

    }
  }
}

void Polinomio::mostrarRaices(){
  int largo = raices.size();
  cout << "=== Resultado ===" << endl << endl;
  for(int i=0; i<largo; i++){
    cout << "x" << i+1 << " = " << raices[i] << endl;
  }
  /*
  cout << endl << "=== Integrantes ===" << endl;
  cout <<"Roberto Albornoz" << endl;
  cout <<"Kevin Peralta" << endl;
  cout <<"Sebastián Santelices" << endl;
  */
}

void Polinomio::verificarCero(){ // verifica si 0 es raíz 
  if(grado>0 && terminosF[0] == ""){
    raices.push_back(0);
    while(grado>0 && terminosF[0] == ""){
      grado--;
      terminosF.erase(terminosF.begin());
    }
  }
}

bool Polinomio::verificarRaiz(float raiz){
  largo = raices.size();
  for (int i=0; i<largo ; i++){
    if(raiz == raices[i]) return true;
  }
  return false;
}

bool Polinomio::evaluarPolinomio(float n){
  int largo = terminosF.size();
  float suma = 0;
  for (int i=0; i<largo ; i++){
    if(terminosF[i]!=""){
      suma += stoi(terminosF[i])*(pow(n,i));
    }
  }
  //cout << "n=" << n << " - " << suma << endl;
  if( suma == 0 || (-1*delta < suma && suma < delta )) return true;
  return false;
}

void Polinomio::posiblesRaices(){
  vector<float> multiplosTi;
  vector<float> multiplosCi;
  vector<float> posiblesRaices;
  if(grado > 0){
    int terminoIndependiente, coeficienteInicial;
    if(stoi(terminosF[0])<0){
      terminoIndependiente = -1*stof(terminosF[0]);
    }else{
      terminoIndependiente = stof(terminosF[0]);
    }

    if(stoi(terminosF[terminosF.size()-1]) < 0){
      coeficienteInicial = -1*stof(terminosF[terminosF.size()-1]);
    }else{
      coeficienteInicial = stof(terminosF[terminosF.size()-1]);
    }
    multiplosTi.push_back(1);
    multiplosTi.push_back(terminoIndependiente);
    multiplosCi.push_back(1);
    multiplosCi.push_back(coeficienteInicial);
    
    for (int i=2; i<terminoIndependiente/2 ; i++){
      if(terminoIndependiente % i == 0) multiplosTi.push_back(i);
    }
    for (int i=2; i<coeficienteInicial/2 ; i++){
      if(coeficienteInicial%i == 0) multiplosCi.push_back(i);
    }
    int largomti = multiplosTi.size();
    int largomci = multiplosCi.size();
    for (int i=0; i < largomti ; i++){
      for(int j = 0 ; j < largomci ; j ++){
        posiblesRaices.push_back(multiplosTi[i]/multiplosCi[j]);
      }
    }
    int largoRaices = posiblesRaices.size();
    //for(int i =0; i < largoRaices;i++) cout << posiblesRaices[i] << ", ";
    //cout << endl;
    for (int i = 0 ; i< largoRaices ; i++){
      if(evaluarPolinomio(posiblesRaices[i]) && !verificarRaiz(posiblesRaices[i])) {
        raices.push_back(posiblesRaices[i]);
        grado--;
      }
      if(evaluarPolinomio((-1)*posiblesRaices[i]) && !verificarRaiz((-1)*posiblesRaices[i])) {
        raices.push_back(-1*posiblesRaices[i]);
        grado--;
      }
    }
  }
}

void Polinomio::obtenerRaices(){ // renombrar a verificar cero
  verificarCero();
  posiblesRaices();
  mostrarRaices();
}