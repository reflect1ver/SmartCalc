#ifndef CALC_H
#define CALC_H

#include <QMainWindow>
#include <QVector>

extern "C" {
#include "../s21_calculator.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class Calc;
}
QT_END_NAMESPACE

class Calc : public QMainWindow {
  Q_OBJECT

 public:
  Calc(QWidget *parent = nullptr);
  ~Calc();

 private:
  Ui::Calc *ui;
  double xBegin, xEnd, h, X;
  int N;

  QVector<double> x, y;

 private slots:
  void digits_numbers();
  void clear();
  void unar();
  void eq();
  void graph();
  void credit();
};
#endif  // CALC_H
