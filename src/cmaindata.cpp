#include <QDir>
#include <QFile>
#include <QSettings>
#include <QMessageBox>

#include <windows.h>

#include "..\include\cmaindata.h"

#define ALL_REMOVABLE_DRIVES

#ifdef _WIN64
  #define CRYPTO_PRO_USERS_PATH (L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Crypto Pro\\Settings\\Users")
#else
  #define CRYPTO_PRO_USERS_PATH ("HKEY_LOCAL_MACHINE\\SOFTWARE\\Crypto Pro\\Settings\\Users")
#endif

CContainerData::CContainerData(QObject *parent) : QObject(parent)
{
//  key_carrier_        = KC_NULL;
//  container_name_     = "";
//  start_key_validity_ = QDateTime::currentDateTime();
//  end_key_validity_   = QDateTime::currentDateTime();
//  name_key_           = nullptr;
//  header_key_         = nullptr;
//  primary_key_        = nullptr;
//  masks_key_          = nullptr;
//  primary2_key_       = nullptr;
//  masks2_key_         = nullptr;
}

CContainerData::CContainerData(TKeyCarrier vkey_carrier, QObject *parent)
{
  key_carrier_        = vkey_carrier;
  container_name_     = "";
  start_key_validity_ = QDateTime::currentDateTime();
  end_key_validity_   = QDateTime::currentDateTime();
  name_key_           = nullptr;
  header_key_         = nullptr;
  primary_key_        = nullptr;
  masks_key_          = nullptr;
  primary2_key_       = nullptr;
  masks2_key_         = nullptr;
}

CContainerData::CContainerData(QString vcontainer_name, TKeyCarrier vkey_carrier, QObject *parent)
{

}

CContainerData::~CContainerData()
{

}

QString CContainerData::ContainerName()
{
  return container_name_;
}

void CContainerData::SetContainerName(QString vcontainer_name)
{
  if (container_name_ != vcontainer_name) {
    container_name_ = vcontainer_name;
  };
}

QDateTime CContainerData::StartKeyValidity()
{
  //  if (start_key_validity_ != vstart_key_validity) {
  //    start_key_validity_ = vstart_key_validity;
  //  };
  return start_key_validity_;
}

QDateTime CContainerData::EndKeyValidity()
{
//  if (end_key_validity_ != vend_key_validity) {
//    end_key_validity_ = vend_key_validity;
//  };
  return end_key_validity_;
}


//  if (name_key_ != vname_key) {
//    name_key_ = vname_key;
//  };
//  if (header_key_ != vheader_key) {
//    header_key_ = vheader_key;
//  };

//  if (primary_key_ != vprimary_key) {
//    primary_key_ = vprimary_key;
//  };
//  if (masks_key_ != vmasks_key) {
//    masks_key_ = vmasks_key;
//  };
//  if (primary2_key_ != vprimary2_key) {
//    primary2_key_ = vprimary2_key;
//  };
//  if (masks2_key_ != vmasks2_key) {
//    masks2_key_ = vmasks2_key;
//  };


