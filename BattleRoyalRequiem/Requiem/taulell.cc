#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cassert>

#include "taulell.h"
#include "common.h"
#include "atzar.h"

using namespace std;

const int MAX_POTENCIA_ATAC = 190;
const int MIN_POTENCIA_ATAC = 50;
const int FORCA_INICIAL = 400;
const int CAV_REGENERA = 10;

int inc_i[] = { 0, 0, 1, 1, 1, 0, -1, -1, -1 };
int inc_j[] = { 0, 1, 1, 0, -1, -1, -1, 0, 1 };

int posicio::DIM;

istream &operator>>(istream &is, posicio &p) {
  return is >> p.i >> p.j;
}

ostream &operator<<(ostream &os, posicio &p) {
  return os << " " << p.i << " " <<  p.j;
}

istream &operator>>(istream &is, casella &c) {
  return is >> c.terreny >> c.pers >> c.bando >> c.forca >> c.id;
}

ostream &operator<<(ostream &os, casella &c) {
  return os << " " << c.terreny << " " << c.pers
            << " " << c.bando << " " << c.forca << " " << c.id;
}


///> L'ordre que rep el robot situat en una posicio concreta
class ordre {
public:
  posicio pos;
  int dir;

  ordre() { }
  ordre(posicio pos, int dir) : pos(pos), dir(dir) { }

  ////canviar per tenir taulell no toroidal
  //posicio pas() {
  //  return posicio((pos.i + inc_i[dir]+posicio::DIM)%posicio::DIM,
  //               (pos.j + inc_j[dir]+posicio::DIM)%posicio::DIM);
  //}
  posicio pas() {
    return posicio(pos.i + inc_i[dir],
                   pos.j + inc_j[dir]);
  }
}; //OMER



ostream & operator<<(ostream &os, ordre &o)
{
  return os << " " << o.pos.i << " " << o.pos.j << " " << o.dir;
}

istream & operator>>(istream &is, ordre &o)
{
  return is >> o.pos.i >> o.pos.j >> o.dir;
}


template <typename T>
ostream &operator<<(ostream &os, vector<T> &v)
{
  os << " " << v.size();
  foreach(i,v) {  // (vector<T>::iterator i=v.begin(); i!=v.end(); i++)
    os << " " << *i;
  }
  return os;
}

template <typename T>
istream &operator>>(istream &is, vector<T> &v)
{
  v.clear();
  int size;
  is >> size;
  if (is) {
    for (int i=0;i<size;i++)
      {
        T t;
        is >> t;
        v.push_back(t);
      }
  }
  return is;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, pair<T1,T2> &p)
{
  os << " " << p.first << " " << p.second;
  return os;
}

template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1,T2> &p)
{
  is >> p.first >> p.second;
  return is;
}


template <typename T1, typename T2>
ostream &operator<<(ostream &os, map<T1,T2> &m)
{
  os << " " << m.size();
  foreach(i,m) {  // (vector<T>::iterator i=v.begin(); i!=v.end(); i++)
    os << " " << i->first << " " << i->second;
  }
  return os;
}

template <typename T1, typename T2>
istream &operator>>(istream &is, map<T1,T2> &m)
{
  m.clear();
  int size;
  if (is >> size) {
    for (int i=0;i<size;i++)
      {
        T1 t1; T2 t2;
        is >> t1 >> t2;
        m[t1] = t2;
      }
  }
  return is;
}



/*
ostream &operator<<(ostream &os, casella &c)
{
  return os << " " << c.terreny << " " << c.pers << " " << c.bando << " " << c.forca;
}

istream &operator>>(istream &is, casella &c)
{
  return is >> c.terreny >> c.pers >> c.bando >> c.forca;
}*/





void Taulell::print_as_player(int n)
{
  if (n>=1 and n<=4) {print_as=n;}
}

