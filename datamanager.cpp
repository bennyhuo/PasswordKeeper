#include "datamanager.h"
#include "QDebug"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <accountinfo.h>
#include <user.h>
#include <utils.h>

bool DataManager::login(const QString &username, const QString &password)
{
    qDebug() << "username:" << username << ";password:" << password;
    //select from the table, check them ..
    //    QSqlDatabase dbconn=QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动
    //    dbconn.setDatabaseName("datainfo");  //在工程目录新建一个mytest.db的文件
    //    if(!dbconn.open())    {
    //        qDebug()<<"Database open error!";
    //    }
    QSqlQuery query;//以下执行相关QSL语句

    QString cmd = "select password from userinfo where username='" + username+"'";
    query.exec(cmd);

    QString password0;
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录    {
        password0=query.value(0).toString();
    qDebug()<<password0;

    if(password==password0){
        qDebug()<< "Login successfully!";
        return true;
    }else{
        qDebug()<< "Username or password error.";
        return false;
    }
}

bool DataManager::createUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    QString cmd = "insert into userinfo(username,password) values('"+username+"','"+password+"')";
    return query.exec(cmd);
}

User DataManager::getUserByName(const QString &username)
{
    QSqlQuery query;//以下执行相关QSL语句

    QString cmd = "select id,password from userinfo where username='" + username+"'";
    query.exec(cmd);

    User user;
    if(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        user.id = query.value(0).toInt();
        user.username = username;
        user.password =query.value(1).toString();
    }else{
        user.id = -1;
    }
    return user;
}

QVector<AccountInfo> *DataManager::getDataList(int userid, const QString &key)
{
    QSqlQuery query;//以下执行相关QSL语句

    QString useridStr = QString::number(userid,10);
    QString cmd = "select id,username,password,websitename from passwordinfo where userid='" + useridStr+"'";
    query.exec(cmd);

    QVector<AccountInfo> *accountList = new QVector<AccountInfo>;
    while(query.next()){
        //query.next()指向查找到的第一条记录，然后每次后移一条记录    {
        int id  = query.value(0).toInt();
        QString username = query.value(1).toString();
        QString password = Utils::decryptByKey(key, query.value(2).toString());
        QString websitename = query.value(3).toString();
        AccountInfo account(id,username,password,websitename,userid);

        accountList->append(account);
    }
    return accountList;
}

void DataManager::addAccount(const AccountInfo &account ,const QString& key)
{
    QSqlQuery query;//以下执行相关QSL语句

    QString cmd = "insert into passwordinfo(username,password,websitename) values('"
            +account.username+"','"+Utils::cryptByKey(key, account.password)+"','"+account.websitename+"')";
    query.exec(cmd);
}

void DataManager::delAccountById(int id)
{
    QSqlQuery query;//以下执行相关QSL语句

    QString cmd = "delete from passwordinfo where id ="+QString::number(id);
    query.exec(cmd);
}

void DataManager::modifyAccount(const AccountInfo &account, const QString &key)
{
    QSqlQuery query;//以下执行相关QSL语句

    QString cmd = "select * from passwordinfo where id="+QString::number(account.id);
    query.exec(cmd);
    if(query.next()){
        cmd = "update passwordinfo set username='"+account.username+
                "',password='"+Utils::cryptByKey(key, account.password)+"',websitename='"+account.websitename+"' where id="+QString::number(account.id);
        query.exec(cmd);
    }else{
        QString cmd = "insert into passwordinfo(username,password,websitename,userid) values('"
                +account.username+"','"+Utils::cryptByKey(key, account.password)+"','"+account.websitename+"','"+QString::number(account.userid)+"')";
        query.exec(cmd);
    }
}

User DataManager::getUserById(int id)
{
    QSqlQuery query;//以下执行相关QSL语句

    QString idStr = QString::number(id);
    QString cmd = "select id,username,password from userinfo where id=" + idStr;
    query.exec(cmd);

    User user;
    if(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        user.id = query.value(0).toInt();
        user.password =query.value(1).toString();
    }else{
        user.id = -1;
    }
    return user;
}

DataManager::DataManager()
{
    dbconn = QSqlDatabase::addDatabase("QSQLITE");
    dbconn.setDatabaseName("datainfo");
    if(!dbconn.open()){
        qDebug() << "Databse open error!";
    }
}

DataManager::~DataManager()
{
    dbconn.close();
}
