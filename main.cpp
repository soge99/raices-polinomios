#include "Polinomio.cpp"
#include <stdio.h> 
#include <string.h>
#include <vector>
#include <math.h>
using namespace std;


int main(int argc, char* argv[]) {
  Polinomio p1 = Polinomio(argv,argc);
  p1.obtenerRaices();
  return 0;
}