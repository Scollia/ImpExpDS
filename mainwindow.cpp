#include <QSettings>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <Winreg.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  programm_options  = new CProgrammOptions(this);
  programm_options->Load();
  main_data         = new CMainData(this);

  PrepareUI();
/*
  strRegKeyDS   = "HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Crypto Pro\Settings\Users\" + Lbl_UserSID->text() + "\Keys"
*/
//  QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Crypto Pro\\Settings\\Users\\" + Lbl_UserSID->text() + "\\Keys", QSettings::NativeFormat );
//  for (const auto& g : settings.childGroups()) {
//    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
//    ui->tableWidget->setItem(ui->tableWidget->rowCount(),2, new QTableWidgetItem(g));
//    ui->tableWidget->cellWidget(ui->tableWidget->rowCount(), 2)->set
//  }
//  RegOpenKeyExW();
}

MainWindow::~MainWindow()
{
  programm_options->Save();
  delete ui;
}

void MainWindow::PrepareUI() {
  Lbl_UserName    = new QLabel(this);
  Lbl_UserSID     = new QLabel(this);

  ui->statusbar->addPermanentWidget(Lbl_UserName);
  ui->statusbar->addPermanentWidget(Lbl_UserSID);

  Lbl_UserName->setText(programm_options->UserDomain() + "\\" + programm_options->UserName());
  Lbl_UserSID->setText(programm_options->UserSID());

// Скрываем колонку под номером 4
  ui->tblWdgt_UserContainers->hideColumn(3);
  ui->tblWdgt_ArchiveContainers->hideColumn(3);


  // Указываем число колонок
//  ui->tableWidget->setColumnCount(5);
  // Включаем сетку
//  ui->tableWidget->setShowGrid(true);
  // Разрешаем выделение только одного элемента
//  ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  // Разрешаем выделение построчно
//  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  // Устанавливаем заголовки колонок
//  ui->tableWidget->setHorizontalHeaderLabels(headers);
  // Растягиваем последнюю колонку на всё доступное пространство
//  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//  ui->tableWidget->resizeColumnsToContents();

// Соединяем сигнала кнопок со слотами
  connect(ui->pshBttn_ReadUserContainers,SIGNAL(clicked()),this,SLOT(ReadUserContainers()));
  connect(ui->pshBttn_ExportUserContainers,SIGNAL(clicked()),this,SLOT(ExportUserContainers()));
  connect(ui->pshBttn_ReadArchiveContainers,SIGNAL(clicked()),this,SLOT(ReadArchiveContainers()));
  connect(ui->pshBttn_ImportArchiveContainers,SIGNAL(clicked()),this,SLOT(ImportArchiveContainers()));
}

void MainWindow::ReadUserContainers() {
  // Очищаем таблицу
  ui->tblWdgt_UserContainers->setRowCount(0);
  ui->tblWdgt_UserContainers->clearContents();

  QSettings*   tmpSettings   = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Crypto Pro\\Settings\\Users\\" + programm_options->UserSID() + "\\Keys", QSettings::NativeFormat);
  for (const auto& g : tmpSettings->childGroups()) {
    auto row = ui->tblWdgt_UserContainers->rowCount();
    ui->tblWdgt_UserContainers->insertRow(row);
    auto tmpContainerName = new QTableWidgetItem(g);

    // Снимаем флаг "Редактирование"
    tmpContainerName->setFlags(tmpContainerName->flags() & ~Qt::ItemIsEditable);
    ui->tblWdgt_UserContainers->setItem(row, 2, tmpContainerName);
  };
};

void MainWindow::ExportUserContainers() {
//  ui->tblWdgt_UserContainers->setRowCount(0);
//  ui->tblWdgt_UserContainers->clearContents();
//  QMessageBox::information(this, "Сообщение", "Значение = " + QString::number(ui->tblWdgt_UserContainers->selectionModel()->selectedRows().size()));
  for (const auto& g : ui->tblWdgt_UserContainers->selectionModel()->selectedRows()) {
    ui->tblWdgt_UserContainers->item(g.row(), 2)->text();
    HKEY phkResult;
    RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Wow6432Node\\Crypto Pro\\Settings\\Users\\" + programm_options->UserSID() + "\\Keys", phkResult);
    RegSaveKeyEx(phkResult, "d:\dever", NULL);
  };
};

void MainWindow::ReadArchiveContainers() {
  ui->tblWdgt_ArchiveContainers->insertRow(0);
//  ui->tblWdgt_ArchiveContainers->resizeColumnsToContents();
};

void MainWindow::ImportArchiveContainers() {
  ui->tblWdgt_ArchiveContainers->removeRow(0);
//  ui->tblWdgt_ArchiveContainers->resizeColumnsToContents();
};

