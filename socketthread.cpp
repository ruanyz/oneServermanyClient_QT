#include "socketthread.h"

SocketThread::SocketThread(int desc,QObject *parent) :
    QThread(parent),description(desc)
{

}

void SocketThread::run(){

    //    qDebug()<<description;
    cSocket = new Socket(description,0);
    cSocket->setSocketDescriptor(description);

    //    connect(cSocket,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));
    connect(cSocket,SIGNAL(disconnected()),this,SLOT(disconnectfromhost()));
//    connect(cSocket,SIGNAL(error(QAbstractSocket::SocketError a)),this,SLOT(deleteClient(QAbstractSocket::SocketError a)));
    connect(this,SIGNAL(sent_thTOsocket(QByteArray,int)),cSocket,SLOT(sendata(QByteArray ,int)));
    connect(cSocket,SIGNAL( data_clientTOthread(QByteArray,int)),this,SLOT(data_thTOserver(QByteArray,int)));

    exec();

}


//void SocketThread::deleteClient(QAbstractSocket::SocketError e){

//}


void SocketThread::data_thTOserver(QByteArray data,int c){
    emit data_serverTOdia(data,c);
}


void SocketThread::readyReadSlot(){
    QByteArray data = cSocket->readAll();
    qDebug()<<data<<description;
    //emit showMSG(data,description);
}

void SocketThread::sent_th(QByteArray data,int c){
   emit sent_thTOsocket(data,c);
}

void SocketThread::disconnectfromhost(){
    qDebug()<<"hello12";
    emit ref_com_ui(description);
}
