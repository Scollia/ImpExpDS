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
//  key_carrier_type_   = KC_NULL;
//  key_carrier_root_   = "";
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

CContainerData::CContainerData(TKeyCarrier vkey_carrier_type, QString vkey_carrier_root, QObject *parent) : QObject(parent)
{
  key_carrier_type_   = vkey_carrier_type;
  key_carrier_root_   = vkey_carrier_root;

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

CContainerData::CContainerData(QString vcontainer_name, TKeyCarrier vkey_carrier_type, QString vkey_carrier_root, QObject *parent) : QObject(parent)
{
  key_carrier_type_   = vkey_carrier_type;
  key_carrier_root_   = vkey_carrier_root;
  container_name_     = vcontainer_name;

//  start_key_validity_ = QDateTime::currentDateTime();
//  end_key_validity_   = QDateTime::currentDateTime();
//  name_key_           = nullptr;
//  header_key_         = nullptr;
//  primary_key_        = nullptr;
//  masks_key_          = nullptr;
//  primary2_key_       = nullptr;
//  masks2_key_         = nullptr;
}

CContainerData::~CContainerData()
{
  free (name_key_);
  free (header_key_);
  free (primary_key_);
  free (masks_key_);
  free (primary2_key_);
  free (masks2_key_);
}

TKeyCarrier CContainerData::KeyCarrierType()
{
  return key_carrier_type_;
}

void CContainerData::SetKeyCarrierType(TKeyCarrier vkey_carrier_type)
{
  if (key_carrier_type_ != vkey_carrier_type) {
    key_carrier_type_   = vkey_carrier_type;
    SetKeyCarrierRoot("");
  };
}

QString CContainerData::KeyCarrierRoot()
{
  return key_carrier_root_;
}

void CContainerData::SetKeyCarrierRoot(QString vkey_carrier_root)
{
  if (key_carrier_root_ != vkey_carrier_root) {
    key_carrier_root_   = vkey_carrier_root;
  };
}

QString CContainerData::ContainerName()
{
  return container_name_;
}

void CContainerData::SetContainerName(QString vcontainer_name)
{
  if (container_name_ != vcontainer_name) {
    container_name_ = vcontainer_name;

    start_key_validity_ = QDateTime::currentDateTime();
    end_key_validity_   = QDateTime::currentDateTime();

    free (name_key_);
    free (header_key_);
    free (primary_key_);
    free (masks_key_);
    free (primary2_key_);
    free (masks2_key_);
  };
}

QDateTime CContainerData::StartKeyValidity()
{
  return start_key_validity_;
}

QDateTime CContainerData::EndKeyValidity()
{
  return end_key_validity_;
}

bool CContainerData::ExportContainer(TKeyCarrier vkey_carrier_type, QString vkey_carrier_root)
{
  SetKeyCarrierType(vkey_carrier_type);
  SetKeyCarrierRoot(vkey_carrier_root);

  return ExportContainer();
}

bool CContainerData::ExportContainer(QString vcontainer_name, TKeyCarrier vkey_carrier_type, QString vkey_carrier_root)
{
  SetKeyCarrierType(vkey_carrier_type);
  SetKeyCarrierRoot(vkey_carrier_root);
  SetContainerName(vcontainer_name);

  return ExportContainer();
}

bool CContainerData::ExportContainer()
{
  if (key_carrier_type_ == KC_NULL) {
    QMessageBox::warning(NULL, "Сообщение", "Не задан тип ключевого носителя");
    return false;
  } else {
    if (key_carrier_root_ == "") {
      QMessageBox::warning(NULL, "Сообщение", "Не задан путь к ключевому носителю");
      return false;
    } else {
      if (container_name_ == "") {
        QMessageBox::warning(NULL, "Сообщение", "Не задано имя контейнера ключа");
        return false;
      };
    };
  };

  switch (key_carrier_type_) {
    case KC_NULL: {
      QMessageBox::warning(NULL, "Сообщение", "Не задан тип ключевого носителя");
      return false;
    }; break;
    case KC_ARCHIVE: {

    }; break;
    case KC_KP_REGISTER: {
      HKEY hkey;
      DWORD type;
      DWORD cbData;

      if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((key_carrier_root_ + "\\" + container_name_).toStdWString().c_str()), 0, KEY_QUERY_VALUE , &hkey) == ERROR_SUCCESS)
      {
        if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
        {
          realloc(name_key_, cbData);
          if( RegQueryValueExW(hkey, L"name.key", NULL, NULL, name_key_, &cbData)  != ERROR_SUCCESS) {
            free (name_key_);
          };
        };

        if (RegQueryValueEx(hkey, L"header.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
        {
          realloc(header_key_, cbData);
          if( RegQueryValueExW(hkey, L"header.key", NULL, NULL, header_key_, &cbData)  != ERROR_SUCCESS) {
            free (header_key_);
          };
        };

        if (RegQueryValueEx(hkey, L"primary.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
        {
          realloc(primary_key_, cbData);
          if( RegQueryValueExW(hkey, L"primary.key", NULL, NULL, primary_key_, &cbData)  != ERROR_SUCCESS) {
            free (primary_key_);
          };
        };

        if (RegQueryValueEx(hkey, L"masks.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
        {
          realloc(masks_key_, cbData);
          if( RegQueryValueExW(hkey, L"masks.key", NULL, NULL, masks_key_, &cbData)  != ERROR_SUCCESS) {
            free (masks_key_);
          };
        };

        if (RegQueryValueEx(hkey, L"primary2.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
        {
          realloc(primary2_key_, cbData);
          if( RegQueryValueExW(hkey, L"primary2.key", NULL, NULL, primary2_key_, &cbData)  != ERROR_SUCCESS) {
            free (primary2_key_);
          };
        };

        if (RegQueryValueEx(hkey, L"masks2.key", NULL, &type, NULL, &cbData) == ERROR_SUCCESS)
        {
          realloc(masks2_key_, cbData);
          if( RegQueryValueExW(hkey, L"masks2.key", NULL, NULL, masks2_key_, &cbData)  != ERROR_SUCCESS) {
            free (masks2_key_);
          };
        };

        RegCloseKey(hkey);
      } else {
        QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к контейнеру: " + container_name_);
      };
    }; break;
    case KC_KP_REMOVABLE_DRIVES: {
      QMessageBox::warning(NULL, "Сообщение", "Данный тип ключевого носителя неподдерживается");
    }; break;
    default: {
      QMessageBox::warning(NULL, "Сообщение", "Неизвестный тип ключевого носителя");

    };
  }

  return true;
}

//====

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
