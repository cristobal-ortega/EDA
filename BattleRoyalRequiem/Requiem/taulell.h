#ifndef TAULELL_H
#define TAULELL_H

/* #include <iostream> */
/* #include <iomanip> */
/* #include <vector> */
/* #include <algorithm> */
/* #include <set> */
/* #include <map> */

/* #include "common.h" */
/* #include "atzar.h" */

#include <set>

#include "robots.h"

using namespace std;

//llegeix les ordres escrites en el format de robots.h
bool llegeix_ordres(istream &iss, vector<PII> &v);

class casella {
public:
  int terreny, pers, bando, forca, id;  //terreny==-1: mur

  casella() {}
  casella(int t, int p, int b, int f, int i=0)
    : terreny(t), pers(p), bando(b), forca(f), id(i) { }
};


///> Parell de valors (i,j), amb auto-coneixement de les mides del taulell
struct posicio {
  int i, j;
  static int DIM;

  posicio() { }
  posicio(int i, int j) : i(i), j(j) { }

  bool fora() {
    return ((i < 0) or (i >= DIM) or (j < 0) or (j >= DIM));
  }
};

struct compare_posicio
{
  bool operator()(const posicio &p1, const posicio &p2)
  {
    return p1.i<p2.i or (p1.i==p2.i and p1.j<p2.j);
  }
};

typedef set<posicio, compare_posicio> set_posicio;

class Taulell {
public:
  typedef vector<vector<casella> > VVC;

  atzar A;
  VVC Map;
  vector<int> n_pagesos, n_cavallers, n_caselles;
  int torn;
  int NUMTORNS;
  int LLAVOR;
  int DIM;
  int PAGESOS;
  int CAVALLERS;
  int print_as;
  int last_id;

  int quad_i[5];
  int quad_j[5];

  map<int, posicio> personatges;
  int torns_restants;
  int torn_actual;

  /** Des de quin punt de vista \a n, de 1 a 4, ha de serialitzar-se amb
      el operator << */
  void print_as_player(int n);

  /** Retorna la casella d'una posicio \a pos */
  inline casella &m(posicio pos) { return Map[pos.i][pos.j]; }

 private:

  /** Tradueix una posicio \a pos del sistema global al sistema 
      vist per l'equip \a bando */
  void rota(posicio &pos, int bando);

  /** Tradueix una posicio \a pos vista per l'equip \a bando 
      a una posicio del sistema global */
  void rotainv(posicio &pos, int bando);

  /** Tria una posicio inicial a l'atzar per a un jugador de
   l'equip \a bando*/
  posicio posicio_ini(int bando);

  /** Mira si la posicio \a pos esta amenacada pel bandol \a bando */
  bool amenaca(posicio pos, int bando);
  
  /** Tria una posicio (espiral) no amenacada dintre del bandol \a bando;
      si no pot, en tria una d'amenacada. */
  posicio posicio_spawn(int bando);

  /** Ordre d'un \a bando: mou el robot de la posicio \a pos en la
      direccio \a dir, control.lant que el robot no sigui algun dels robots
      moguts de \a aux. A mes, vigila que cap robot ocupi una de les
      posicions \a atacades, que es un conjunt de posicions on ha mort
      un robot aquest torn i, per tant, ningu pot posar-s'hi */
  void mou(posicio pos, int dir, int bando,
	   set<int> &aux, set_posicio &atacades);


public:

  /** Crea un taulell. S'admet el constructor buit, per si es te un taulell
      serialitzat */
  Taulell(int _NUMTORNS = 100, int _LLAVOR = 4321,
	  int _DIM = -1,  int _PAGESOS = 0, int _CAVALLERS = 0);
  
  inline int num_pagesos(int bando) {return n_pagesos[bando];}
  inline int num_cavallers(int bando) {return n_cavallers[bando];}
  inline int num_caselles(int bando) {return n_caselles[bando];}
  inline int puntuacio(int bando) {
    if (n_caselles[bando]>0) return n_caselles[bando];
    else {
      if (n_pagesos[bando]+n_cavallers[bando]==0) return -1;
      else return 0;
    }
  }

  /** Retorna els ids dels robots del bando \a bando */
  vector<int> ids_robots(int bando);
  
  /** Retorna el mapa actual tal i com el veu el bandol \a bando */
  VVC mapa(int bando);

  /* ANTIGA: Executa el torn corresponent al bandol \a bando, on \a V
      es el seu vector d'ordres */
  //  string juga(vector<pair<int,int> > &V, int bando);

  /** Executa el torn de tots els bandols, on \a V es el vector
      de vectors d'ordres. Una ordre de tipus '9' indica que el
      personatge en concret es queda quiet.*/
  int juganou(const vector<vector<PII> > &V);

  /** Transforma taulell en mapa */
  friend ostream &operator<<(ostream &os, Taulell &t);

  /** Autentica serialitzacio del taulell */
  friend istream &read(istream &is, Taulell &t);
  friend ostream &write(ostream &os, Taulell &t);
};

#endif
