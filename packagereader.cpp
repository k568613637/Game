#include "packagereader.h"

PackageReader::PackageReader(QObject *parent) :
    QObject(parent)
{
    data.resize(MAXBUFFSIZE);
}
void PackageReader::ReadData(QAbstractSocket *socket)
{

    data.append(socket->readAll());
    qDebug()<<__FUNCTION__<<data.data();

}
