#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "socketthread.h"
#include "widget.h"
#include "client.h"

class Widget;
class client;
class Server : public QTcpServer{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
      ~Server();
private:
    void incomingConnection(int description);

signals:
    void sent_thTOsocket(QByteArray,int);

public slots:
    void closeClient();

private :

    Widget *w;
public:
        QList<int> socketList;
};

#endif // SERVER_H
