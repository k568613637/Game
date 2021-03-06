#include "serverlistener.h"

ServerListener::ServerListener(QObject *parent) :
    QObject(parent)
{
    memset(clients,0,sizeof(QTcpSocket *)*MAXCONNECTION);
    reader = new PackageReader(this);
    MainServer = new QTcpServer(this);
    list = new UserList();
    if(!MainServer)
        qDebug()<<__FUNCTION__;
    if(! (MainServer->listen(QHostAddress::Any,GAMESERVERPORT)) )
        qDebug()<<__FUNCTION__;
    connect(MainServer,SIGNAL(newConnection()),this,SLOT(hasNewConn()));
    connect(this,SIGNAL(hasNewData(QAbstractSocket*,UserList *)),reader,SLOT(ReadData(QAbstractSocket*,UserList *)));
}
void ServerListener::hasNewConn()
{
    while(MainServer->hasPendingConnections())
    {
        for(int i=0;;i++)
        {
            if(i==MAXCONNECTION)//连接队列已满
            {
                qDebug()<<"MAXCONNECTION";
                MainServer->nextPendingConnection()->close();
                break;
            }
            if(clients[i]==NULL)//添加连接
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
        if(clients[i]!=NULL&&clients[i]->isReadable())
        {
            qDebug()<<__FUNCTION__;
            emit hasNewData(clients[i],list);    //发送信号给数据包解析类
        }
    }
}
void ServerListener::onSocketError(QAbstractSocket::SocketError s)
{
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(clients[i]&&clients[i]->error()==s)
        {
            qDebug()<<clients[i]->errorString();
            list->Del(clients[i]);
            clients[i]->close();
            clients[i]->deleteLater();
            clients[i]=NULL;                      //关闭并清除错误的套结字
        }
    }
}

