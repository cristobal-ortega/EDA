#include "DomView.h"
#include <cassert>
#include <iomanip>

#define MINTIME 50

QImage *DomView::getCacheImage(int w, int h, int colorland,
			       int what, int colorwhat) {
//colorland : 0 (none), 1-4
//what: 0 (empty), 1 (wall), 2 (T80PAG), 3-6 (T100CAV, feble--fort)
//colorwhat : 1-4
  //total: 5*(1+1+4+4*4)=5*22=110

  if (cache_images.empty()) cache_images.resize(110, 0);
  if (cachew!=w or cacheh!=h) {
    for(int i=0; i<int(cache_images.size()); ++i) {
      if (cache_images[i]) {
	delete cache_images[i];
	cache_images[i]=0;
      }
    }
    cachew = w;
    cacheh = h;
  }

  int i = colorland*22;
  if (what==1) i=1;  //colorland es invalid quan what==1
  else if (what==2) i+=1+colorwhat;
  else if (what>2) i+=1+4*(what-2)+colorwhat;

  if (cache_images[i]) return cache_images[i];
  else {

    cache_images[i] = new QImage(w, h, QImage::Format_RGB32);
    
    QPainter painter(cache_images[i]);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(vB[0]);
    painter.drawRect(QRect(0, 0, w, h));
    //hem de dibuixar la imatge: primer, el terreny (si no es mur)
    if (colorland>=0) {
      painter.setBrush(vB[colorland]);
      painter.drawRect(QRectF(0.05*w, 0.05*h, 0.9*w, 0.9*h));
    }

    //a continuacio, l'objecte que hi ha a sobre
    if (what>0) {
      if (what==1) { //dibuixar mur
	painter.setPen(vC[5]);
	QPen pen = painter.pen();
	pen.setWidth(2);
	painter.setPen(pen);
	painter.setBrush(vB[5]);  //5: color de mur
	painter.drawRect(QRectF(0, 0, w, h));
      }
      else if (what>=2) { //dibuixar T80PAG o T100CAV
	assert(colorwhat!=0);
	painter.setPen(vC[colorwhat]);
	
	if (what==2) {
	  painter.setBrush(Qt::NoBrush);
	  painter.drawEllipse(QRectF(0.3*w, 0.3*h, 0.4*w, 0.4*h));
	}
	else if (what>=3) {
	  QPen pen = painter.pen();
	  pen.setWidth(0.5+0.5*(what-3));
	  painter.setPen(pen);
	  painter.setBrush(Qt::NoBrush);
	  //	  painter.setBrush(vB[colorwhat]);
	  painter.drawEllipse(QRectF(0.1*w, 0.1*h, 0.8*w, 0.8*h));
	}      
      } 
    }
    return cache_images[i];
  }
}



void DomView::setSpeed(int speedms) {
  timeAnimation = min(100, speedms/2);
  timeDelay = max(speedms/2, speedms-100);
}

void DomView::setSpeedFromSlider(int s) {
  // 5 == default_speed_ms
  int x = default_speed_ms;
  while (s > 5) {
    x *= 2/3.0;
    --s;
  }
  while (s < 5) {
    x *= 3/2.0;
    ++s;
  }
  setSpeed(x);
}



void DomView::setStop() {
  status = STOP;
}

DomView::DomView(vector<string> &_jug, int numtorns, QWidget *parent):
  QWidget(parent), names(_jug), numTs(0), turn(-1),
  status(PLAY), waitingFor(NOTHING),
  timeAnimation(100), timeDelay(200) {

  logo.load("ada-royale.png");
  T.resize(numtorns+1);
  
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  
  //  setWindowTitle(tr("Dominator 2"));
  //  resize(minsize, minsize);

  setMinimumSize(minsize,minsize);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  clock.start();
  animationTimer.setSingleShot(false);
  connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));

  basetime = clock.elapsed();
  animationTimer.start(MINTIME);
  initColors();
}

void DomView::initColors() {
  vC.resize(6);
  vC[0] = QColor("grey");
  vC[1] = QColor("orangered");
  vC[2] = QColor("blue");
  vC[3] = QColor("limegreen");
  vC[4] = QColor("magenta");
  vC[5] = QColor("black");

  vB.resize(6);
  fori(5) {
    vB[i] = QBrush(vC[i].light(170));
  }
  vB[5] = QBrush("grey");
}

void DomView::saveImage(const string &name, int width,
			int height, int provturn) {

  int oldturn = turn;
  turn = provturn;
  //  QPixmap qp(width, height);
  QImage qi(width, height, QImage::Format_RGB32);
  qi.fill( qRgb(128, 255, 128) );

  QPainter p(&qi);
  dibuixa(p);

  qi.save(QString(name.c_str())); 
  turn = oldturn;
}

