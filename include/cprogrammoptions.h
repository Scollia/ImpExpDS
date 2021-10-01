#ifndef CPROGRAMMOPTIONS_H
#define CPROGRAMMOPTIONS_H

#include <QObject>
#include <QString>

class CProgrammOptions : public QObject
{
    Q_OBJECT
  public:
    explicit CProgrammOptions(QObject *parent = nullptr);
//    ~CProgrammOptions();
    void Load();
    void Save();

    QString UserName();
    void    SetUserName(QString user_name);
    QString UserSID();
    void    SetUserSID(QString user_sid);
    QString UserDomain();
    void    SetUserDomain(QString user_domain);
    QString PathToArchive();
    void    PathToArchive(QString path_to_archive);


  private:
    QString user_name_;
    QString user_sid_;
    QString user_domain_;

    QString path_to_archive_;
  signals:
};

#endif // CPROGRAMMOPTIONS_H
