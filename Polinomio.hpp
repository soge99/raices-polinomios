#pragma once
#include <vector>
#include <string>
using namespace std;

class Polinomio{
  private:
    int grado; //grado del polinomio
    string pol; //string del polinomio
    int largo; //largo entero, considerando signos como (**)
    vector<string> terminos;//vector de monomios formato terminos = [2x**3,3x**2,x]
    vector<string> terminosF;//vector de monomios en formato terminosF[exponente] = Base
    vector<float> raices;
  private:
    //obtiene todos los terminos del polinomio y los agrega a un vector. EJ: 2x**3 o 3x**2
    void obtenerTerminos();

    // Obtiene Base y exponente de un termino y añade a un vector en formato terminosF[exponente] = Base
    void formatUnTermino(string);
    //metodo auxiliar del metodo formatUnTermino que invierte una cadena de texto
    string invertirCadena(string);
    void detGrado(int);
    bool esCorrecto(char);
    string getCoef(string);
    string getExp(string);

    //Recorre un vector de terminos y añade a un vector terminosF con el formato terminosF[exponente] = Base
    void formatTerminos();

    //Metodos para encontrar raices de polinomios
    void verificarCero();
    void posiblesRaices();
    bool verificarRaiz(float);
    bool evaluarPolinomio(float);
    vector<int> ruffini(int n);
    bool esCotaMayor(vector<int>);
    bool esCotaMenor(vector<int>);
    int cotaMayor();
    int cotaMenor();
  
  public:
    // constructor, requiere un polinomio que provienede un arreglo de caracteres y un entero quereciba el largo de la cadena
    Polinomio(char* _pol[], int);
    // Funcion usada en el desarrollo para mostrar propiedades del polinomio
    void obtenerRaices();
    void mostrarRaices();
    void encontrarCotas();
};
