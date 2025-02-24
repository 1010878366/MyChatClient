﻿#include "loginwidget.h"
#include "ui_loginwidget.h"
#include"mainwindow.h"

LoginWidget::LoginWidget(QWidget *parent) :
    CustomMoveWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    //设置QSS
    QFile file(":/qss/resource/qss/default.css");
    file.open(QIODevice::ReadOnly);

    //设置样式表
    qApp->setStyleSheet(file.readAll());
    file.close();

    ui->stackedWidget->setCurrentIndex(0);

    //给lineEditUser添加图片
    ui->lineEditUser->SetIcon(QPixmap(":/resource/common/ic_user.png"));
    ui->lineEditPasswd->SetIcon(QPixmap(":/resource/common/ic_lock.png"));

    m_tcpSocket=new ClientSocket;
    connect(m_tcpSocket,&ClientSocket::signalMessage,this,&LoginWidget::onSignalMessage);
    connect(m_tcpSocket,&ClientSocket::signalStatus,this,&LoginWidget::onSignalStatus);

    m_tcpSocket->CheckConnected();  //检查是否连接到服务器
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_btnWinMenu_clicked()
{
    ui->stackedWidget->setstartVal(0);
    ui->stackedWidget->setendVal(180);
    ui->stackedWidget->animation(1);
}

void LoginWidget::on_btnCancel_clicked()
{
    ui->stackedWidget->setstartVal(0);
    ui->stackedWidget->setendVal(-180);
    ui->stackedWidget->animation(0);
}

void LoginWidget::on_btnLogin_clicked()
{
    QString username = ui->lineEditUser->text();
    QString passwd = ui->lineEditPasswd->text();

    //构建JSON对象
    QJsonObject json;
    json.insert("name",username);
    json.insert("passwd",passwd);

    m_tcpSocket->SltSendMessage(0x11,json);
    /*
    MainWindow *mainWindow=new MainWindow;
    mainWindow->show();

    this->hide();   //登录窗口隐藏
    */
}

void LoginWidget::on_btnWinClose_clicked()
{
    close();
}

void LoginWidget::onSignalMessage(const quint8 &type,const QJsonValue &dataVal)
{

}

void LoginWidget::onSignalStatus(const quint8 &state)
{
    switch(state)
    {
    case 0x01:
        ui->labelWinTitle->setText("已连接服务器");
        break;
    case 0x03:  //用户登录成功
    {
        qDebug()<<"用户登录成功！";

        MainWindow *mainWindow=new MainWindow;
        mainWindow->show();
        this->hide();   //登录窗口隐藏
    }
        break;
    case 0x04:  //用户未注册
        qDebug()<<"用户未注册！";
        break;
    case 0x13:  //用户已在线
        qDebug()<<"用户已在线！";
        break;

    }

}


