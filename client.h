#ifndef CLIENT_H
#define CLIENT_H

//#include <QDialog>
#include <QTcpSocket>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include "socket.h"
#include <QWidget>

class Socket;

namespace Ui {
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = 0);
    ~client();

 signals:
//      void  transFile(QString,bool);
    void  isFile(bool);

private:
    Ui::client *ui;
    QTcpSocket *cSocket;
    void closeEvent(QCloseEvent *e);
    bool transferfile;

    QFile *file;
    QString fileName;
    /* 总数据大小，已发送数据大小，剩余数据大小，每次发送数据块大小 */
    qint64 fileBytes, sentBytes, restBytes, loadBytes;

    bool  isfile;
    Socket *a;



public slots:
    void getData();
    void senData();
    void deleteLater();
    void selectFile();
    void continue_transfer(qint64 sentSize);

//    void teans(QString,bool,bool);
//    void uploadFile();
};

#endif // CLIENT_H