void Taulell::rota(posicio &pos, int bando) {
  if (bando==1) return;
  else if (bando==2)
    {
      int a=pos.i;
      pos.i = DIM - pos.j -1;
      pos.j = a;
    }
  else if (bando==3)
    {
      pos.i = DIM - pos.i -1;
      pos.j = DIM - pos.j -1;
    }
  else if (bando==4)
    {
      int a=pos.i;
      pos.i = pos.j;
      pos.j = DIM - a -1;
    }
  return;
}

void Taulell::rotainv(posicio &pos, int bando)
{
  if (bando==1) return;
  else if (bando==2) rota(pos, 4);
  else if (bando==3) rota(pos, 3);
  else if (bando==4) rota(pos, 2);
  return;
}

posicio Taulell::posicio_ini(int bando) {
  posicio pos;
  do {
    pos.i = 1+A.tria(2*DIM/5 - 2);
    pos.j = 1+A.tria(2*DIM/5 - 2);
    rotainv(pos, bando);
  } while (m(pos).terreny==-1 or m(pos).pers);
  return pos;
}


bool Taulell::amenaca(posicio pos, int bando) {
  for (int dir = EST; dir <= NE; ++dir) {
    posicio pos2 = ordre(pos, dir).pas();
    if (not pos2.fora() and m(pos2).pers == CAV and m(pos2).bando != bando)
      return true;
  }
  return false;
}


//fem espiral: a la primera passada, evitem amenaces;
//en la segona passada, acceptem amenaces
posicio Taulell::posicio_spawn(int bando) {
  posicio pos(DIM/5, DIM/5);
  posicio rpos = pos;
  rotainv(rpos, bando);
  if (!m(rpos).pers and not amenaca(rpos, bando)) return rpos;

  for (int intent=0;intent<2;++intent) {
    bool evita_amenaca = intent==0; //al primer intent, evitem amenaces
    for (int radi=1; radi<DIM/5; radi++) {
      pos.i=DIM/5+radi; pos.j=DIM/5+radi;
      int dircercle[4] = {NORD, OEST, SUD, EST};
      for (int d = 0; d<4; ++d) {
        for (int r = 0; r<radi*2; ++r) {
          posicio rpos = pos;
          rotainv(rpos, bando);
          if (!m(rpos).pers and
              not (evita_amenaca and amenaca(rpos, bando))) return rpos;

          pos = ordre(pos, dircercle[d]).pas();
        }
      }
    }
  }
  assert(0);
  return posicio(0,0);  //per tornar algo, no fara falta.
}


