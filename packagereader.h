#ifndef PACKAGEREADER_H
#define PACKAGEREADER_H

#include <QObject>
#include "Public.h"
#include "userlist.h"
#include <QDataStream>
#include <QAbstractSocket>
class PackageReader : public QObject
{
    Q_OBJECT
public:
    explicit PackageReader(QObject *parent = 0);
    bool Login();
    
signals:
    
public slots:
    void ReadData(QAbstractSocket *socket,UserList *);

private:
    QDataStream stream;
    
};

#endif // PACKAGEREADER_H
