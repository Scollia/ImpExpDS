#ifndef CPROGRAMMOPTIONS_H
#define CPROGRAMMOPTIONS_H

#include <QString>

class CProgrammOptions
{
public:
  CProgrammOptions();
  ~CProgrammOptions();

  QString UserName();
  void    SetUserName(QString user_name);
  QString UserSID();
  void    SetUserSID(QString user_sid);
  QString UserDomain();
  void    SetUserDomain(QString user_domain);

private:
  QString user_name_;
  QString user_sid_;
  QString user_domain_;
};

#endif // CPROGRAMMOPTIONS_H
