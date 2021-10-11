#ifndef CMAINDATA_H
#define CMAINDATA_H

#include <QObject>

class CContainerData : public QObject
{
    Q_OBJECT

  public:
    explicit CContainerData(QObject *parent = nullptr);
    ~CContainerData();

    QString     ContainerName();
    void        SetContainerName(QString vcontainer_name);
    QByteArray  NameKey();
    void        SetNameKey(QByteArray vname_key);
    QByteArray  HeaderKey();
    void        SetHeaderKey(QByteArray vheader_key);
    QByteArray  PrimaryKey();
    void        SetPrimaryKey(QByteArray vprimary_key);
    QByteArray  MasksKey();
    void        SetMasksKey(QByteArray vmasks_key);
    QByteArray  Primary2Key();
    void        SetPrimary2Key(QByteArray vprimary2_key);
    QByteArray  Masks2Key();
    void        SetMasks2Key(QByteArray vmasks2_key);

    void        ExportContainer(QString vcontainer_path);
    void        ImportContainer(QString vcontainer_path);
    void        SaveConteinerToArchive(QString varchive_path);
    void        LoadContainerToArchive(QString varchive_path);

  private:
    QString    container_name_;
    QByteArray name_key_;
    QByteArray header_key_;
    QByteArray primary_key_;
    QByteArray masks_key_;
    QByteArray primary2_key_;
    QByteArray masks2_key_;

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
