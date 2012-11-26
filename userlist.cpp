#include "userlist.h"

UserList::UserList()
{

    for(int i=0;i<MAXCONNECTION;i++)
        users[i]=NULL;
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

UserList::~UserList()
{
    for(int i;i<MAXCONNECTION;i++)
    {
        if(users[i]!=NULL)
            delete users[i];
    }
}