void Taulell::mou(posicio pos, int dir, int bando, set<int> &aux,
                  set_posicio &atacades) {

  if (pos.fora() or              //la posicio ha de ser legal
      !m(pos).pers or            //la posicio no te un personatge
      m(pos).bando!=bando or     //no es del meu bando
      aux.find(m(pos).id)!=aux.end() or     //ja ha estat mogut!
      dir<=0 or dir>8)        //direccio no valida!
    return;

  //ha rebut ordre !=9 (si no, no s'hauria cridat mou). Per tant,
  //conta com si s'hagues mogut a efectes de recuperar vida
  aux.insert(m(pos).id);

  dir += 2*(bando-1);
  if (dir > NE) dir -= NE;  //la direccio s'ha de rotar.

  posicio pos2 = ordre(pos, dir).pas();
  //si esta fora o te mur, no podem anar-hi
  if (pos2.fora() or m(pos2).terreny==-1) return;

  //si s'ha atacat, ningu hi pot anar-hi
  if (atacades.find(pos2)!=atacades.end()) return;

  if (m(pos).pers == PAG) {
    //em demanen que mogui un pages

    if (m(pos2).pers) return;
    m(pos).pers = 0;
    --n_caselles[m(pos2).terreny];
    ++n_caselles[bando];
    m(pos2).pers = PAG;
    m(pos2).terreny = m(pos2).bando = bando;
    m(pos2).id = m(pos).id;
    m(pos).id=0;
    personatges[m(pos2).id]=pos2;

    return;
  }

  //em demanen que mogui un cavaller. Si no te oposicio...
  if (!m(pos2).pers) {
    m(pos).pers = 0;
    m(pos2).pers = CAV;
    m(pos2).bando = bando;
    m(pos2).forca = m(pos).forca;
    m(pos2).id = m(pos).id;
    m(pos).id = 0;
    personatges[m(pos2).id]=pos2;

    return;
  }

  if (m(pos2).bando == bando) return;
  //intentar atacar a un dels seus... desvergonyits.

  if (m(pos2).pers == PAG) {
    //je je, sang i destruccio.

    atacades.insert(pos2);   //en aquesta casella ja no es pot moure ningu
    personatges.erase(m(pos2).id);
    m(pos2).pers = 0;
    m(pos2).id = 0;
    --n_pagesos[m(pos2).bando];
    ++n_pagesos[bando];
    posicio pos3 = posicio_spawn(bando);
    if (m(pos3).terreny!=bando)
      {
        --n_caselles[m(pos3).terreny];
        ++n_caselles[bando];
      }
    last_id++;
    m(pos3).id = last_id;
    personatges[m(pos3).id]=pos3;
    aux.insert(last_id);  //que no facin trampes... no pot moure aquest pages.
    m(pos3).pers = PAG;
    m(pos3).terreny = m(pos3).bando = bando;
    return;
  }


  //intentem atacar a un cavaller enemic!
  m(pos2).forca -= A.tria(MAX_POTENCIA_ATAC+1-MIN_POTENCIA_ATAC)+MIN_POTENCIA_ATAC;
  if (m(pos2).forca > 0) return;
  atacades.insert(pos2);
  m(pos2).pers = 0;
  personatges.erase(m(pos2).id);
  m(pos2).id = 0;

  --n_cavallers[m(pos2).bando];
  ++n_cavallers[bando];
  posicio pos3 = posicio_spawn(bando);
  m(pos3).pers = CAV;
  m(pos3).bando = bando;
  m(pos3).forca = FORCA_INICIAL;
  last_id++;
  m(pos3).id = last_id;
  personatges[m(pos3).id]=pos3;
  aux.insert(last_id); //que no faci trampes moguent aquest cavaller.
}


