#include <QSettings>
#include <QFile>
#include <QDir>
#include <QMessageBox>

//#include <sstream>
//#include <iomanip>
//#include <stdio.h>
#include <windows.h>

#include "..\include\cmaindata.h"

#ifdef _WIN64
  #define CRYPTO_PRO_USERS_PATH (L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Crypto Pro\\Settings\\Users")
#else
  #define CRYPTO_PRO_USERS_PATH ("HKEY_LOCAL_MACHINE\\SOFTWARE\\Crypto Pro\\Settings\\Users")
#endif

CContainerData::CContainerData(QObject *parent) : QObject(parent)
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
  return start_key_validity_;
}

void CContainerData::SetStartKeyValidity(QDateTime vstart_key_validity)
{
  if (start_key_validity_ != vstart_key_validity) {
    start_key_validity_ = vstart_key_validity;
  };
}

QDateTime CContainerData::EndKeyValidity()
{
  return end_key_validity_;
}

void CContainerData::SetEndKeyValidity(QDateTime vend_key_validity)
{
  if (end_key_validity_ != vend_key_validity) {
    end_key_validity_ = vend_key_validity;
  };
}


QString CContainerData::NameKey()
{
  return name_key_;
}

void CContainerData::SetNameKey(QString vname_key)
{
  if (name_key_ != vname_key) {
    name_key_ = vname_key;
  };
}

QString CContainerData::HeaderKey()
{
  return header_key_;
}

void CContainerData::SetHeaderKey(QString vheader_key)
{
  if (header_key_ != vheader_key) {
    header_key_ = vheader_key;
  };
}

QString CContainerData::PrimaryKey()
{
  return primary_key_;
}

void CContainerData::SetPrimaryKey(QString vprimary_key)
{
  if (primary_key_ != vprimary_key) {
    primary_key_ = vprimary_key;
  };
}

QString CContainerData::MasksKey()
{
  return masks_key_;
}

void CContainerData::SetMasksKey(QString vmasks_key)
{
  if (masks_key_ != vmasks_key) {
    masks_key_ = vmasks_key;
  };
}

QString CContainerData::Primary2Key()
{
  return primary2_key_;
}

void CContainerData::SetPrimary2Key(QString vprimary2_key)
{
  if (primary2_key_ != vprimary2_key) {
    primary2_key_ = vprimary2_key;
  };
}

QString CContainerData::Masks2Key()
{
  return masks2_key_;
}

void CContainerData::SetMasks2Key(QString vmasks2_key)
{
  if (masks2_key_ != vmasks2_key) {
    masks2_key_ = vmasks2_key;
  };
}

void CContainerData::ExportContainer(QString vcontainer_path)
{
  if (container_name_ != "") {
    HKEY hkey;
    DWORD type;
    DWORD cbData;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((vcontainer_path + "\\" + container_name_).toStdWString().c_str()), 0, KEY_QUERY_VALUE , &hkey) == ERROR_SUCCESS)
    {
      if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
      {
        char* data = new char[cbData];
        DWORD size = cbData;

        if( RegQueryValueExW(hkey,L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
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

        if( RegQueryValueExW(hkey,L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
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

        if( RegQueryValueExW(hkey,L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
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

        if( RegQueryValueExW(hkey,L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
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

        if( RegQueryValueExW(hkey,L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
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

        if( RegQueryValueExW(hkey,L"name.key", NULL, NULL, reinterpret_cast<LPBYTE>(data), &size)  == ERROR_SUCCESS) {
          masks2_key_ = QString(data);
        } else {
          masks2_key_ = "";
        };
        delete[] (data);
      };

      RegCloseKey(hkey);
    } else {
      QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к контейнеру:" + container_name_);
    }
  } else {
    QMessageBox::warning(NULL, "Сообщение", "Не задано имя контейнера");
  };
}

void CContainerData::ImportContainer(QString vcontainer_path)
{
  if (container_name_ != "") {
    HKEY hkey;
    DWORD type;
    DWORD cbData;
    RegCreateKeyEx();
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((vcontainer_path + "\\" + container_name_).toStdWString().c_str()), 0, KEY_QUERY_VALUE , &hkey) == ERROR_SUCCESS)
    {


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
