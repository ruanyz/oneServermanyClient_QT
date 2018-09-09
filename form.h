#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include "socket.h"


class Socket;


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
signals:
//      void  transFile(QString,bool);
   void  isFile(bool);

private:
    Ui::Form *ui;
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

#endif // FORM_H
