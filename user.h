#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    ~User();
    User(const User& user);
    User(int _id, QString _username, QString _password);
    int id;
    QString username;
    QString password;
};

#endif // USER_H
