#include <stdio.h> 
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>

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

void Polinomio::detGrado(int exp){
  if(exp > grado){
    grado = exp;
  }
};

bool Polinomio::esCorrecto(char caracter){
  bool base = true;
  if(caracter == '*' || caracter == 'x'){
    base = false;
  }
  return(base);
}

string Polinomio::getCoef(string cadena){
  string tempBase = "";
  int largoCadena = cadena.length();
  bool seguir = true;
  for(int i = 0; i < largoCadena; i++){
    if(esCorrecto(cadena[i]) == false){
        seguir = false;
      }
    //obtiene la base de terminos del tipo 2x**3
    if(cadena[i] != 'x' && seguir){
      tempBase+=cadena[i];
    }else if(cadena[i] == 'x' && i ==0){
      tempBase='1';
    }else if(cadena[i]=='x' && cadena[i-1] == '-'){
      tempBase ="-1";
    }
  }
  return (tempBase);
};

string Polinomio::getExp(string cadena){ 
  string tempExp = "";
  int largoCadena = cadena.length();
  bool seguir = true;
  for(int i = largoCadena -1; i >= 0; i--){
      if(esCorrecto(cadena[i]) == false){
        seguir = false;
      }
      if(cadena[i] != '*' && seguir && cadena.find('x') != std::string::npos){
        tempExp+=cadena[i];
        tempExp=invertirCadena(tempExp);
        detGrado(stoi(tempExp));//determina el grado del polinomio con el exponente mas grande
      }else if(cadena[i] == 'x' && i ==0 && largoCadena == 1){
        tempExp='1';
        detGrado(stoi(tempExp));
      }else if(isdigit(cadena[i]) && esCorrecto(cadena[i]) && cadena.find('x') == std::string::npos){
        tempExp = "0";
        detGrado(stoi(tempExp));
      }else if(cadena[i] == 'x' && i == largoCadena-1){
        tempExp ="1"; 
        detGrado(stoi(tempExp));
      }
    }
    return(tempExp);
};

//falta contemplar terminos tipo {x,-x,n, nx,-nx}
void Polinomio::formatUnTermino(string cadena){
  string tempExp= getExp(cadena);
  string tempBase = getCoef(cadena);
  //cout<<"Base: "<< tempBase<<endl;
  //cout<<"Exp: "<< tempExp<<endl;
  try{
    terminosF.resize(grado+1);
    terminosF[stoi(tempExp)]=tempBase;
  }catch(int e){
    cout<<"Ocurrio un error redimensionando el vector, tamaño insuficiente o negativo "<<endl;
  }
  //cout<<"grado: "<<grado<<endl;
};

void Polinomio::formatTerminos(){
  int numTerminos = terminos.size();
  //int numTerminosF = terminosF.size();
  
  for (int i =0; i < numTerminos; i++){
    formatUnTermino(terminos[i]);
  }
  /*
  for (int i =0; i < numTerminosF; i++){
    cout<<terminosF[i]<<endl;
  }
  */
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
  cout << endl << "=== Integrantes ===" << endl << endl;
  cout <<"Roberto Albornoz" << endl;
  cout <<"Kevin Peralta" << endl;
  cout <<"Sebastián Santelices" << endl;
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
  if( suma == 0 || (-1*delta < suma && suma < delta )) return true;
  return false;
}

vector<int> Polinomio::ruffini(int n){
  int Grado = terminosF.size();
  int coef;
  int terminof;
  vector<int> ruffini;
  if(terminosF[Grado-1] == ""){
    ruffini.push_back(0);
  }else{
    ruffini.push_back(stoi(terminosF[Grado-1]));
  }
  for (int i=1; i<Grado ; i++){
    if(terminosF[Grado-1-i] == ""){
      terminof = 0;
    }else{
      terminof = stoi(terminosF[Grado-1-i]);
    }
    coef = n*ruffini[i-1] + terminof;
    ruffini.push_back(coef);
  }
  return ruffini;
}

void Polinomio::mostrarRuffini(){
  vector<int> ruf = ruffini(-1);
  largo = ruf.size();
  for (int i=0; i<largo; i++){
    cout<< ruf[i] << ", ";
  }cout << endl;
}

bool Polinomio::esCotaMayor(vector<int> ruff){
  int largo = ruff.size();
  for (int i=0; i<largo ; i++){
    if(ruff[i]<0) return false;
  }
  return true;
}

bool Polinomio::esCotaMenor(vector<int> ruff){
  int largo = ruff.size();
  for (int i=1; i<largo ; i++){
    if(ruff[i] == 0 && ruff[i-1] == 0) return false;
    if(ruff[i]*ruff[i-1]>0) return false;
  }
  return true;
}

int Polinomio::cotaMayor(){
  vector<int> resultadoRuff;
  for (int i=-500000; i<500000 ; i++){
    if(i!=0) i++;
    resultadoRuff=ruffini(i);
    if( esCotaMayor(resultadoRuff) ) return i;
  }
  return -500000;
}

int Polinomio::cotaMenor(){
  vector<int> resultadoRuff;
  for (int i=500000; i>-500000 ; i--){
    if(i==0) i--;
    resultadoRuff=ruffini(i);
    if(esCotaMenor(resultadoRuff)) return i;
  }
  return 500000;
}

void Polinomio::encontrarCotas(){
  int cMayor, cMenor;
  cMayor=cotaMayor();
  cMenor=cotaMenor();
  cout << "cota menor " << cMenor << " cota mayor " << cMayor << endl;
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
    for (int i=2; i<=terminoIndependiente/2 ; i++){
      if(terminoIndependiente % i == 0) multiplosTi.push_back(i);
    }
    for (int i=2; i<=coeficienteInicial/2 ; i++){
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
    for (int i = 0 ; i< largoRaices ; i++){
      if(evaluarPolinomio(posiblesRaices[i]) ) {
        grado--;
        if(!verificarRaiz(posiblesRaices[i])){
          raices.push_back(posiblesRaices[i]);
        }
      }
      if(evaluarPolinomio((-1)*posiblesRaices[i])) {
        grado--;
        if(!verificarRaiz((-1)*posiblesRaices[i])){
          raices.push_back(-1*posiblesRaices[i]);
        }  
      }
    }
  }
  sort(raices.begin(),raices.end());
}

void Polinomio::obtenerRaices(){ 
  obtenerTerminos();
  formatTerminos();
  verificarCero();
  posiblesRaices();
  mostrarRaices();
  encontrarCotas();
}