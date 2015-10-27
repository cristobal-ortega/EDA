#ifndef ATZAR_H
#define ATZAR_H

#include <vector>

using namespace std;


class atzar {
  private:

  void seguent();

 public:
  int llavor;

  atzar(): llavor(0) {}
  
  // inicialitza la llavor amb el valor donat
  atzar(int llavor);

  // retorna un real aleatori de [0, 1)
  double uniforme();

  // retorna un enter aleatori de [esquerra, dreta]
  int uniforme(int esquerra, int dreta);

  // retorna un real aleatori de [esquerra, dreta] amb dig digits
  double uniforme(int esquerra, int dreta, int dig);

  // retorna true amb probabilitat p
  bool probabilitat(double p);

  // retorna una permutació aleatòria de 0 .. n - 1
  vector<int> permutacio(int n);

  int tria(int n) { return (int)(uniforme()*(double)n); }
};


#endif
