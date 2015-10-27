#ifndef DOMWIN_H
#define DOMWIN_H

#include <QtGui>
#include <vector>
#include "DomView.h"
#include "TimeWidget.h"

using namespace std;

class DomWin: public QWidget {
  Q_OBJECT

    public:

  DomView *dv;
  TimeWidget *tw;
  vector<QLabel *> vl;
  
  DomWin(vector<string> &names, int numtorns,
	 int fontsize = 12, QWidget *parent = 0);

  public Q_SLOTS:
  void updateTeamPoints(int team, string name, int points, QColor c);
};

#endif
