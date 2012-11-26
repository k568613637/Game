#include "serverlistener.h"

ServerListener::ServerListener(QObject *parent) :
    QObject(parent)
{
    memset(clients,0,sizeof(QTcpSocket *)*MAXCONNECTION);
    reader = new PackageReader(this);
    MainServer = new QTcpServer(this);
    if(!MainServer)
        qDebug()<<__FUNCTION__;
    if(! (MainServer->listen(QHostAddress::Any,GAMESERVERPORT)) )
        qDebug()<<__FUNCTION__;
    connect(MainServer,SIGNAL(newConnection()),this,SLOT(hasNewConn()));
    connect(this,SIGNAL(hasNewData(QAbstractSocket*)),reader,SLOT(ReadData(QAbstractSocket*)));
    //connect(MainServer,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)))
}
void ServerListener::hasNewConn()
{
    while(MainServer->hasPendingConnections())
    {
        for(int i=0;;i++)
        {
            if(i==MAXCONNECTION)
            {
                qDebug()<<"MAXCONNECTION";
                MainServer->nextPendingConnection()->close();
                break;}
            if(clients[i]==NULL)
            {
                clients[i]=MainServer->nextPendingConnection();
                connect(clients[i],SIGNAL(readyRead()),this,SLOT(hasData()));
                connect(clients[i],SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)));
                qDebug()<<__FUNCTION__<<"succeed";
                break;

            }
        }
    }
}
void ServerListener::hasData()
{
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(clients[i]!=NULL&&clients[i]->isReadable()){
            qDebug()<<__FUNCTION__;
            emit hasNewData(clients[i]);
        }
    }
}
void ServerListener::onSocketError(QAbstractSocket::SocketError s)
{
    //if(MainServer->e)
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(clients[i]&&clients[i]->error()==s)
        {
            qDebug()<<clients[i]->errorString();
            clients[i]->close();
            delete clients[i];
            clients[i]=NULL;
        }
    }
}

