#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Windows.h>
#include <winbase.h>
#include <Sddl.h>
#include <LM.h>
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Lbl_UserName = new QLabel(this);
    Lbl_UserSID  = new QLabel(this);
    ui->statusbar->addPermanentWidget(Lbl_UserName);
    ui->statusbar->addPermanentWidget(Lbl_UserSID);

    Lbl_UserName->setText(getenv("UserName"));

    char sid_buffer[1024];
    LPCTSTR wszAccName = Lbl_UserName->text().toStdWString().c_str();
    PSID sid = (SID *)sid_buffer;
    DWORD cbSid = 1024;
    LPTSTR wszDomainName = (LPTSTR)GlobalAlloc(GPTR, sizeof(TCHAR) * 1024);
    DWORD cchDomainName = 1024;
    SID_NAME_USE eSidType;
    LPTSTR sidstring;

    if (LookupAccountName(NULL, wszAccName, sid, &cbSid, wszDomainName, &cchDomainName, &eSidType)) {
      if (ConvertSidToStringSid(sid, &sidstring)) {
#ifdef UNICODE
        Lbl_UserSID->setText(QString::fromUtf16((const ushort*) sidstring));
#else
        Lbl_UserSID->setText(QString::fromLocal8Bit((const char*) sidstring));
#endif
      }
    };
/*
    strRegKeyDS    = "HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Crypto Pro\Settings\Users\" + Lbl_UserSID->text() + "\Keys"
*/
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Crypto Pro\\Settings\\Users\\" + Lbl_UserSID->text() + "\\Keys", QSettings::NativeFormat );
    for (const auto& g : settings.childGroups()) {
      ui->tableWidget->insertRow(ui->tableWidget->rowCount());
      ui->tableWidget->setItem(ui->tableWidget->rowCount(),2, new QTableWidgetItem(g));
//      ui->tableWidget->cellWidget(ui->tableWidget->rowCount(), 2)->set
    }
//    RegOpenKeyExW();


/*
    if (!LookupAccountName(NULL, wszAccName, sid_buffer, &cbSid, wszDomainName, &cchDomainName, &eSidType)) {
        return GetLastError();
    }

    if (!ConvertSidToStringSid(sid, &sidstring)) {
        return GetLastError();
    }
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

