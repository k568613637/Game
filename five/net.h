#ifndef NET_H
#define NET_H

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QErrorMessage>
#include <QMessageBox>
#define PORT 8910
#define SERVER 1
#define CLIENT 0
struct Connection {
    quint16 port;
    QHostAddress add;
};

class Net :public QObject
{
    Q_OBJECT
public:
    Net(int type, QString ip);
    void senddata(QString str);
    bool IsListening();
    void listen();
    bool connectto(QString add);
    bool beServer();
public slots:
    void readdata();
    void newTcpConnect();
    void onSocketError(QAbstractSocket::SocketError s);
signals:
    void has_data(QString *);
    void has_err(QString );
    void startGame();
private:
    /*QUdpSocket *udp;
    struct Connection conn;*/
    QTcpServer *server;
    QTcpSocket *socket;
    QString data;
};

#endif // NET_H
