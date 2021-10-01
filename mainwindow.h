#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include\cprogrammoptions.h"
#include "include\cmaindata.h"

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  CProgrammOptions* programm_options;
  CMainData*        main_data;
  QLabel* Lbl_UserName;
  QLabel* Lbl_UserSID;

  void PrepareUI();

private slots:
  void ReadUserContainers();
  void ExportUserContainers();
  void ReadArchiveContainers();
  void ImportArchiveContainers();
signals:

};
#endif // MAINWINDOW_H