void DomView::dibuixa(QPainter &painter) {
  int width = painter.device()->width();
  int height = painter.device()->height();

  assert(width==500 and height==500);

  //  int side = qMin(width, height);
  int D = 50;
  if (not T.empty()) D = T[0].DIM;
  //
  //    image = new 
  //    p2 = new QPainter(*image);
  //  }

  //  painter.translate((width-side)/2, (height-side)/2);
  //  painter.scale(side / double(100*D), side / double(100*D));
  
  assert(turn>=0);
  assert(numTs>turn);
  
  fori(D) forj(D) {
    casella &c = T[turn].Map[i][j]; 
    int owner = c.terreny;
    assert(owner>=-1 and owner<=4);

    int what = 0;
    if (owner==-1) what = 1;
    else if (c.pers == PAG) what = 2;
    else if (c.pers == CAV) {
      what = 3+int((c.forca*3.0/400.0)+0.49);
      if (what<3 or what>6) {
	cerr << what << endl;
	cerr << c.forca << endl;
      }
      assert(what>=3 and what<=6);
    }
    painter.drawImage(j*10, i*10, *getCacheImage(10, 10, c.terreny,
						 what, c.bando));
    /*    
    painter.setPen(Qt::NoPen);
    painter.setBrush(vB[owner]);
    painter.drawRect(j*100+1, i*100+1, 98, 98);
    
    //tenim un robot per pintar
    if (c.bando != 0) {
      owner = c.bando;
      assert(owner>=1 and owner<=4);
      
      painter.setPen(vC[owner]);
      if (c.pers == PAG) {
	painter.setBrush(Qt::NoBrush);
	painter.drawEllipse(j*100+30, i*100+30, 40, 40);
      }
      else if (c.pers == CAV) {
      	QPen pen = painter.pen();
	pen.setWidth(1+c.forca/20);
	painter.setPen(pen);
	painter.setBrush(vB[owner]);
	painter.drawEllipse(j*100+10, i*100+10, 80, 80);
	pen.setWidth(0);
	painter.setPen(pen);
      }
    }
    */

  }
}


void DomView::saveImages(const string &basefilename) {
  for(int i=0; i<numTs; ++i) {
    ostringstream oss;
    oss << basefilename << "." << setfill('0') << setw(3) << i << ".ppm";
    cerr << "Saving image '" << oss.str() << "'..." << endl;
    saveImage(oss.str(), 500, 500, i);
  }
}

void DomView::paintEvent(QPaintEvent *) {

  if (turn==-1) {
    QPainter painter(this);
    painter.drawPixmap(QRect(0, 0, width(), height()),
		      logo);
    return;
  }

  /*  int side = qMin(width(), height());
  int D = 50;
  if (not T.empty()) D = T[0].DIM;*/

  for(int i=0;i<4;++i) {
    signalUpdateTeamPoints(i, names[i],
			   T[turn].puntuacio(i+1), vC[i+1]);
  }

  //always draw on a QImage(500, 500)
  QImage qim(500, 500, QImage::Format_RGB32);
  QPainter p2(&qim);
  dibuixa(p2);

  QPainter painter(this);
  painter.drawImage(QRect(0, 0, width(), height()),
		    qim, QRect(0, 0, 500, 500));
}
  
  
void DomView::addTaulell(Taulell &t) {
  if (numTs == int(T.size())) return;
  T[numTs++] = t;
  signalMaxTimeChanged(numTs);
}

/*
  T.push_back(t);
  if (turn==-1) {
    turn = 0;
	  update();
	}

  if (status == PLAY and waitingFor == NOTHING
      and int(T.size()) == turn-2) {

    next_frame();  //start again the animation    
  }
  }*/


void DomView::next_frame() {
  //do we have a next frame?
  if (numTs-1 == turn) return;

  ++turn; signalTimeChanged(turn);
  if (status == PLAY) waitingFor = ANIMATION;
  else if (status == STOP) waitingFor = NOTHING;

  basetime = clock.elapsed();
  animate();
  //  prepareRedrawing(minredrawingtime);
}

void DomView::prev_frame() {
  //do we have a prev frame?
  if (turn <= 0) return;

  --turn; signalTimeChanged(turn);
  if (status == PLAY) waitingFor = DELAY;
  else if (status == STOP) waitingFor = NOTHING;

  basetime = clock.elapsed();
  animate();
}


void DomView::animate() {

  int diff = clock.elapsed() - basetime;
  
  //  cout << diff << ", " << waitingFor << ", " << status << ", " << numTs << endl;

  if (waitingFor == ANIMATION and diff > timeAnimation) {
    waitingFor = DELAY;
    basetime = clock.elapsed() - (diff-timeAnimation);

    animationTimer.start(min(MINTIME, max(1, timeDelay - (diff-timeAnimation))));
  }
  else if (waitingFor == DELAY and diff > timeDelay) {
    if (status == PLAY) {
      //haig d'esperar
      if (turn == numTs-1) {
	waitingFor = NOTHING;
	animationTimer.start(MINTIME);
	update();
	return;
      }

      ++turn; signalTimeChanged(turn);
      waitingFor = ANIMATION;
      basetime = clock.elapsed();

      animationTimer.start(minredrawingtime);
      return;  //no repaint if delaying
    }
    else if (status == STOP) {
      waitingFor = NOTHING;
      animationTimer.start(MINTIME);
      update();
      return;
    }
  }
  else if (waitingFor == NOTHING) {
    if (status == PLAY and turn<numTs-1) {
      ++turn; signalTimeChanged(turn);
      waitingFor = ANIMATION;
      basetime = clock.elapsed();

      animationTimer.start(minredrawingtime);
    }
    else return; //no repaint if doing nothing
  }

  repaint();
}


void DomView::stop() {
  status = STOP;
}

void DomView::play() {
  status = PLAY;
}

//void DomView::start() {
//  turn = 0;
//  status = STOP;
//  update();
//}

void DomView::stepback() {
  status = STOP;
  prev_frame();
  update();
}

void DomView::stepforw() {
  status = STOP;
  next_frame();
  update();
}

void DomView::setTimer(int t) {
  status = STOP;
  if (t>=0 and t<numTs) {
    turn = t;
    signalTimeChanged(turn);
  }
  update();
}
