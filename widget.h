#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QTcpServer>
#include "server.h"
#include <QDebug>
#include <QDateTime>

namespace Ui {
class Widget;
}

class Server;

class Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
      Server *server;
      int count;

private:
    Ui::Widget *ui;
//  QTcpServer *server;

public slots:
    void sendDataToClient();
    void setCombox();
    void receiveMsg(QByteArray data,int);
    void rel_ui(int);


signals:
    void sendData();
    void sent_diaTOthread(QByteArray,int);

};

#endif // WIDGET_H
