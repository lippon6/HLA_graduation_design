#include "socket_config.h"
#include "data_parse.h"
#include "QMessageBox"


#define PORT_NUM  5550



//socket服务器初始化
bool SocketConfig::initSocket()
{
    myTCPServer = new QTcpServer();
    int port = PORT_NUM;
    if(!myTCPServer->listen(QHostAddress::Any, port))
    {
        //QMessageBox::information(this, "QT通信网络", "服务器端监听失败");
        return false;
    }
    else
    {
        return true;
        //QMessageBox::information(this, "QT通信网络", "服务器端监听成功");
    }
}

//建立连接
bool SocketConfig::serverNewConnection()
{
    myTCPSocket = myTCPServer->nextPendingConnection();

    if(!myTCPSocket)
    {
        return false;
    }
    else
    {

        return true;
    }
}

//服务器接收数据
void SocketConfig::receiveData()
{
    char buffer[1024] = {0};
    myTCPSocket->read(buffer,1024);
    if(strlen(buffer) > 0)
    {
        QMessageBox::information(this, "QT网络通信", buffer);
        for(int i = 0; i < strlen(buffer); i++)
        {
            if(i < BUFFER_VAL_MAX)
            {
                parser.frameBuffers[parser.addIdx].buff[i] = buffer[i];
            }
            else
            {
                break;
            }
        }

        if(parser.addIdx < FRAME_NUM_MAX - 1)
        {
            parser.addIdx++;
        }
        else
        {
             parser.addIdx = 0;
        }
    }
    else
    {

    }
}

void SocketConfig::sendData(QString sendData)
{
    char sendMsgChar[1024] = {0};

    strcpy_s(sendMsgChar, sendData.toStdString().c_str());
    // QMessageBox::information(this, "QT通信网络", "正在发送");
    if(myTCPSocket->isValid())
    {
        int sendRe = myTCPSocket->write(sendMsgChar, strlen(sendMsgChar));
        if(-1 == sendRe)
        {
            QMessageBox::information(this, "QT网络通信", "服务端发送数据失败！");
        }
    }
    else
    {
        QMessageBox::information(this, "QT网络通信", "套接字无效！");
    }
}
