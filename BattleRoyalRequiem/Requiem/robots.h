#ifndef ROBOTS_H
#define ROBOTS_H

/*********************************************/
/*                                           */
/*  No toquis res d'aquest fitxer! La versio */
/* definitiva del teu programa es compilara  */
/* utilitzant un fitxer identic a aquest, de */
/* manera que no et serveix per a res        */
/* modificar-lo.                             */
/*                                           */
/*                                           */
/*********************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "atzar.h"
#include "common.h"

using namespace std;

/*********************************************************************/
/* EL CODI QUE HI HA EN AQUEST FITXER NO EL NECESSITEU MIRAR PER RES */
/*********************************************************************/


const int PAG = 1;
const int CAV = 2;


const int EST = 1;
const int SE = 2;
const int SUD = 3;
const int SO = 4;
const int OEST = 5;
const int NO = 6;
const int NORD = 7;
const int NE = 8;
const int RES = 9;


/** All the information of a robot */
struct t_robot
{
  int id;     ///< (id>0)
  int i;      ///< row (i>=0)
  int j;      ///< column (col>=0)
  int equip;  ///< team (1-4); my team is always 1.
  int model;  ///< robot model (PAG, CAV)
  int vida;   ///< life points (life>0)

  ///< return an invalid robot
  static t_robot invalid() {
    t_robot r;
    r.id = r.i = r.j = r.equip = r.model = r.vida = -1;
    return r;
  }
};


const int pas_i[10]={0, 0, 1, 1, 1, 0, -1, -1, -1, 0};
const int pas_j[10]={0, 1, 1, 0, -1, -1, -1, 0, 1, 0};



/** All the information of the game board where the match takes place. */
class Mapa
{

 public:
  /** Information of a square */
  struct casella
  {
    int equip;   ///< the owner: -1 if wall, 0 if free, 1-4 otherwise
    int id;      ///< the robot placed on the square: -1 if wall, 0 if free, id>0 otherwise
  };

  Mapa() {}

  string whoami;

 private:
  int D;                      ///< dimensions del taulell (DxD)
  vector<vector<casella> > M; ///< matriu amb les caselles
  vector<t_robot> F;          ///< vector amb les fitxes (robots)
  atzar A;                    ///< per si algu necessita fer randoms

  int trn_actual;             ///< torn actual
  int trns_rstnts;            ///< torns que resten per acabar la partida

  map<int, int> Ordres;     ///< mapa amb les ordres <id, moviment>
  vector<int> ordreOrdres;  ///< ordre en el que es donen les ordres, rodolí
  map<int, int> Robots;     ///< mapa de robots <id, posicio a F>
  vector<int> n_pag,        ///< número de robots T80
    n_cav,                  ///< número de robots T100
    n_territoris;           ///< número de caselles ocupades

  vector<vector<int> > id_pag,  ///< ids dels robots T80, per equips
    id_cav;                     ///< ids dels robots T100, per equips

  ostringstream log;        ///< ostream on loguegem els missatges d'error


  /** Precalcula quants robots hi ha de cada tipus i de cada equip.
      Assumeix que n_pag i n_cav estan ben calculades. */
  void calcula_id_pag_id_cav() {
    id_pag.resize(5);
    id_cav.resize(5);
    for(int k=1; k<=4; ++k) {
      id_pag[k].resize(n_pag[k]);
      id_cav[k].resize(n_cav[k]);
    }

    vector<vector<int> > vj(2, vector<int>(5));
    for (int i=0;i<(int)F.size();i++) {
      int equip = F[i].equip;  //1--4

      if (F[i].model==PAG)
	id_pag[equip][vj[0][equip]++] = F[i].id;
      else if (F[i].model==CAV)
	id_cav[equip][vj[1][equip]++] = F[i].id;
    }
  }

  /** Serialitzacio de la classe */
  friend istream &operator>>(istream &in, Mapa &m);

  /** Mira si estem dins del taulell */
  inline bool dins(int i, int j)
  {
    return (i>=0 and i<D and j>=0 and j<D);
  }

  /** Imprimeix un error per la sortida estandard */

  void runtime_error(const string namefunc, const string pars,
	     const string msg) {
    cerr << "ERROR " << whoami << ", ";
    cerr << namefunc << "(" << pars << "): " << msg << "." << endl;
  }

 public:
  /** Is there some robot with this \a id ?*/
  bool existeix(int id)
    {
      if (id<0) {
	ostringstream pars; pars << id;
	runtime_error("existeix", pars.str(), "No robot with negative id");
	return false;
      }

      return Robots.find(id)!=Robots.end();
    }

  /** Is there some robot at square (\a i, \a j)? */
  bool existeix(int i, int j)
    {
      if (not dins(i,j)) {
	ostringstream pars; pars << i << "," << j;
	runtime_error("existeix", pars.str(), "Square out of bounds");
	return false;
      }
      return (M[i][j].id>0);
    }

 private:
  /** The size of the board (by default, 50) */
  int mida()
    {
      return D;
    }

