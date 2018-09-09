#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include "socketthread.h"
#include <QMessageBox>
#include <QFile>
#include <stdio.h>
#include "iostream"
#include <QDebug>

namespace name {

}

class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Socket(int desc,QObject *parent = 0);
    explicit Socket(QObject *parent = 0);
//    bool static  isfile;


signals:
    void  data_clientTOthread(QByteArray,int);

public slots:
    void recvdata();
    void sendata(QByteArray data,int c);
    void getIsfile(bool);

private:
    int description;

    QString fileName;
    QFile *file;
    /* 已接受数据，总数据，文件名长度 */
    qint64 gotBytes, fileBytes, nameSize;



};

#endif // SOCKET_H
