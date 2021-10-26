#ifndef CMAINDATA_H
#define CMAINDATA_H

#include <QObject>
#include <QDateTime>
#include <QBitArray>


enum TKeyCarrier {
  KC_NULL;
  KC_ARCHIVE,
  KC_KP_REGISTER,
  KC_KP_REMOVABLE_DRIVES
};

class CContainerData : public QObject
{
    Q_OBJECT

  public:
    explicit CContainerData(QObject *parent = nullptr);
    explicit CContainerData(TKeyCarrier vkey_carrier = KC_NULL, QObject *parent = nullptr);
    explicit CContainerData(QString vcontainer_name, TKeyCarrier vkey_carrier = KC_NULL, QObject *parent = nullptr);
    ~CContainerData();

    QString   ContainerName();
    void      SetContainerName(QString vcontainer_name);
    QDateTime StartKeyValidity();

    QDateTime EndKeyValidity();

    void      ExportContainer(QString vcontainer_path);
    void      ImportContainer(QString vcontainer_path);
    void      SaveConteinerToArchive(QString varchive_path);
    void      LoadContainerFromArchive(QString varchive_path);

  private:
    TKeyCarrier     key_carrier_        = KC_NULL;
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
