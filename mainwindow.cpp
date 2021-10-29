#include <QDir>
#include <QSettings>
#include <QMessageBox>
#include <QTreeWidgetItem>

#include <Windows.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef _WIN64
//  #define CRYPTO_PRO_USERS_PATH (L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Crypto Pro\\Settings\\Users")
  #define CRYPTO_PRO_USERS_PATH (L"SOFTWARE\\Wow6432Node\\Crypto Pro\\Settings\\Users")
#else
//  #define CRYPTO_PRO_USERS_PATH ("HKEY_LOCAL_MACHINE\\SOFTWARE\\Crypto Pro\\Settings\\Users")
  #define CRYPTO_PRO_USERS_PATH ("SOFTWARE\\Crypto Pro\\Settings\\Users")
#endif

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  programm_options  = new CProgrammOptions(this);
  programm_options->Load();
  main_data         = new CMainData(this);

  PrepareUI();
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

  QSettings* tmpSettings   = new QSettings("HKEY_LOCAL_MACHINE\\" + QString::fromWCharArray(CRYPTO_PRO_USERS_PATH) + "\\" + programm_options->UserSID() + "\\Keys", QSettings::NativeFormat);
  for (const auto& g : tmpSettings->childGroups()) {
    auto row = ui->tblWdgt_UserContainers->rowCount();
    ui->tblWdgt_UserContainers->insertRow(row);
    auto tmpContainerName = new QTableWidgetItem(g);

    // Снимаем флаг "Редактирование"
    tmpContainerName->setFlags(tmpContainerName->flags() & ~Qt::ItemIsEditable);
    ui->tblWdgt_UserContainers->setItem(row, 2, tmpContainerName);
  };
  delete tmpSettings;
};

//  QMessageBox::information(this, "Сообщение", "Значение = " + QString::number(ui->tblWdgt_UserContainers->selectionModel()->selectedRows().size()));

void MainWindow::ExportUserContainers() {
  for (const auto& g : ui->tblWdgt_UserContainers->selectionModel()->selectedRows()) {
    CContainerData *tmpcontainer = new CContainerData(this);

    tmpcontainer->SetContainerName(ui->tblWdgt_UserContainers->item(g.row(), 2)->text());
    tmpcontainer->ExportContainer(QString::fromWCharArray(CRYPTO_PRO_USERS_PATH) + "\\" + programm_options->UserSID() + "\\Keys");
//    tmpcontainer->SaveConteinerToArchive(programm_options->PathToArchive());
    tmpcontainer->SetContainerName(ui->tblWdgt_UserContainers->item(g.row(), 2)->text() + "_2");
    tmpcontainer->ImportContainer(QString::fromWCharArray(CRYPTO_PRO_USERS_PATH) + "\\" + programm_options->UserSID() + "\\Keys");

    delete tmpcontainer;
  };
};

void MainWindow::ReadArchiveContainers() {
  // Очищаем таблицу
  ui->tblWdgt_ArchiveContainers->setRowCount(0);
  ui->tblWdgt_ArchiveContainers->clearContents();

  QDir archive(programm_options->PathToArchive());

  if (archive.exists()){
    archive.setFilter(QDir::Files);

    QFileInfoList containerfileslist = archive.entryInfoList();

    foreach (QFileInfo containerfile, containerfileslist) {
      CContainerData *tmpcontainer = new CContainerData(this);
      tmpcontainer->SetContainerName(containerfile.fileName());
//      tmpcontainer->LoadContainerFromArchive(programm_options->PathToArchive());

      auto row = ui->tblWdgt_ArchiveContainers->rowCount();
      ui->tblWdgt_ArchiveContainers->insertRow(row);
      auto tmpContainerName = new QTableWidgetItem(tmpcontainer->ContainerName());

      // Снимаем флаг "Редактирование"
      tmpContainerName->setFlags(tmpContainerName->flags() & ~Qt::ItemIsEditable);
      ui->tblWdgt_ArchiveContainers->setItem(row, 2, tmpContainerName);
    }
  } else {
    QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к архиву контейнеров:\n" + programm_options->PathToArchive());
  };
};

void MainWindow::ImportArchiveContainers() {
  QDir archive(programm_options->PathToArchive());

  if (archive.exists()) {
    for (const auto& g : ui->tblWdgt_ArchiveContainers->selectionModel()->selectedRows()) {
      CContainerData *tmpcontainer = new CContainerData(this);

      tmpcontainer->SetContainerName(ui->tblWdgt_ArchiveContainers->item(g.row(), 2)->text());
//      tmpcontainer->LoadContainerFromArchive(programm_options->PathToArchive());
      tmpcontainer->ImportContainer(QString::fromWCharArray(CRYPTO_PRO_USERS_PATH) + "\\" + programm_options->UserSID() + "\\Keys");

      delete tmpcontainer;
    };
  } else {
    QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к архиву контейнеров:\n" + programm_options->PathToArchive());
  };
};

