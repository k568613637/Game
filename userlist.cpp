#include "userlist.h"

UserList::UserList()
{

    for(int i=0;i<MAXCONNECTION;i++)
        users[i]=NULL;
    current=0;
}
int UserList::Insert(User *user)
{
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(users[i]==NULL)
        {
            users[i]=user;
            qDebug()<<__FUNCTION__<<user->name;
            return 1;
        }
    }
    return -1;
}

struct User * UserList::GetUser(int i)
{
    return users[i];
}

struct User * UserList::Next()
{

    for(;;)
    {
        current++;
        if(users[current-1]!=NULL)
            return users[current-1];
        if(current==MAXCONNECTION)
        {
            current=0;
            return NULL;
        }
    }
}


UserList::~UserList()
{
    for(int i;i<MAXCONNECTION;i++)
    {
        if(users[i]!=NULL)
            delete users[i];
    }
}
