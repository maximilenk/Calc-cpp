#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_br_fr, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_br_b, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(delete_button()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(equal()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(graph_clicked()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(exp_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  clean_text();
  QPushButton *button = (QPushButton *)sender();
  if (button->text()[0] >= '0' && button->text()[0] <= '9') {
    last_number = 1;
  } else {
    last_number = 0;
  }
  QString label = ui->showing->text() + button->text();
  ui->showing->setText(label);
}

void MainWindow::equal() {
  exp_flag = 0;
  last_number = 0;
  char *str = new char[ui->showing->text().length()];
  QByteArray temp = ui->showing->text().toLatin1();
  strlcpy(str, temp, ui->showing->text().length() + 1);
  double result, x = 0;
  std::string str1(str);
  if (ui->showing->text().contains('x')) x = ui->xValue->value();
  if (c.call_model(str1, x, result)) {
    ui->showing->setText("ERROR");
  } else {
    QString strResult;
    sprintf(str, "%.7f", result);
    strResult = str;
    ui->showing->setText(strResult);
  }
  delete[] str;
  str = nullptr;
}

void MainWindow::delete_button() {
  last_number = 0;
  exp_flag = 0;
  ui->showing->setText("");
}

void MainWindow::func_clicked() {
  last_number = 0;
  clean_text();
  QPushButton *button = (QPushButton *)sender();
  QString label = ui->showing->text() + button->text() + '(';
  ui->showing->setText(label);
}

void MainWindow::clean_text() {
  if (ui->showing->text() == "ERROR" || ui->showing->text() == "inf" ||
      ui->showing->text() == "nan")
    ui->showing->setText("");
}

void MainWindow::graph_clicked() {
  ui->widget->clearGraphs();
  char *str = new char[ui->showing->text().length()];
  QByteArray temp = ui->showing->text().toLatin1();
  strlcpy(str, temp, ui->showing->text().length() + 1);
  double result = 0;
  std::string str1(str);
  if (!c.call_model(str1, 0, result) &&
      ui->end_x->value() > ui->start_x->value() &&
      ui->end_y->value() > ui->start_y->value()) {
    ui->widget->xAxis->setRange(ui->start_x->value(), ui->end_x->value());
    ui->widget->yAxis->setRange(ui->start_y->value(), ui->end_y->value());
    for (double i = ui->start_x->value(); i <= ui->end_x->value();
         i += (ui->end_x->value() - ui->start_x->value()) * 0.0005) {
      c.call_model(str1, i, result);
      x.push_back(i);
      y.push_back(result);
      str1 = str;
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
  } else {
    QMessageBox::information(this, "Error", "incorrect input");
  }
  delete[] str;
  str = nullptr;
}

void MainWindow::exp_clicked() {
  if (!exp_flag && last_number) {
    clean_text();
    QPushButton *button = (QPushButton *)sender();
    QString label = ui->showing->text() + button->text();
    ui->showing->setText(label);
    exp_flag = 1;
    last_number = 0;
  }
}