void CContainerData::ExportContainer(QString vcontainer_path)
{
  if (container_name_ != "") {
    HKEY hkey;
    DWORD type;
    DWORD cbData;

QMessageBox::warning(NULL, "Сообщение", vcontainer_path + "\\" + container_name_);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((vcontainer_path + "\\" + container_name_).toStdWString().c_str()), 0, KEY_QUERY_VALUE , &hkey) == ERROR_SUCCESS)
    {
      if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
      {
        char* data = new char[cbData];
        DWORD size = cbData;

        if( RegQueryValueExW(hkey, L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
          name_key_ = QString(data);
        } else {
          name_key_ = "";
        };
        delete[] (data);
      };

      if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
      {
        char* data = new char[cbData];
        DWORD size = cbData;

        if( RegQueryValueExW(hkey, L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
          header_key_ = QString(data);
        } else {
          header_key_ = "";
        };
        delete[] (data);
      };
      if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
      {
        char* data = new char[cbData];
        DWORD size = cbData;

        if( RegQueryValueExW(hkey, L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
          primary_key_ = QString(data);
        } else {
          primary_key_ = "";
        };
        delete[] (data);
      };

      if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
      {
        char* data = new char[cbData];
        DWORD size = cbData;

        if( RegQueryValueExW(hkey, L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
          masks_key_ = QString(data);
        } else {
          masks_key_ = "";
        };
        delete[] (data);
      };

      if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
      {
        char* data = new char[cbData];
        DWORD size = cbData;

        if( RegQueryValueExW(hkey, L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
          primary2_key_ = QString(data);
        } else {
          primary2_key_ = "";
        };
        delete[] (data);
      };

      if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
      {
        char* data = new char[cbData];
        DWORD size = cbData;

        if( RegQueryValueExW(hkey, L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
          masks2_key_ = QString(data);
        } else {
          masks2_key_ = "";
        };
        delete[] (data);
      };

      RegCloseKey(hkey);
    } else {
      QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к контейнеру: " + container_name_);
    }
  } else {
    QMessageBox::warning(NULL, "Сообщение", "Не задано имя контейнера");
  };
}

void CContainerData::ImportContainer(QString vcontainer_path)
{
  if (container_name_ != "") {
    HKEY hkey;
//    DWORD type;
//    DWORD cbData;
    DWORD lpdwDisposition;
//    RegCreateKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((vcontainer_path + "\\" + container_name_).toStdWString().c_str()), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_QUERY_VALUE, NULL, &hkey, &lpdwDisposition);
    RegCreateKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((vcontainer_path + "\\" + container_name_).toStdWString().c_str()), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &lpdwDisposition);
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((vcontainer_path + "\\" + container_name_).toStdWString().c_str()), 0, KEY_QUERY_VALUE, &hkey) == ERROR_SUCCESS)
    {
//      if (RegSetValueEx(runKey, packageName, 0, REG_SZ, (BYTE*)machineInstallFolder, (wcsnlen(machineInstallFolder, sizeof(machineInstallFolder)) + 1) * sizeof(wchar_t)) != ERROR_SUCCESS) {
//              return GetLastError();
//      }
QMessageBox::warning(NULL, "Сообщение", "Все в норме");
      RegCloseKey(hkey);
    } else {
      QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к контейнеру:" + container_name_);
    }
  } else {
    QMessageBox::warning(NULL, "Сообщение", "Не задано имя контейнера");
  };
}

void CContainerData::SaveConteinerToArchive(QString varchive_path)
{
  if (container_name_ != "") {
    QDir archive;

    if (!archive.exists(varchive_path)) {
      archive.mkpath(varchive_path);
    };

    if (archive.exists(varchive_path)) {
      QFile file(varchive_path + "\\" + container_name_);

      if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_6_0);

        out << start_key_validity_ << end_key_validity_ << name_key_ << header_key_ << primary_key_ << masks_key_ << primary2_key_ << masks2_key_;
      };
    } else {
      QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к архиву контейнеров:\n" + varchive_path);
    };
  } else {
    QMessageBox::warning(NULL, "Сообщение", "Не задано имя контейнера");
  };
}

void CContainerData::LoadContainerFromArchive(QString varchive_path)
{
  if (container_name_ != "") {
    QDir archive;

    if (archive.exists(varchive_path)){
      QFile file(varchive_path + "\\"+ container_name_);

      if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_0);

        in >> start_key_validity_ >> end_key_validity_ >> name_key_ >> header_key_ >> primary_key_ >> masks_key_ >> primary2_key_ >> masks2_key_;
      } else {
        QMessageBox::warning(NULL, "Сообщение", "Отсутствует контейнер:\n" + container_name_);
      };
    } else {
      QMessageBox::warning(NULL, "Сообщение", "Отсутствует архив контейнеров:\n" + varchive_path);
    };
  } else {
    QMessageBox::warning(NULL, "Сообщение", "Не задано имя контейнера");
  };
}

CMainData::CMainData(QObject *parent) : QObject(parent)
{

}

CMainData::~CMainData()
{
  while (!container_data_.isEmpty()) {
    delete container_data_.takeFirst();
  };
}
