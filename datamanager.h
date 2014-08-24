#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVector>
#include <QSqlDatabase>

class QString;
class AccountInfo;
class User;

class DataManager
{
public:
    DataManager();
    ~DataManager();

    static DataManager& getInstance(){
        static DataManager instance;
        return instance;
    }

    bool login(const QString& username,const QString& password);

    bool createUser(const QString& username, const QString& password);

    User getUserByName(const QString& username);

    QVector<AccountInfo> *getDataList(int userid,const QString& key);

    void addAccount(const AccountInfo& account, const QString &key);

    void delAccountById(int id);

    void modifyAccount(const AccountInfo& account, const QString& key);

    User getUserById(int id);

private:


    QSqlDatabase dbconn;
};

#endif // DATAMANAGER_H
