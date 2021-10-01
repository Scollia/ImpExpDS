#include "..\include\cprogrammoptions.h"
#include "..\mainwindow.h"

#include <QSettings>
#include <Windows.h>
//#include <winbase.h>
#include <Sddl.h>

#define INFO_BUFFER_SIZE 32767

CProgrammOptions::CProgrammOptions(QObject *parent) : QObject(parent)
{
// Определение имени текущего пользователя
  user_name_ = "";

  TCHAR  buf_user_name[INFO_BUFFER_SIZE];
  DWORD  buf_user_name_char_count = INFO_BUFFER_SIZE;

  if (GetUserName(buf_user_name, &buf_user_name_char_count)) {
    user_name_ = QString::fromWCharArray(buf_user_name, buf_user_name_char_count);
  };

// Определение SID и домен текущего пользователя
  user_sid_     = "";
  user_domain_  = "";
  if (user_name_ != "") {
    LPTSTR        sid_string = NULL;
    SID_NAME_USE  sid_type;
    PSID          buf_sid;
    TCHAR*        buf_domain_name;

    DWORD         sid_size = 0;
    DWORD         domdomain_name_size = 0;

    LookupAccountName(NULL, buf_user_name, NULL, &sid_size, NULL, &domdomain_name_size, &sid_type);
    buf_sid = (SID*) malloc(sid_size * sizeof(SID));
    buf_domain_name = (TCHAR*) malloc(domdomain_name_size * sizeof(TCHAR));

    if (LookupAccountName(NULL, buf_user_name, buf_sid, &sid_size, buf_domain_name, &domdomain_name_size, &sid_type)) {
      if (ConvertSidToStringSid(buf_sid, &sid_string)) {
        user_sid_ = QString::fromWCharArray(sid_string);
      };
      user_domain_ = QString::fromWCharArray(buf_domain_name);
    };

    free (buf_sid);
    free (buf_domain_name);
  };
}

//CProgrammOptions::~CProgrammOptions()
//{

//}

void CProgrammOptions::Load()
{
  QSettings* tmpSettings = new QSettings(this);

  tmpSettings->beginGroup("Main");
  path_to_archive_ = tmpSettings->value("PathToArchive", ".\\DSArchive").toString();
  tmpSettings->endGroup();

  tmpSettings->beginGroup("Position");
  tmpSettings->beginGroup("MainWindows");
  ((MainWindow*) parent())->setGeometry(tmpSettings->value("x", 50).toInt(), tmpSettings->value("y", 50).toInt(), tmpSettings->value("width", 800).toInt(), tmpSettings->value("height", 400).toInt());
  tmpSettings->endGroup();
  tmpSettings->endGroup();

};

void CProgrammOptions::Save()
{
  if (path_to_archive_ == "") {
    path_to_archive_ = ".\\DSArchive";
  };

  QSettings* tmpSettings = new QSettings(this);

  tmpSettings->beginGroup("Main");
  tmpSettings->setValue("PathToArchive", path_to_archive_);
  tmpSettings->endGroup();

  tmpSettings->beginGroup("Position");
  tmpSettings->beginGroup("MainWindows");

  tmpSettings->setValue("x", ((MainWindow*) parent())->x());
  tmpSettings->setValue("y", ((MainWindow*) parent())->y());
  tmpSettings->setValue("width", ((MainWindow*) parent())->width());
  tmpSettings->setValue("height", ((MainWindow*) parent())->height());
  tmpSettings->endGroup();
  tmpSettings->endGroup();
};

QString CProgrammOptions::UserName()
{
  return user_name_;
}

void CProgrammOptions::SetUserName(QString user_name)
{
  if (user_name_ != user_name) {
    user_name_ = user_name;
  };
}

QString CProgrammOptions::UserSID()
{
  return user_sid_;
}

void CProgrammOptions::SetUserSID(QString user_sid)
{
  if (user_sid_ != user_sid) {
    user_sid_ = user_sid;
  };
}

QString CProgrammOptions::UserDomain()
{
  return user_domain_;
}

void CProgrammOptions::SetUserDomain(QString user_domain)
{
  if (user_domain_ != user_domain) {
    user_domain_ = user_domain;
  };
}

QString CProgrammOptions::PathToArchive()
{
  return path_to_archive_;
}

void CProgrammOptions::PathToArchive(QString path_to_archive)
{
  if (path_to_archive_ != path_to_archive) {
    path_to_archive_ = path_to_archive;
  };
}
