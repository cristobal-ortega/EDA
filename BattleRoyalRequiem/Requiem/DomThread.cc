#include "DomThread.h"
#include "DomView.h"
#include "aibase.h"
#include <cassert>
#include <algorithm>
#include <iomanip>



DomThread::~DomThread() {}


DomThread::DomThread(vector<AIbase*> &ais,
		     int numtorns, int seed, int dim, int T80ini, int T100ini,
		     DomView *dv, const string &output_filename,
		     QObject *parent): QThread(parent) {
  AIs = ais;
  T = Taulell(numtorns, seed, dim, T80ini, T100ini);

  domview = dv;
  if (domview) domview->addTaulell(T);

  write_output = output_filename!="";

  if (write_output) {
    //    ofs.open(output_filename.c_str());
    ofs2.open(output_filename.c_str());
    //    if (not ofs) {
    //      cerr << "Could not open file '" << output_filename
    //	   << "' for writting." << endl;
    //    }
    if (not ofs2) {
      cerr << "Could not open file '" << (output_filename+".cs")
	   << "' for writting." << endl;
    }
    else {
      //      ofs << "_REQUIEM 1.0" << endl;
      ofs2 << "_REQUIEM_CS " << REQUIEM_VERSION << endl;
      fori(4) {
	string name = ais[i]->name();
	assert(name.find_first_of(' ')==string::npos); //no valen espais!
	//	ofs << name << endl;
	ofs2 << name << endl;
      }
      //      ofs << seed << endl;
      ofs2 << seed << endl;

      //      write(ofs, T) << endl;  //primer taulell
      //      ofs.flush();
      ofs2.flush();
    }
  }
}

void DomThread::run() {
  for (int torn = 0; torn<T.NUMTORNS; ++torn) {
    
    cerr << "Torn " << (torn+1) << "..." << endl;
    
    vector<vector<PII> > vordres(4);
    for (int i = 0; i<4; ++i) {
      stringstream ss1;
      T.print_as_player(i+1);
      ss1 << T;
      

      ss1 >> AIs[i]->_M;
      
      cerr << " " << (i+1) << "..." << endl;

      stringstream ssnom;
      ssnom << AIs[i]->name() << "(" << i+1 << ")";
      AIs[i]->_M.whoami = ssnom.str()
;
      AIs[i]->fes_torn();
      
      stringstream ss2;
      AIs[i]->_M.escriu_ordres(ss2);
      llegeix_ordres(ss2, vordres[i]);

      //compte: llegeix_ordres ha aplicat un sort a vordres[i].
    }

    T.juganou(vordres);

    if (domview) domview->addTaulell(T);

    if (write_output) {
      //o be guardem els nous taulells a saco...
      //      write(ofs, T) << endl;
      //      ofs.flush();

      //o be guardem les ordres donades...
      for (int i = 0; i<4; ++i) {
	for (int j = 0; j<(int)vordres[i].size(); ++j) {
	  int v = vordres[i][j].second;
	  assert(v>=0 and v<=9); //single char
	  ofs2 << char(vordres[i][j].second+'0');
	}
      }
      ofs2 << endl;
      ofs2.flush();
    }

  }
  cerr << endl << "The match is finished." << endl;
  
  cerr << endl << "Result:" << endl;
  for(int i=0;i<4;++i) {
    cout << T.puntuacio(i+1) << endl;
  }
}
  //
  //  T.print_as_player(1);
  //  cerr << T;
