#include <qthread.h>
#include "taulell.h"
#include <fstream>
#include <vector>

class AIbase;
class DomView;

bool llegeix_ordres(istream &iss, vector<PII> &v);

class DomThread: public QThread {

  Q_OBJECT

 public:
  DomThread(vector<AIbase*> &ais,
	    int numtorns, int seed, int dim, int T80ini, int T100ini,
	    DomView *dv, const string &output_filename,
	    QObject *parent = 0);
  ~DomThread();

  vector<AIbase*> AIs;
  Taulell T;
  DomView *domview;

  bool write_output;
  ofstream ofs;
  ofstream ofs2; 

  void run_in_own_thread() {run();}

 protected:
  void run();
};
  
