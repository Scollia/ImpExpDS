#include <QDir>
#include <QFile>
#include <QSettings>
#include <QMessageBox>

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

bool CContainerData::IsCorrectKeyCarrier()
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

  return true;
}


QByteArray  CContainerData::NameKey()
{
  QByteArray ret;

  ret.fromRawData((char*) name_key_, name_key_size_);
  return ret;
}

QByteArray  CContainerData::HeaderKey()
{
  QByteArray ret;

  ret.fromRawData((char*) header_key_, header_key_size_);
  return ret;
}

QByteArray  CContainerData::PrimaryKey()
{
  QByteArray ret;

  ret.fromRawData((char*) primary_key_, primary_key_size_);
  return ret;
}

QByteArray  CContainerData::MasksKey()
{
  QByteArray ret;

  ret.fromRawData((char*) masks_key_, masks_key_size_);
  return ret;
}

QByteArray  CContainerData::Primary2Key()
{
  QByteArray ret;

  ret.fromRawData((char*) primary2_key_, primary2_key_size_);
  return ret;
}

QByteArray  CContainerData::Masks2Key()
{
  QByteArray ret;

  ret.fromRawData((char*) masks2_key_, masks2_key_size_);
  return ret;
}

bool CContainerData::ImportContainer(TKeyCarrier vkey_carrier_type, QString vkey_carrier_root)
{
  if (vkey_carrier_type != KC_NULL) {
    SetKeyCarrierType(vkey_carrier_type);
  };
  if (vkey_carrier_root != "") {
    SetKeyCarrierRoot(vkey_carrier_root);
  };

  return ImportContainer();
}

bool CContainerData::ImportContainer(QString vcontainer_name, TKeyCarrier vkey_carrier_type, QString vkey_carrier_root)
{
  if (vkey_carrier_type != KC_NULL) {
    SetKeyCarrierType(vkey_carrier_type);
  };
  if (vkey_carrier_root != "") {
    SetKeyCarrierRoot(vkey_carrier_root);
  };
  if (vcontainer_name != "") {
    SetContainerName(vcontainer_name);
  };

  return ImportContainer();
}

bool CContainerData::ImportContainer()
{
  if (IsCorrectKeyCarrier()) {

    switch (key_carrier_type_) {
      case KC_NULL: {
        QMessageBox::warning(NULL, "Сообщение", "Не задан тип ключевого носителя");
        return false;
      }; break;
      case KC_ARCHIVE: {
        QDir archive;

        if (archive.exists(key_carrier_root_)){
          QFile file(key_carrier_root_ + "\\"+ container_name_);

          if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_6_0);

//          in >> start_key_validity_ >> end_key_validity_ >> name_key_ >> header_key_ >> primary_key_ >> masks_key_ >> primary2_key_ >> masks2_key_;
          } else {
            QMessageBox::warning(NULL, "Сообщение", "Отсутствует контейнер:\n" + container_name_);
          };
        } else {
          QMessageBox::warning(NULL, "Сообщение", "Отсутствует архив контейнеров:\n" + key_carrier_root_);
        };
      }; break;
      case KC_KP_REGISTER: {
        HKEY hkey;
        DWORD type;

        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((key_carrier_root_ + "\\" + container_name_).toStdWString().c_str()), 0, KEY_QUERY_VALUE , &hkey) == ERROR_SUCCESS)
        {
          if (RegQueryValueEx(hkey, L"name.key", NULL, &type, NULL, &name_key_size_) == ERROR_SUCCESS)
          {
            name_key_ = (unsigned char*) realloc(name_key_, name_key_size_);
            if(RegQueryValueExW(hkey, L"name.key", NULL, NULL, name_key_, &name_key_size_) != ERROR_SUCCESS) {
              free (name_key_);
            };
          };

          if (RegQueryValueEx(hkey, L"header.key", NULL, &type, NULL, &header_key_size_) == ERROR_SUCCESS)
          {
            header_key_ =(unsigned char*)  realloc(header_key_, header_key_size_);
            if(RegQueryValueExW(hkey, L"header.key", NULL, NULL, header_key_, &header_key_size_) != ERROR_SUCCESS) {
              free (header_key_);
            };
          };

          if (RegQueryValueEx(hkey, L"primary.key", NULL, &type, NULL, &primary_key_size_) == ERROR_SUCCESS)
          {
            primary_key_ = (unsigned char*) realloc(primary_key_, primary_key_size_);
            if( RegQueryValueExW(hkey, L"primary.key", NULL, NULL, primary_key_, &primary_key_size_)  != ERROR_SUCCESS) {
              free (primary_key_);
            };
          };

          if (RegQueryValueEx(hkey, L"masks.key", NULL, &type, NULL, &masks_key_size_) == ERROR_SUCCESS)
          {
            masks_key_ = (unsigned char*) realloc(masks_key_, masks_key_size_);
            if( RegQueryValueExW(hkey, L"masks.key", NULL, NULL, masks_key_, &masks_key_size_)  != ERROR_SUCCESS) {
              free (masks_key_);
            };
          };

          if (RegQueryValueEx(hkey, L"primary2.key", NULL, &type, NULL, &primary2_key_size_) == ERROR_SUCCESS)
          {
            primary2_key_ = (unsigned char*) realloc(primary2_key_, primary2_key_size_);
            if( RegQueryValueExW(hkey, L"primary2.key", NULL, NULL, primary2_key_, &primary2_key_size_)  != ERROR_SUCCESS) {
              free (primary2_key_);
            };
          };

          if (RegQueryValueEx(hkey, L"masks2.key", NULL, &type, NULL, &masks2_key_size_) == ERROR_SUCCESS)
          {
            masks2_key_ = (unsigned char*) realloc(masks2_key_, masks2_key_size_);
            if( RegQueryValueExW(hkey, L"masks2.key", NULL, NULL, masks2_key_, &masks2_key_size_)  != ERROR_SUCCESS) {
              free (masks2_key_);
            };
          };

          RegCloseKey(hkey);
        } else {
          QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к контейнеру: " + container_name_);
          return false;
        };
      }; break;
      case KC_KP_REMOVABLE_DRIVES: {
        QMessageBox::warning(NULL, "Сообщение", "Данный тип ключевого носителя неподдерживается");
        return false;
      }; break;
      default: {
        QMessageBox::warning(NULL, "Сообщение", "Неизвестный тип ключевого носителя");
        return false;
      };
    };

    return true;
  } else {
    return false;
  };
}

