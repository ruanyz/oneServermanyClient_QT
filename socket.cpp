#include "socket.h"

bool isfile;

Socket::Socket(int desc,QObject *parent) :
    QTcpSocket(parent),description(desc)
{
    fileBytes = gotBytes = nameSize = 0;
    isfile = false;
    connect(this,SIGNAL(readyRead()),this,SLOT(recvdata()));
}


Socket::Socket(QObject *parent):QTcpSocket(parent){


}

//  dialog  give data  to client
void Socket::sendata(QByteArray data,int c){
    if(data.isEmpty()){
        QMessageBox::warning(NULL,tr("warming"),tr("the mes is empty"));
        return;
    }else{
        if(c==description)
             write(data);
    }
}



void Socket::getIsfile(bool a){
    isfile = a;
}



//client give data to dialog


void Socket::recvdata(){
    qDebug()<<isfile;

    if(isfile == true){
        QDataStream in(this);
        in.setVersion(QDataStream::Qt_5_2);

        /* 首部未接收/未接收完 */
        if(gotBytes <= 2 * sizeof(qint64))
        {
            if(!nameSize) // 前两个长度字段未接收
            {
                if(this->bytesAvailable() >= 2 * sizeof(qint64))
                {
                    in >> fileBytes >> nameSize;
                    gotBytes += 2 * sizeof(qint64);

                    //                ui->recvProg->setMaximum(fileBytes);
                    //                ui->recvProg->setValue(gotBytes);
                }
                else // 数据不足，等下次
                    return;
            }
            else if(this->bytesAvailable() >= nameSize)
            {
                in >> fileName;
                gotBytes += nameSize;
                //            ui->recvProg->setValue(gotBytes);
                std::cout << "--- File Name: "
                          << fileName.toStdString() << std::endl;
            }
            else // 数据不足文件名长度，等下次
                return;
        }

        /* 已读文件名、文件未打开 -> 尝试打开文件 */
        if(!fileName.isEmpty() && file == Q_NULLPTR)
        {
            file = new QFile(fileName);
            if(!file->open(QIODevice::ReadWrite)) // 打开失败
            {
                std::cerr << "*** File Open Failed ***" << std::endl;
                delete file;
                file = Q_NULLPTR;
                return;
            }

        }
        if(file == Q_NULLPTR) // 文件未打开，不能进行后续操作
            return;

        if(gotBytes < fileBytes) // 文件未接收完
        {
            gotBytes += this->bytesAvailable();
            qDebug()<<gotBytes<<fileBytes;
            //        ui->recvProg->setValue(gotBytes);
            file->write(this->readAll());
        }
        if(gotBytes == fileBytes) // 文件接收完
        {
            qDebug()<<"wan cheng";
//            this->close(); // 关socket
            file->close();
//            delete file;
            gotBytes=0;
            fileName.clear();

        }
    }else if(isfile == false){
        QByteArray data = readAll();
        emit data_clientTOthread(data,this->description);
    }
}
