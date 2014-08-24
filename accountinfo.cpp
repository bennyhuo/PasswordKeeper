#include "accountinfo.h"

AccountInfo::AccountInfo():id(-1)
{

}

AccountInfo::~AccountInfo()
{

}

AccountInfo::AccountInfo(int _id, QString _username, QString _password, QString _websitename)
    :id(_id), username(_username),password(_password), websitename(_websitename)
{
}

AccountInfo::AccountInfo(int _id, QString _username, QString _password, QString _websitename, int _userid)
    :id(_id), userid(_userid), username(_username),password(_password), websitename(_websitename)
{
}

AccountInfo &AccountInfo::operator =(const AccountInfo & account)
{
    id = account.id;
    username = account.username;
    password = account.password;
    userid = account.userid;
    websitename = account.websitename;
    return *this;
}

AccountInfo::AccountInfo(const AccountInfo &account)
{
    id = account.id;
    username = account.username;
    password = account.password;
    userid = account.userid;
    websitename = account.websitename;
}

void AccountInfo::changeAccount(int index, QString content)
{
    switch (index) {
    case 0:
        username = content;
        break;
    case 1:
        password = content;
        break;
    case 2:
        websitename = content;
        break;
    default:
        break;
    }
}
