#include "packagereader.h"

PackageReader::PackageReader(QObject *parent) :
    QObject(parent)
{
    stream.setVersion(QDataStream::Qt_4_8);
}
void PackageReader::ReadData(QAbstractSocket *socket, UserList *list)
{
    stream.setDevice(socket);
    int cmd;
    int length1,length2;
    struct User *user;
    stream>>cmd;
    QString data1,data2;
    switch (cmd)
    {
    case CMD_LOGIN:
        stream>>length1;

        if(length1<0||length1>MAX_STR_LEN)
            goto Fault;
        data1.resize(length1);
        stream>>data1;
        stream>>length2;
        if(length2<0||length2>MAX_STR_LEN)
            goto Fault;
        data2.resize(length2);
        stream>>data2;
        qDebug()<<data1<<data2;
        /*bala
         *bala
         *bala
         */
        user = new struct User;
        user->name=data1;
        user->add=socket->peerAddress();
        user->online=1;
        user->port=socket->peerPort();
        qDebug()<<user->name;
        if(-1==list->Insert(user))
        {
            delete user;
            goto Fault;
        }
        stream<<SUCCEED;
        return ;
    default:
        goto Fault;
    }
Fault:
    stream<<FAULT;
}
