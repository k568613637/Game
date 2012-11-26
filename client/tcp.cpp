#include "tcp.h"

Tcp::Tcp(QObject *parent) :
    QObject(parent)
{
    stream.setVersion(QDataStream::Qt_4_8);
    socket=new QTcpSocket(this);
    if(!socket)
        qDebug()<<__FUNCTION__<<"error";
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)));
}
void Tcp::ConnectTo(QHostAddress *add, quint16 port)
{
    socket->connectToHost(*add,port);

}
bool Tcp::isOpen()
{
    return socket->isOpen();
}
QTcpSocket *Tcp::GetSocket()
{
    return socket;
}
void Tcp::onSocketError(QAbstractSocket::SocketError s)
{
    qDebug()<<socket->errorString();
}
bool Tcp::login(QString &name, QString &passwd)
{
    stream.setDevice(socket);
    int resault;
    if(!isOpen())
        return 0;
    stream<<CMD_LOGIN;
    stream<<name.length();
    stream<<name;
    stream<<passwd.length();
    stream<<passwd;
    if(!socket->waitForReadyRead())
        return 0;
    stream>>resault;
    qDebug()<<__FUNCTION__<<resault;
    if(resault==FAULT)
        return 0;
    return 1;
}

Tcp::~Tcp()
{
    socket->close();
    delete socket;
}
