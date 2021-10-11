#include <QSettings>
#include <QFile>

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

QByteArray CContainerData::NameKey()
{
  return name_key_;
}

void CContainerData::SetNameKey(QByteArray vname_key)
{
  if (name_key_ != vname_key) {
    name_key_ = vname_key;
  };
}

QByteArray CContainerData::HeaderKey()
{
  return header_key_;
}

void CContainerData::SetHeaderKey(QByteArray vheader_key)
{
  if (header_key_ != vheader_key) {
    header_key_ = vheader_key;
  };
}

QByteArray CContainerData::PrimaryKey()
{
  return primary_key_;
}

void CContainerData::SetPrimaryKey(QByteArray vprimary_key)
{
  if (primary_key_ != vprimary_key) {
    primary_key_ = vprimary_key;
  };
}

QByteArray CContainerData::MasksKey()
{
  return masks_key_;
}

void CContainerData::SetMasksKey(QByteArray vmasks_key)
{
  if (masks_key_ != vmasks_key) {
    masks_key_ = vmasks_key;
  };
}

QByteArray CContainerData::Primary2Key()
{
  return primary2_key_;
}

void CContainerData::SetPrimary2Key(QByteArray vprimary2_key)
{
  if (primary2_key_ != vprimary2_key) {
    primary2_key_ = vprimary2_key;
  };
}

QByteArray CContainerData::Masks2Key()
{
  return masks2_key_;
}

void CContainerData::SetMasks2Key(QByteArray vmasks2_key)
{
  if (masks2_key_ != vmasks2_key) {
    masks2_key_ = vmasks2_key;
  };
}

void CContainerData::ExportContainer(QString vcontainer_path)
{
  QSettings*   tmpSettings   = new QSettings(vcontainer_path, QSettings::NativeFormat);

  name_key_       = tmpSettings->value("name.key").toByteArray();
  header_key_     = tmpSettings->value("header.key").toByteArray();
  primary_key_    = tmpSettings->value("primary.key").toByteArray();
  masks_key_      = tmpSettings->value("masks.key").toByteArray();
  primary2_key_   = tmpSettings->value("primary2.key").toByteArray();
  masks2_key_     = tmpSettings->value("masks2.key").toByteArray();

  delete tmpSettings;
}

void CContainerData::ImportContainer(QString vcontainer_path)
{

}

void CContainerData::SaveConteinerToArchive(QString varchive_path)
{
  QFile file(varchive_path);

  if (file.open(QIODevice::WriteOnly)) {
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_1);

    out << name_key_ << header_key_ << primary_key_ << masks_key_ << primary2_key_ << masks2_key_;
  };
}

void CContainerData::LoadContainerToArchive(QString varchive_path)
{

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