Taulell::Taulell(int _NUMTORNS, int _LLAVOR,
                 int _DIM,  int _PAGESOS, int _CAVALLERS):
  NUMTORNS(_NUMTORNS), LLAVOR(_LLAVOR), DIM(_DIM),
  PAGESOS(_PAGESOS), CAVALLERS(_CAVALLERS)
{
  print_as=1;
  for (int i=0;i<5;i++) quad_i[i]=quad_j[i]=0;
  quad_i[3]=quad_i[4]=quad_j[2]=quad_j[3]= DIM/2;
  last_id=0;

  //si DIM==-1 es que s'ha cridat amb el constructor per
  //defecte. No fa falta que iniciem una partida.
  if (DIM!=-1)
    {
      posicio::DIM=DIM;

      A = atzar(LLAVOR);
      Map = VVC(DIM, vector<casella>(DIM, casella(0, 0, 0, 0)));

      //afegim els murs: bordes...
      for (int i=0;i<DIM;++i) {
        m(posicio(i,0)).terreny = -1;
        m(posicio(i,DIM-1)).terreny = -1;
        m(posicio(0,i)).terreny = -1;
        m(posicio(DIM-1,i)).terreny = -1;
      }

      //i random...
      if (0) {	// codi ADARoyale
	      int nummurs = A.tria(3)+A.tria(4)+A.tria(5)+3;
	      for (int i=0; i<nummurs; ++i) {
	        bool vertical = A.tria(2)==0;
	        int fixed = 2*DIM/5 + A.tria(DIM/5);
	        int from = DIM/8+A.tria(DIM/2);
	        int to = from+2+A.tria(6);
	        if (A.tria(2)==0) {
	          from = DIM-1-from;
	          to = DIM-1-to;
	          swap(from,to);
	        }
	        for (int i=from;i<=to;++i) {
	          posicio pos;
	          if (vertical) pos = posicio(i, fixed);
	          else pos = posicio(fixed, i);
	          m(pos).terreny = -1;
	        }
	      }
	  } else {
		  // codi Requiem
		  // de moment, poso això, si cal, ja ho canviaré
		  for (int i=4; i<DIM-4; ++i) if (i < DIM/2-3 or i > DIM/2+3) {
				posicio p1(i, DIM/2);
				if (A.tria(4)) m(p1).terreny = -1;
				posicio p2(DIM/2, i);
				if (A.tria(4)) m(p2).terreny = -1;
		  }
		  for (int i=DIM/3; i<2*DIM/3; ++i) {
    		  for (int j=DIM/3; j<2*DIM/3; ++j) {
				posicio p1(i, j);
				if (A.tria(30)==0) m(p1).terreny = -1;
              }
          }
	  }

      //afegim els robots
      for (int bando = 1; bando <= 4; ++bando) {
        for (int rep = 0; rep < PAGESOS; ++rep) {
          posicio pos = posicio_ini(bando);
          m(pos).pers = PAG;
          m(pos).terreny = m(pos).bando = bando;
          last_id++;
          m(pos).id=last_id;
          personatges[last_id]=pos;
        }

        for (int rep = 0; rep < CAVALLERS; ++rep) {
          posicio pos = posicio_ini(bando);
          m(pos).pers = CAV;
          m(pos).bando = bando;
          m(pos).forca = FORCA_INICIAL;
          last_id++;
          m(pos).id=last_id;
          personatges[last_id]=pos;
        }
      }

      n_pagesos = vector<int>(5, PAGESOS);
      n_cavallers = vector<int>(5, CAVALLERS);
      n_caselles = vector<int>(5, PAGESOS);
      n_caselles[0] = DIM*DIM - 4*PAGESOS;

      torns_restants=NUMTORNS;
      torn_actual=1;

      torn = 1;  //li toca al jugador 1
    }
}

Taulell::VVC Taulell::mapa(int bando) {
  VVC aux = Map;
  for (int rep = 0; rep < bando - 1; ++rep) {
    for (int i = 0; i < DIM/2; ++i) {
      for (int j = 0; j < DIM/2; ++j) {
        casella a = aux[i][j];
        aux[i][j] = aux[j][DIM-i-1];
        aux[j][DIM-i-1] = aux[DIM-i-1][DIM-j-1];
        aux[DIM-i-1][DIM-j-1] = aux[DIM-j-1][i];
        aux[DIM-j-1][i] = a;
      }
    }
  }
  return aux;
}

/*string Taulell::juga(vector<pair<int,int> > &V, int bando) {
  if (bando != torn) return "Problema intern";

  //haig de executar les ordres.
  set<int> moguts;
  set_posicio atacades;
  for (int i=0;i<(int)V.size();i++)
    {
      if (personatges.find(V[i].first)!=personatges.end())
        {
          mou(personatges[V[i].first], V[i].second, bando, moguts, atacades);
        }
    }

  if (++torn > 4) {torn = 1; torns_restants--; torn_actual++;}

  return "";
  }*/

