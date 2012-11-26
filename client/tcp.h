#ifndef TCP_H
#define TCP_H
#include <QMainWindow>
#include <QObject>
#include <QtNetwork>
#include <QDataStream>
#include "../Public.h"
class Tcp : public QObject
{
    Q_OBJECT
public:
    explicit Tcp(QObject *parent = 0);
    void ConnectTo(QHostAddress *add,quint16 port);
    bool isOpen();
    bool login(QString &name,QString &passwd);
    QTcpSocket *GetSocket();
    ~Tcp();
signals:
    
public slots:
    void onSocketError(QAbstractSocket::SocketError s);
private:
    QTcpSocket *socket;
    QDataStream stream;
    
};

#endif // TCP_H
