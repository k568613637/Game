#ifndef PACKAGEREADER_H
#define PACKAGEREADER_H

#include <QObject>
#include "Public.h"
#include <QByteArray>
#include <QAbstractSocket>
#include <QDataStream>
class PackageReader : public QObject
{
    Q_OBJECT
public:
    explicit PackageReader(QObject *parent = 0);
    
signals:
    
public slots:
    void ReadData(QAbstractSocket *socket);

private:
    QByteArray data;
    QDataStream stream;
    
};

#endif // PACKAGEREADER_H
