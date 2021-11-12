#ifndef CMAINDATA_H
#define CMAINDATA_H

#include <QObject>
#include <QDateTime>
#include <QBitArray>

#include <windows.h>

enum TKeyCarrier {
  KC_NULL,
  KC_ARCHIVE,
  KC_KP_REGISTER,
  KC_KP_REMOVABLE_DRIVES
};

class CContainerData : public QObject
{
    Q_OBJECT

  public:
    explicit CContainerData(QObject *parent = nullptr);
    explicit CContainerData(TKeyCarrier vkey_carrier_type, QString vkey_carrier_root = "", QObject *parent = nullptr);
    explicit CContainerData(QString vcontainer_name, TKeyCarrier vkey_carrier_type = KC_NULL, QString vkey_carrier_root = "", QObject *parent = nullptr);
    ~CContainerData();

    TKeyCarrier KeyCarrierType();
    void        SetKeyCarrierType(TKeyCarrier vkey_carrier_type);
    QString     KeyCarrierRoot();
    void        SetKeyCarrierRoot(QString vkey_carrier_root);
    QString     ContainerName();
    void        SetContainerName(QString vcontainer_name);
    QDateTime   StartKeyValidity();
    QDateTime   EndKeyValidity();

    bool      ImportContainer();
    bool      ImportContainer(TKeyCarrier vkey_carrier_type, QString vkey_carrier_root = "");
    bool      ImportContainer(QString vcontainer_name, TKeyCarrier vkey_carrier_type = KC_NULL, QString vkey_carrier_root = "");

    bool      ExportContainer();
    bool      ExportContainer(TKeyCarrier vkey_carrier_type, QString vkey_carrier_root = "");
    bool      ExportContainer(QString vcontainer_name, TKeyCarrier vkey_carrier_type = KC_NULL, QString vkey_carrier_root = "");

  private:
    bool        IsCorrectKeyCarrier();

    QByteArray  NameKey();
    QByteArray  HeaderKey();
    QByteArray  PrimaryKey();
    QByteArray  MasksKey();
    QByteArray  Primary2Key();
    QByteArray  Masks2Key();

    TKeyCarrier     key_carrier_type_   = KC_NULL;
    QString         key_carrier_root_     = "";
    QString         container_name_     = "";
    QDateTime       start_key_validity_ = QDateTime::currentDateTime();
    QDateTime       end_key_validity_   = QDateTime::currentDateTime();
    unsigned char*  name_key_           = nullptr;
    DWORD           name_key_size_      = 0;
    unsigned char*  header_key_         = nullptr;
    DWORD           header_key_size_    = 0;
    unsigned char*  primary_key_        = nullptr;
    DWORD           primary_key_size_   = 0;
    unsigned char*  masks_key_          = nullptr;
    DWORD           masks_key_size_     = 0;
    unsigned char*  primary2_key_       = nullptr;
    DWORD           primary2_key_size_  = 0;
    unsigned char*  masks2_key_         = nullptr;
    DWORD           masks2_key_size_    = 0;

  signals:
};

class CMainData : public QObject
{
  Q_OBJECT

  public:
    explicit CMainData(QObject *parent = nullptr);
    ~CMainData();
    void ReadUserConteiner(QString psid);
    void ExportUserConteiner(QString ppath_to_archive);
    void ImportArchiveConteiner(QString ppath_to_archive);

  private:
    QList<CContainerData*> container_data_;

  signals:
};

#endif // CMAINDATA_H