bool CContainerData::ExportContainer(TKeyCarrier vkey_carrier_type, QString vkey_carrier_root)
{
  if (vkey_carrier_type != KC_NULL) {
    SetKeyCarrierType(vkey_carrier_type);
  };
  if (vkey_carrier_root != "") {
    SetKeyCarrierRoot(vkey_carrier_root);
  };

  return ExportContainer();
}

bool CContainerData::ExportContainer(QString vcontainer_name, TKeyCarrier vkey_carrier_type, QString vkey_carrier_root)
{
  if (vkey_carrier_type != KC_NULL) {
    SetKeyCarrierType(vkey_carrier_type);
  };
  if (vkey_carrier_root != "") {
    SetKeyCarrierRoot(vkey_carrier_root);
  };
  if (vcontainer_name != "") {
    SetContainerName(vcontainer_name);
  };

  return ExportContainer();
}

bool CContainerData::ExportContainer()
{
  if (IsCorrectKeyCarrier()) {

    switch (key_carrier_type_) {
      case KC_NULL: {
        QMessageBox::warning(NULL, "Сообщение", "Не задан тип ключевого носителя");
        return false;
      }; break;
      case KC_ARCHIVE: {
        QDir archive;

        if (!archive.exists(key_carrier_root_)) {
          archive.mkpath(key_carrier_root_);
        };

        if (archive.exists(key_carrier_root_)) {
          QFile file(key_carrier_root_ + "\\" + container_name_);

          if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_6_0);

            out << start_key_validity_ << end_key_validity_ << HeaderKey() << HeaderKey() << PrimaryKey() << MasksKey() << Primary2Key() << Masks2Key();
          };
        } else {
          QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к архиву контейнеров:\n" + key_carrier_root_);
          return false;
        };
      }; break;
      case KC_KP_REGISTER: {
        HKEY hkey;
        DWORD lpdwDisposition;

        RegCreateKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((key_carrier_root_ + "\\" + container_name_).toStdWString().c_str()), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &lpdwDisposition);

        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<const wchar_t*>((key_carrier_root_ + "\\" + container_name_).toStdWString().c_str()), 0, KEY_QUERY_VALUE , &hkey) == ERROR_SUCCESS) {
          QMessageBox::warning(NULL, "Сообщение", "Все в норме");

          RegCloseKey(hkey);
        } else {
          QMessageBox::warning(NULL, "Сообщение", "Ошибка доступа к контейнеру: " + container_name_);
          return false;
        };
      }; break;
      case KC_KP_REMOVABLE_DRIVES: {
        QMessageBox::warning(NULL, "Сообщение", "Данный тип ключевого носителя неподдерживается");
        return false;
      }; break;
      default: {
        QMessageBox::warning(NULL, "Сообщение", "Неизвестный тип ключевого носителя");
        return false;
      };
    };

    return true;
  } else {
    return false;
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
