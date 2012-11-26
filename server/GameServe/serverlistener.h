#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <QObject>
#include <QtNetwork>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include "../../Public.h"
#include "../../packagereader.h"
class ServerListener : public QObject
{
    Q_OBJECT
public:
    explicit ServerListener(QObject *parent = 0);
    
signals:
    void hasNewData(QAbstractSocket *);
    
public slots:
    void hasNewConn();
    void hasData();
    void onSocketError(QAbstractSocket::SocketError s);

private:
    QTcpServer *MainServer;
    QTcpSocket *clients[MAXCONNECTION];
    PackageReader *reader;
};

#endif // SERVERLISTENER_H