int Taulell::juganou(const vector<vector<PII> > &V) {

  vector<PIPII> all;    //(equip, PII)
  fori(V.size()) {      //les ordres del equip i
    forj(V[i].size()) { //9: ordre nula
      if (V[i][j].second!=9) all.push_back(PIPII(i, V[i][j]));
    }
  }

  vector<int> perm = A.permutacio(all.size());

  set<int> moguts;
  set_posicio atacades;
  foreach(i, perm) {
    int eq = all[*i].first;
    int id = all[*i].second.first;
    int dir = all[*i].second.second;

    if (personatges.find(id)!=personatges.end()) {
      mou(personatges[id], dir, eq+1, moguts, atacades);
    }
  }

  foreach(i, personatges)
    if (m(i->second).pers == CAV and               //si es un cavaller i
        moguts.find(i->first)==moguts.end()) {     //no s'ha mogut...
      m(i->second).forca = min(FORCA_INICIAL,
                               m(i->second).forca + CAV_REGENERA);
    }

  torns_restants--;
  torn_actual++;

  return 1;
}


//aixo escriu un mapa!
ostream &operator<<(ostream &os, Taulell &t) {
  Taulell::VVC mm=t.mapa(t.print_as);
  int ofs=(5-t.print_as)%4;

  //quatre dades basiques
  os << " " << t.DIM << " " << t.torn
     << " " << t.torns_restants
     << " " << t.torn_actual;

  //el mapa
  for (int i=0;i<t.DIM;i++)
    {
      string s(t.DIM, '0');
      for (int j=0;j<t.DIM;j++)
        {
          if (mm[i][j].terreny>0) s[j]=(mm[i][j].terreny-1+ofs)%4+1+'0';
          else s[j]=char(mm[i][j].terreny+'0'); //0 o /
        }
      os << " " << s;
    }

  //els jugadors
  os << " " << t.personatges.size();
  foreach(i, t.personatges) {
      posicio p=i->second;
      posicio rotp=p;
      t.rota(rotp, t.print_as);

      os << " " << i->first << " " << rotp.i << " " << rotp.j << " "
         << (t.m(p).bando-1+ofs)%4+1
         << " " << t.m(p).pers << " " << t.m(p).forca;
    }

  return os << " ";
}


ostream &write(ostream &os, Taulell &t) {
#define SER(x) os << t.x << endl;
  SER(Map) SER(n_pagesos) SER(n_cavallers) SER(n_caselles)
    SER(torn) SER(NUMTORNS) SER(LLAVOR) SER(DIM) SER(PAGESOS)
    SER(CAVALLERS) SER(print_as) SER(last_id) SER(personatges)
    SER(torns_restants) SER(torn_actual)
#undef SER

  return os;
}

istream &read(istream &is, Taulell &t) {
#define SER(x) if (is) is >> t.x;
  SER(Map) SER(n_pagesos) SER(n_cavallers) SER(n_caselles)
    SER(torn) SER(NUMTORNS) SER(LLAVOR) SER(DIM) SER(PAGESOS)
    SER(CAVALLERS) SER(print_as) SER(last_id) SER(personatges)
    SER(torns_restants) SER(torn_actual)
#undef SER

  posicio::DIM = t.DIM;

  return is;
}
/*

  friend istream &write(istream &is, Taulell &t);
  is >> t.map >> t.n_pagesos
     >> t.n_cavallers >> t.n_caselles
     >> t.torn >> t.NUMTORNS >> t.LLAVOR
     >> t.DIM >> t.PAGESOS >> t.CAVALLERS;
  posicio::DIM=t.DIM;
  return is;
  }*/


vector<int> Taulell::ids_robots(int bando) {
  vector<int> ids;
  foreach(i, personatges) {
    if (m(i->second).bando==bando) ids.push_back(i->first);
  }
  return ids;
}


bool llegeix_ordres(istream &iss, vector<PII> &v) {
  int n;
  iss >> n;

  v.clear();
  if (n<0 or n>100000) {
    //minima comprovacio de que no hi ha un error
    cerr << "Nombre d'ordres n=" << n << " erroni." << endl;
    return false;
  }

  v.resize(n);
  fori(n) {
    iss >> v[i].first >> v[i].second;
  }
  //s'assegura que les ordres es donen ordenadament
  sort(v.begin(), v.end());

  return iss;
}

