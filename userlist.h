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
private:
    struct User *users[MAXCONNECTION];
    
};

#endif // USERLIST_H
