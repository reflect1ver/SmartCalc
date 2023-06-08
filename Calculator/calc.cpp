#include "calc.h"

#include "./ui_calc.h"

Calc::Calc(QWidget *parent) : QMainWindow(parent), ui(new Ui::Calc) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_ac, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->pushButton_unar, SIGNAL(clicked()), this, SLOT(unar()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(graph()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(eq()));
  connect(ui->solve_cred, SIGNAL(clicked()), this, SLOT(credit()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_left_scob, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_right_skob, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_umnozh, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

Calc::~Calc() { delete ui; }

void Calc::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();

  QString new_text = ui->textEdit->toPlainText() + button->text();

  ui->textEdit->setText(new_text);
}

void Calc::clear() { ui->textEdit->setText(""); }

void Calc::unar() {
  QString new_text = ui->textEdit->toPlainText() + "~";
  ui->textEdit->setText(new_text);
}

void Calc::eq() {
  double result;
  QString buf = ui->textEdit->toPlainText();
  QString string_result;
  result = calc(buf.toStdString().c_str());
  string_result = QString::number(result, 'g', 8);

  ui->textEdit->setText(string_result);
}

void Calc::graph() {
  ui->widget->clearGraphs();
  x.clear();
  y.clear();

  char Out[511];
  int len = 0;
  QString buf = ui->textEdit->toPlainText();
  QString buf2;

  len = forward(buf.toStdString().c_str(), Out);

  buf = ui->step->toPlainText();
  if (buf != "") {
    h = buf.toDouble();
  } else {
    h = 0.1;
  }

  buf = ui->X_left->toPlainText();
  if (buf != "") {
    xBegin = buf.toDouble() + h;
  } else {
    xBegin = -3;
  }

  buf = ui->X_right->toPlainText();
  if (buf != "") {
    xEnd = buf.toDouble() + h;
  } else {
    xEnd = 3 + h;
  }

  buf = ui->X_right_end->toPlainText();
  buf2 = ui->X_left_end->toPlainText();
  if (buf != "" && buf2 != "") {
    ui->widget->xAxis->setRange(buf.toDouble(), buf2.toDouble());
  } else {
    ui->widget->xAxis->setRange(-3, 4);
  }

  buf = ui->Y_down_end->toPlainText();
  buf2 = ui->Y_up_end->toPlainText();
  if (buf != "" && buf2 != "") {
    ui->widget->yAxis->setRange(buf.toDouble(), buf2.toDouble());
  } else {
    ui->widget->yAxis->setRange(-3, 4);
  }

  X = xBegin;
  N = (xEnd - xBegin) / h + 2;

  for (X = xBegin; X <= xEnd; X += h) {
    x.push_back(X);
    y.push_back(Y_calc(Out, len, X));
    X += h;
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void Calc::credit() {
  double result;
  double first = 0;
  double last = 0;

  QString sum = ui->sum->toPlainText();
  QString p = ui->percent->toPlainText();
  QString srok = ui->srok->toPlainText();

  QString string_result;

  if (ui->anuit->isChecked() == 1 && ui->diff->isChecked() == 1) {
    ui->plat->setText("Two flags");
    ui->pereplat->setText("Two flags");
    ui->viplat->setText("Two flags");

  } else if (ui->diff->isChecked() == 1 && p.toDouble() > 0 &&
             sum.toDouble() >= 0 && srok.toDouble() > 0) {
    result = diff(p.toDouble(), sum.toDouble(), srok.toDouble(), &first, &last);

    string_result =
        QString::number(first, 'g', 7) + " - " + QString::number(last, 'g', 7);
    ui->plat->setText(string_result);

    string_result = QString::number(result - sum.toDouble(), 'g', 7);
    ui->pereplat->setText(string_result);

    string_result = QString::number(result, 'g', 8);
    ui->viplat->setText(string_result);

  } else if (ui->anuit->isChecked() == 1 && p.toDouble() > 0 &&
             sum.toDouble() >= 0 && srok.toDouble() > 0) {
    result = annuitet(p.toDouble(), sum.toDouble(), srok.toInt());

    string_result = QString::number(result, 'g', 7);
    ui->plat->setText(string_result);

    string_result =
        QString::number(result * srok.toDouble() - sum.toDouble(), 'g', 7);
    ui->pereplat->setText(string_result);

    string_result = QString::number(result * srok.toDouble(), 'g', 8);
    ui->viplat->setText(string_result);

  } else if (ui->anuit->isChecked() == 0 && ui->diff->isChecked() == 0) {
    ui->plat->setText("Choose flag");
    ui->pereplat->setText("Choose flag");
    ui->viplat->setText("Choose flag");
  } else {
    ui->plat->setText("Error");
    ui->pereplat->setText("Error");
    ui->viplat->setText("Error");
  }
}
