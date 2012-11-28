#include "packagereader.h"

PackageReader::PackageReader(QObject *parent) :
    QObject(parent)
{

}
void PackageReader::ReadData(QAbstractSocket *socket, UserList *list)
{
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(socket);
    l=list;
    s=socket;
    int cmd;
    socketStream>>cmd;
    QString data1,data2;
    switch (cmd)
    {
    case CMD_LOGIN:
        if(!Login())
            qDebug()<<"login fault";
        SendList();
        break;
    case CMD_GET_LIST:
        qDebug()<<SendList();

    default:
        break;
    }
}

bool PackageReader::Login()
{
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(s);
    struct User *user;
    int nameLen,passwdLen;
    QString name,passwd;
    socketStream>>nameLen;
    if(nameLen<0||nameLen>MAX_STR_LEN)
    {
        socketStream<<FAULT;
        return 0;
    }
    name.resize(nameLen);
    socketStream>>name;
    socketStream>>passwdLen;
    if(passwdLen<0||passwdLen>MAX_STR_LEN)
    {
        socketStream<<FAULT;
        return 0;
    }
    passwd.resize(passwdLen);
    socketStream>>passwd;
    qDebug()<<"user name"<<name<<"passwd:"<<passwd;
    /*bala
     *bala
     *bala
     */
    user = new struct User;
    user->name=name;
    user->add=s->peerAddress();
    user->online=1;
    user->port=s->peerPort();
    qDebug()<<user->name;
    if(-1==l->Insert(user))
    {
        delete user;
        socketStream<<FAULT;
        return 0;
    }
    socketStream<<SUCCEED;
    return 1;

}
int PackageReader::SendList()
{
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(s);
    qDebug()<<__FUNCTION__;
    int count=0;
    struct User *user;

    QByteArray data;
    for(;;)
    {

        QDataStream stream(&data,QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_4_8);
        user=l->Next();
        if(user==NULL)
        {
            qDebug()<<__FUNCTION__<<"end";
            return count;

        }
        qDebug()<<user->name;
        stream<<VAL_USER
              <<user->name.length()
              <<user->name
              <<user->add.toIPv4Address()
              <<user->port
              <<user->online;
        socketStream.writeRawData(data.data(),data.size());
        count++;
        qDebug()<<__FUNCTION__<<"count"<<count;
   }


}
