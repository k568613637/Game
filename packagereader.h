#ifndef PACKAGEREADER_H
#define PACKAGEREADER_H

#include <QObject>
#include "Public.h"
#include <QByteArray>
#include <QAbstractSocket>
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
    
};

#endif // PACKAGEREADER_H
