#include "DomWin.h"
#include <QLayout>
#include <cassert>

/*
QLabel *createLabel(string name, QColor c) {
  QLabel *l = new QLabel(name.c_str());
  QPalette qp = l->palette();
  qp.setColor(QPalette::WindowText, c);
  l->setPalette(qp);
  l->setAlignment(Qt::AlignCenter);
  return l;
}
*/


DomWin::DomWin(vector<string> &names, int numtorns, int fontsize,
	       QWidget *parent):
  QWidget(parent) {
 
  vl.resize(4);
  for(int i=0;i<4;++i) {
    vl[i] = new QLabel(names[i].c_str());
    vl[i]->setAlignment(Qt::AlignCenter);

    QFont qf = vl[i]->font();
    qf.setPointSize(fontsize);
    qf.setStyleHint(QFont::Times);
    vl[i]->setFont(qf);
  }
  

  QVBoxLayout *vLayoutL = new QVBoxLayout;
  vLayoutL->addStretch(1);
  vLayoutL->addWidget(vl[0]);
  vLayoutL->addStretch(1);
  vLayoutL->addWidget(vl[3]);  
  vLayoutL->addStretch(1);

  QVBoxLayout *vLayoutR = new QVBoxLayout;
  vLayoutR->addStretch(1);
  vLayoutR->addWidget(vl[1]);  
  vLayoutR->addStretch(1);
  vLayoutR->addWidget(vl[2]);  
  vLayoutR->addStretch(1);

  QVBoxLayout *vLayoutC = new QVBoxLayout;
  dv = new DomView(names, numtorns);

  connect(dv,
	  SIGNAL(signalUpdateTeamPoints(int, string, int, QColor)),
	  this,
	  SLOT(updateTeamPoints(int, string, int, QColor))
	  );

  //  vLayoutC->addWidget(ql);
  vLayoutC->addWidget(dv); 
  tw = new TimeWidget(dv);
  vLayoutC->addWidget(tw);

  
  QHBoxLayout *mainLayout = new QHBoxLayout;
  
  mainLayout->addLayout(vLayoutL);
  mainLayout->addLayout(vLayoutC);
  mainLayout->addLayout(vLayoutR);

  setLayout(mainLayout);
  setWindowTitle(tr("Requiem"));

}


void DomWin::updateTeamPoints(int team, string name, int points, QColor c) {
  ostringstream oss;
  oss << name << "\n" << points;
  vl[team]->setText(oss.str().c_str());

  QPalette qp = vl[team]->palette();
  qp.setColor(QPalette::WindowText, c);
  vl[team]->setPalette(qp);
}
