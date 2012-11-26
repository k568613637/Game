#include "packagereader.h"

PackageReader::PackageReader(QObject *parent) :
    QObject(parent)
{

}
void PackageReader::ReadData(QAbstractSocket *socket)//可能需要优化
{

    int a;
    char str;
    stream.setDevice(socket);
    //data=(socket->readAll());
    //qDebug()<<__FUNCTION__<<data.data();
    stream>>a;
    qDebug()<<a;


}
