#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include <QWidget>
#include <QLayout>

//class WorldController;
class QSlider;
//class QLineEdit;

class TimeWidget: public QWidget {
  Q_OBJECT

  public:
  TimeWidget(QWidget *domview, QWidget *parent = NULL);

 private:
  QSlider *slider;
  QSlider *speeder;
  //  QLineEdit *timeEdit;

  private Q_SLOTS:
  void maxTimeChanged(int t);
  void timeChanged(int t);
  void reset();
};


#endif
