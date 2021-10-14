#ifndef CMAINDATA_H
#define CMAINDATA_H

#include <QObject>
#include <QDateTime>
#include <QBitArray>


class CContainerData : public QObject
{
    Q_OBJECT

  public:
    explicit CContainerData(QObject *parent = nullptr);
    ~CContainerData();

    QString   ContainerName();
    void      SetContainerName(QString vcontainer_name);
    QDateTime StartKeyValidity();
    void      SetStartKeyValidity(QDateTime vstart_key_validity);
    QDateTime EndKeyValidity();
    void      SetEndKeyValidity(QDateTime vend_key_validity);
    QString   NameKey();
    void      SetNameKey(QString vname_key);
    QString   HeaderKey();
    void      SetHeaderKey(QString vheader_key);
    QString   PrimaryKey();
    void      SetPrimaryKey(QString vprimary_key);
    QString   MasksKey();
    void      SetMasksKey(QString vmasks_key);
    QString   Primary2Key();
    void      SetPrimary2Key(QString vprimary2_key);
    QString   Masks2Key();
    void      SetMasks2Key(QString vmasks2_key);

    void      ExportContainer(QString vcontainer_path);
    void      ImportContainer(QString vcontainer_path);
    void      SaveConteinerToArchive(QString varchive_path);
    void      LoadContainerFromArchive(QString varchive_path);

  private:
    QString   container_name_;
    QDateTime start_key_validity_;
    QDateTime end_key_validity_;
    QString   name_key_;
    QString   header_key_;
    QString   primary_key_;
    QString   masks_key_;
    QString   primary2_key_;
    QString   masks2_key_;

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
