#ifndef CMAINDATA_H
#define CMAINDATA_H

#include <QObject>
#include <QDateTime>
#include <QBitArray>

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
    bool IsCorrectKeyCarrier();


    TKeyCarrier     key_carrier_type_   = KC_NULL;
    QString         key_carrier_root_     = "";
    QString         container_name_     = "";
    QDateTime       start_key_validity_ = QDateTime::currentDateTime();
    QDateTime       end_key_validity_   = QDateTime::currentDateTime();
    unsigned char*  name_key_           = nullptr;
    unsigned char*  header_key_         = nullptr;
    unsigned char*  primary_key_        = nullptr;
    unsigned char*  masks_key_          = nullptr;
    unsigned char*  primary2_key_       = nullptr;
    unsigned char*  masks2_key_         = nullptr;

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
