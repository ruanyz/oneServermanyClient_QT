#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <socket.h>

class Socket;

class SocketThread : public QThread
{
    Q_OBJECT
public:
    explicit SocketThread(int desc,QObject *parent = 0);
    void run();

signals:

    void sent_thTOsocket(QByteArray,int);
    void data_serverTOdia(QByteArray,int);
    void ref_com_ui(int);

public slots:
    void readyReadSlot();
    void sent_th(QByteArray data,int c);
    void data_thTOserver(QByteArray data,int);
    void disconnectfromhost();
//    void deleteClient(QAbstractSocket::SocketError a);


private:
    Socket *cSocket;
    int description;

};

#endif // SOCKETTHREAD_H
