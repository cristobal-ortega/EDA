#ifndef AIBASE_H
#define AIBASE_H

#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "common.h"
#include "robots.h"

struct AIbase {
  //  int abs(int a) { if (a>=0) return a; else return -a;}


  virtual string name() {return "AIbase";}
  virtual int color1() {return 0x00112233;}
  virtual int color2() {return 0x00112234;}


  static vector<AIbase *> register_class(AIbase *p) {
    static vector<AIbase *> v;
    if (p) v.push_back(p);
    return v;
  }

  static vector<string> name_registrants() {
    vector<AIbase *> v = register_class(0);
    vector<string> vs(v.size());
    fori(v.size()) {
      vs[i] = v[i]->name();
    }
    return vs;
  }

  static bool check_registrants(bool print = false) {
    vector<AIbase *> v = register_class(0);

    set<string> snames;
    if (v.empty()) return false;

    if (print) cerr << "Known robot AIs:" << endl;
    foreach(i, v) {
      string s = (*i)->name();
      if (print) cerr << s << " ";
      if (snames.find(s)!=snames.end()) {
	cerr << endl;
	cerr << "Critical error: robot AI '"
	     << s << "' appears twice !!" << endl;
	return false;
      }
      snames.insert(s);
    }
    if (print) cerr << endl;
    return true;
  }

  static AIbase* instantiate_robot(string s) {
    vector<AIbase *> v = register_class(0);
    foreach(i, v) {
      if (s == (*i)->name()) return (*i)->clone();
    }
    return 0;
  }

  virtual AIbase* clone() = 0;

  virtual ~AIbase() {}

public:
  Mapa _M;
  virtual void fes_torn() = 0;
  
  bool existeix(int id) {return _M.existeix(id);}
  bool existeix(int i, int j) {return _M.existeix(i,j);}
  t_robot robot(int id) {return _M.robot(id);}
  t_robot robot(int i, int j) {return _M.robot(i,j);}
  int color(int i, int j) {return _M.color(i,j);}
  bool ordena(int id, int mov) {return _M.ordena(id, mov);}
  int num_caselles(int e) {return _M.num_caselles(e);}
  vector<int> T80PAG(int e) {return _M.T80PAG(e);}
  vector<int> pagesos(int e) {return _M.pagesos(e);}
  vector<int> T100CAV(int e) {return _M.T100CAV(e);}
  vector<int> cavallers(int e) {return _M.cavallers(e);}
  int random(int n) {return _M.random(n);}
  int torns_restants() {return _M.torns_restants();}
  int torn_actual() {return _M.torn_actual();}
};


#endif
