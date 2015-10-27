#ifndef DOMVIEW_H
#define DOMVIEW_H

#include <QtGui>
#include <vector>
#include "taulell.h"


using namespace std;

class DomView: public QWidget {
  Q_OBJECT

    public:

static const int default_speed_ms = 150;

  DomView (vector<string> &_jug, int numtorns, QWidget *parent = 0);
  
  /** Aquesta funcio pot ser cridada asincronament, des d'un altre thread */
  void addTaulell(Taulell &t);  

  vector<string> names;
  
  void setSpeed(int speedms);
  void setStop();

 protected:
  //avoid redrawing stuff
  int cachew, cacheh;
  vector<QImage *> cache_images; 
  QImage *getCacheImage(int w, int h, int colorland,
			int what=0, int colorwhat=0);
 
  void initColors();

  static const int minsize = 400;  //pixels 
  static const int minredrawingtime = 20;  //ms
  vector<Taulell> T;
  int numTs;

  vector<QColor> vC;
  vector<QBrush> vB;
  int turn;

  enum Status {PLAY, STOP};
  Status status;

  enum WaitingFor {ANIMATION, DELAY, NOTHING};
  WaitingFor waitingFor;

  int timeAnimation;
  int timeDelay;

  int basetime;

  QTime clock;
  QTimer animationTimer;
  QPixmap logo;

  void saveImage(const string &name, int width, int height, int provturn);

  void dibuixa(QPainter &painter);
  void paintEvent(QPaintEvent *event);

  void next_frame();
  void prev_frame();

 public:
  void saveImages(const string &basefilename);
 Q_SIGNALS:
  void signalTimeChanged(int t);
  void signalSpeedChanged(int t);
  void signalMaxTimeChanged(int t);
  void signalUpdateTeamPoints(int team, string name, int points, QColor c);
  void signalUpdateTurn(int t);

public Q_SLOTS:
  void stop();
  void play();
  void stepback();
  void stepforw();
  void setTimer(int t);
  void setSpeedFromSlider(int s);

protected Q_SLOTS:
  void animate();
};

#endif
