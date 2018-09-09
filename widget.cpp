#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    count = 0;
    ui->lineEdit->setText("127.0.0.1");
    ui->lineEdit_2->setText("1234");
    server = new Server(this);
    server->listen(QHostAddress::Any,ui->lineEdit_2->text().toInt());

    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(sendDataToClient()));
}

//get transfer data
void Widget::sendDataToClient(){
    QByteArray data = ui->lineEdit_3->text().toLatin1();

    int clien = ui->comboBox->currentText().toInt();
    emit sent_diaTOthread(data,clien);
}


void Widget::setCombox(){
    ui->comboBox->addItem(QString("%1").arg(server->socketList.at(count)));
    count++;
}

void Widget::receiveMsg(QByteArray data,int c){
   QDateTime tt =  QDateTime::currentDateTime();
   QString s =  tt.toString("yyyy-mm-dd hh:MM:ss");
   ui->textBrowser->append(s+": "+QString("%1").arg(c)+"   "+data+"\n");

}

void Widget::rel_ui(int des){
    qDebug()<<des<<"11111s";
    server->socketList.removeAll(des);
    ui->comboBox->clear();
    for(int i=0;i<server->socketList.size();i++){
        ui->comboBox->addItem(QString("%1").arg(server->socketList.at(i)),i);
    }
}


Widget::~Widget()
{
    delete ui;
}
