#include "loginwidget.h"
#include "ui_loginwidget.h"
#include"mainwindow.h"

LoginWidget::LoginWidget(QWidget *parent) :
    CustomMoveWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    /*
    //设置QSS
    QFile file(":/qss/resource/qss/default.css");
    file.open(QIODevice::ReadOnly);

    //设置样式表
    qApp->setStyleSheet(file.readAll());
    file.close();
    */
    //设置样式
    myHelper::setStyle("default");

    ui->stackedWidget->setCurrentIndex(0);

    //给lineEditUser添加图片
    ui->lineEditUser->SetIcon(QPixmap(":/resource/common/ic_user.png"));
    ui->lineEditPasswd->SetIcon(QPixmap(":/resource/common/ic_lock.png"));

    ui->labelWinTitle->setText("用户登录");
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
    ui->stackedWidget->setStartVal(0);
    ui->stackedWidget->setEndVal(180);
    ui->stackedWidget->animation(1);
}

void LoginWidget::on_btnCancel_clicked()
{
    ui->stackedWidget->setStartVal(0);
    ui->stackedWidget->setEndVal(-180);
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

//    MainWindow *mainWindow=new MainWindow;
//    mainWindow->show();

//    this->hide();   //登录窗口隐藏

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
    switch (state) 
	{
        case ConnectedHost: //连接成功
            ui->labelWinTitle->setText("已连接服务器");
        break;
    case LoginSuccess:  //用户登录成功
    {
        disconnect(m_tcpSocket, &ClientSocket::signalMessage, this, &LoginWidget::onSignalMessage);
        disconnect(m_tcpSocket, &ClientSocket::signalStatus, this, &LoginWidget::onSignalStatus);
        qDebug()<<"用户登录成功！";

        MainWindow *mainWindow=new MainWindow;
        mainWindow->SetSocket(m_tcpSocket,ui->lineEditUser->text());
        mainWindow->show();
        this->hide();   //登录窗口隐藏
    }
        break;
    case LoginPasswdError:
        qDebug()<<"用户密码错误！";
        break;
    case LoginRepeat:  //用户已在线
        qDebug()<<"用户已在线！";
        break;

    }

}


