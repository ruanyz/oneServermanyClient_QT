#include "server.h"



int  desc;
Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    w =dynamic_cast<Widget*>(parent);

}

Server::~Server(){


}

void Server::incomingConnection(int description){

        desc = description;

    socketList.append(description);
    SocketThread *th = new SocketThread(description,0);

    //set data on combox
    connect(th,SIGNAL(started()),w,SLOT(setCombox()));
    //reveive  transfer data
    connect(w,SIGNAL(sent_diaTOthread(QByteArray,int)),th,SLOT(sent_th(QByteArray,int)));
    connect(th,SIGNAL(data_serverTOdia(QByteArray,int)),w,SLOT(receiveMsg(QByteArray,int)));

    //client disconnect   close client

    connect(th,SIGNAL(ref_com_ui(int)),w,SLOT(rel_ui(int)));
    connect(th,SIGNAL(finished()),this,SLOT(deleteLater()));
    th->start();
}


void Server::closeClient(){



}

