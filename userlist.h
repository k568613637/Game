#ifndef USERLIST_H
#define USERLIST_H

#include <QObject>
#include <QtNetwork>
#include "Public.h"
struct User
{
    QString name;
    QHostAddress add;
    quint16 port;
    bool online;

};

class UserList
{
public:
    UserList();
    ~UserList();
    int Insert(User *user);
    struct User *GetUser(int i);
    struct User *Next();
private:
    struct User *users[MAXCONNECTION];
    int current;
    
};

#endif // USERLIST_H
