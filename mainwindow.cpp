#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : CustomMoveWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->addButton(ui->btnFrind,0);
    m_btnGroup->addButton(ui->btnGroup,1);
    m_btnGroup->addButton(ui->btnConversation,2);
    m_btnGroup->addButton(ui->btnApplay,3);

    //connect(m_btnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &MainWindow::SltMainPageChanged);
    connect(m_btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(SltMainPageChanged(int)));

    InitSysTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnWinClose_clicked()
{
    this->hide();
}

void MainWindow::SltMainPageChanged(int index)
{
    //切换面板
    static int s_nIndex = 0;    //记录当前选中的页的下标
    if(s_nIndex == index)
    {
        return;
    }

    ui->GCStackedWidget->setLength(ui->GCStackedWidget->width(),
        index > s_nIndex ? ChatStackedWidget::LeftToRight:ChatStackedWidget::RightToLeft);
    ui->GCStackedWidget->start(index);
    s_nIndex = index;
}

void MainWindow::InitSysTrayIcon()
{
    //托盘菜单
    systemTrayIcon = new QSystemTrayIcon(this);
    systemTrayIcon->setIcon(QIcon(":/resource/background/app.png"));

    QMenu *m_trayMenu = new QMenu(this);
    m_trayMenu->addAction("我在线上");
    m_trayMenu->addAction("离线");
    m_trayMenu->addSeparator();
    m_trayMenu->addAction("显示主面板");
    m_trayMenu->addSeparator();
    m_trayMenu->addAction("退出");

    systemTrayIcon->setContextMenu(m_trayMenu);
    systemTrayIcon->show();

    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(SltTrayIcoClicked(QSystemTrayIcon::ActivationReason)));
    connect(m_trayMenu, SIGNAL(triggered(QAction*)), this, SLOT(SltTrayIconMenuClicked(QAction*)));

}

void MainWindow::SltTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::DoubleClick:
        if(!this->isVisible())
        {
            this->show();
        }
        break;
    default:
        break;
    }

}

void MainWindow::SetSocket(ClientSocket *tcpSocket, const QString &name)
{
    if (tcpSocket != NULL) {
        m_tcpSocket = tcpSocket;

        connect(m_tcpSocket, &ClientSocket::signalMessage, this, &MainWindow::SltTcpReply);
        connect(m_tcpSocket, &ClientSocket::signalStatus, this, &MainWindow::SltTcpStatus);
    }
}

void MainWindow::SltTcpReply(const quint8 &type,const QJsonValue &dataVal)
{

}

void MainWindow::SltTcpStatus(const quint8 &state)
{

}

// 托盘菜单
void MainWindow::SltTrayIconMenuClicked(QAction *action)
{
    if ("退出" == action->text()) {
        this->hide();
        QTimer::singleShot(500, this, SLOT(SltQuitApp()));
    }
    else if ("显示主面板" == action->text()) {
        this->show();
    }
    else if (!QString::compare("我在线上", action->text()))
    {
        m_tcpSocket->CheckConnected();
    }
    else if (!QString::compare("离线", action->text()))
    {
        m_tcpSocket->CloseConnected();
    }
}

/**
 * @brief MainWindow::SltQuitApp
 * 程序退出处理
 */
void MainWindow::SltQuitApp()
{
    delete ui;
    qApp->quit();
}

void MainWindow::on_btnWinMin_clicked()
{
    this->hide();
}


