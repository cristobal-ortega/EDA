#include "robots.h"

istream &operator>>(istream &in, Mapa &m)
{
  m.id_pag.clear();
  m.id_cav.clear();

  m.n_territoris=m.n_cav=m.n_pag=vector<int>(5, 0);

  int kk; //kk es el torn (1-4), no s'utilitza en mapa.
  in >> m.D >> kk >> m.trns_rstnts >> m.trn_actual;

  //llavor per al random, que anem creant a partir de les dades que rebem
  int seed = m.trns_rstnts;

  m.M=vector<vector<Mapa::casella> >(m.D, vector<Mapa::casella>(m.D));
 
  for (int i=0;i<m.D;i++)
    {
      string st;
      in >> st;
      for (int j=0;j<m.D;j++)
	{
	  int e = st[j]-'0';
	  seed+= e;
	  m.M[i][j].id=(e==-1)?-1:0;
	  m.M[i][j].equip=e;
	  if (e>=0) m.n_territoris[e]++;
	}
    }

  m.Robots.clear();

  int numrobots;
  in >> numrobots;
  m.F=vector<t_robot>(numrobots);
  for (int i=0;i<numrobots;i++)
    {
      t_robot f;
      in >> f.id >> f.i >> f.j >> f.equip >> f.model >> f.vida;
      m.F[i]=f;
      m.Robots[f.id]=i;
      m.M[f.i][f.j].id=f.id;
      if (f.model==CAV)
	m.n_cav[f.equip]++;
      else
	m.n_pag[f.equip]++;

      seed+=f.id + f.i + f.j;
    }
  m.Ordres.clear();
  m.ordreOrdres.clear();
  m.A = atzar(seed);
  return in;
}


void Mapa::escriu_ordres(ostream &os) {
  int numpag = T80PAG(1).size();
  int numcav = T100CAV(1).size();
  os << numpag+numcav << " ";
  foreach(i, ordreOrdres) {
    PII o = *Ordres.find(*i);
    os << " " << o.first << " " << o.second;
  }
  
  vector<int> pags = T80PAG(1);
  vector<int> cavs = T100CAV(1);
  foreach(i, pags) {
    if (Ordres.find(*i)==Ordres.end())
      os << " " << *i  << " 9";
  }
  foreach(i, cavs) {
    if (Ordres.find(*i)==Ordres.end())
      os << " " << *i  << " 9";
  }
}
