#ifndef CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H_

#include <QMainWindow>
#include <QVector>

#include "../controller/controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void digits_numbers();
  void func_clicked();
  void equal();
  void delete_button();
  void clean_text();
  void graph_clicked();
  void exp_clicked();

 private:
  Ui::MainWindow *ui;
  s21::Controller c;
  QVector<double> x, y;
  int last_number{};
  int exp_flag{};
};
#endif  // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H_