 public:
  /** The robot with identifier \a id, or an invalid robot if
      there is no such robot. */
  t_robot robot(int id)
    {
      if (existeix(id)) return F[Robots[id]];

      ostringstream pars; pars << id;
      runtime_error("robot", pars.str(), "Robot does not exist");
      return t_robot::invalid();
    }

  /** The robot at the square (\a i, \a j), or an invalid robot
      if there is none. */
  t_robot robot(int i, int j)
    {
      if (existeix(i, j)) return F[Robots[M[i][j].id]];

      ostringstream pars; pars << i << "," << j;
      runtime_error("robot", pars.str(), "No robot at given square");
      return t_robot::invalid();
    }

  /** The team that owns the square (\a i, \a j); if the square
      has no owner, returns 0; if the square is a wall or the
      indices (\a i, \a j) are invalid, returns -1. */
  int color(int i, int j)
    {
      if (dins(i,j)) {
	return M[i][j].equip;
      }

      ostringstream pars; pars << i << "," << j;
      runtime_error("color", pars.str(), "Square out of bounds");
      return -1;
    }

  /** Give the robot \a id the order to move in the direction \a mov
      (EST=1, SE=2, SUD=3, SO=4, OEST=5, NO=6, NORD=7, NE=8, RES=9). Returns
      \a true if the order is valid (you own the robot with the given
      \a id, the direction \a mov is valid (mov>=1 and mov<=9), the
      robot is not ordered to move to a wall or outside the board, 
      the robot have not received a previous order) */
  bool ordena(int id, int mov)
  {
#define ERROR(mess)  {			  \
    ostringstream pars; pars << id << "," << mov; \
    runtime_error("ordena", pars.str(), mess); \
}
   
    if (not existeix(id)) {
      ostringstream err; err << "No robot with id=" << id;
      ERROR(err.str());
      return false;
    }

    t_robot r=robot(id);
    if (r.equip!=1) {
      ERROR("The robot is not yours");
      return false;
    }

    if (mov<=0 or mov>9) {
      ERROR("Invalid movement direction");
      return false;
    }

    if (Ordres.find(id)!=Ordres.end()) {
      ERROR("The robot has already received an order");
      return false;
    }

    int ni = r.i+pas_i[mov];
    int nj = r.j+pas_j[mov];
    if (not dins(ni, nj)) {
      ERROR("You are asking the robot to move outside the board");
      return false;
    }

    if (M[ni][nj].equip<0) {
      ERROR("You are asking the robot to move to a wall");
      return false;
    }
    

    Ordres[id] = mov;
    ordreOrdres.push_back(id);
    return true;

#undef ERROR
  }

  /** Number of squares owned by the team \a e; number
      of free squares if \a e is 0; number of walls if \a e is -1.

      If \e is invalid, returns -1.*/
  int num_caselles(int e)
    {
      if (e>=0 and e<=4) return n_territoris[e];
      if (e==-1) {
	int num = D*D;
	for (int i=0;i<5;++i) num-=n_territoris[i];
	return num;
      }

      ostringstream pars; pars << e;
      runtime_error("num_caselles", pars.str(), "Wrong parameter");
      return -1;
    }

  /** A vector with the id's of all the robots of type T80PAG owned
      by team \a e.

      Return an empty vector if \a e is invalid.

      Complexity: the first time you call \a T80PAG or \a T100CAV
      it takes time \f$O(n)\f$, where \f$n\f$ is the total number of
      robots in the board. Subsequent calls take only constant time. */
  vector<int> T80PAG(int e)
    {
      if (e<=0 or e>4) {
	ostringstream pars; pars << e;
	runtime_error("pagesos", pars.str(), "Wrong team");
	return vector<int>();
      }
      if (id_pag.size()) return id_pag[e];

      calcula_id_pag_id_cav();
      return id_pag[e];
    }

  vector<int> pagesos(int e) {return T80PAG(e);}

  /** A vector with the id's of all the robots of type T100CAV owned
      by team \a e.

      Return an empty vector if \a e is invalid.

      Complexity: the first time you call \a T80PAG or \a T100CAV
      it takes time \f$O(n)\f$, where \f$n\f$ is the total number of
      robots in the board. Subsequent calls take only constant time. */
  vector<int> T100CAV(int e) {
    if (e<=0 or e>4) {
      ostringstream pars; pars << e;
      runtime_error("cavallers", pars.str(), "Wrong team");
      return vector<int>();
    }
    if (id_cav.size()) return id_cav[e];

    calcula_id_pag_id_cav();
    return id_cav[e];
  }

  vector<int> cavallers(int e) {return T100CAV(e);}
      
  /** A random number between 0 and \f$n-1\f$, both inclusive. */
  int random(int n) {
    if (n<=0) {
      ostringstream pars; pars << n;
      runtime_error("random", pars.str(), "Wrong parameter");
      return -1;
    }

    return A.tria(n);
  }
  
  /** Number (>0) of remaining turns before the match ends.  */
  int torns_restants() {
    return trns_rstnts;
  }

  /** Current turn. The first turn is the turn 1.  */
  int torn_actual() {
    return trn_actual;
  }

  void escriu_ordres(ostream &os);
};

#endif
