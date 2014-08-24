#include "user.h"

User::User():id(-1)
{
}
User::~User()
{

}

User::User(const User &)
{

}

User::User(int _id, QString _username, QString _password)
    :id(_id), username(_username), password(_password)
{

}
