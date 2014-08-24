#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QString>

class AccountInfo
{

public:
    AccountInfo();
    ~AccountInfo();
    AccountInfo(int _id,QString _username, QString _password, QString _websitename);
    AccountInfo(int _id,QString _username, QString _password, QString _websitename,int _userid);
    AccountInfo &operator =(const AccountInfo&);
    AccountInfo(const AccountInfo &account);

    int id;
    int userid;
    QString username;
    QString password;
    QString websitename;

    void changeAccount(int index, QString content);
};

//Q_DECLARE_METATYPE(AccountInfo)

#endif // ACCOUNTINFO_H
