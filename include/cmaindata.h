#ifndef CMAINDATA_H
#define CMAINDATA_H

#include <QObject>

class CContainerData : public QObject
{
    Q_OBJECT
  public:
    explicit CContainerData(QObject *parent = nullptr);
    ~CContainerData();

  private:

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
