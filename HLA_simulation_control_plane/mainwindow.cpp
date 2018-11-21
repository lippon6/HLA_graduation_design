#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(ui->initBtn, SIGNAL(clicked()), this, SLOT(serverInit()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(winMsgSend()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serverInit()
{
    if(socketServer.initSocket() == false)
    {
        QMessageBox::information(this, "QT通信网络", "服务器端监听失败");
    }
    else
    {
        connect(socketServer.myTCPServer, SIGNAL(newConnection()), this, SLOT(winNewConnect()));
        QMessageBox::information(this, "QT通信网络", "服务器端监听成功");
    }
}

void MainWindow::winNewConnect()
{
    if(socketServer.serverNewConnection() == true)
    {
        QMessageBox::information(this, "QT网络通信", "成功接收客户端连接");
        connect(socketServer.myTCPSocket, SIGNAL(readyRead()), this, SLOT(winMsgRead()));
        //connect(socketServer.myTCPSocket, SIGNAL(disconnected()), this, SLOT(serverDisConnection()));
    }
    else
    {
        QMessageBox::information(this, "QT网络通信", "未能正确获取客户端连接");
    }
}

void MainWindow::winMsgRead()
{
    socketServer.receiveData();
}

void MainWindow::winMsgSend()
{
    QString sendMsg = ui->testForSend->toPlainText();

    socketServer.sendData(sendMsg);
}
