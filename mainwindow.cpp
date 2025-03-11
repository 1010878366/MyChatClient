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

    ui->GCStackedWidget->setCurrentIndex(0);

    InitQQListMenu();
    InitSysTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
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

/**
 * @brief MainWindow::InitQQListMenu
 * 添加好友列表菜单
 */
void MainWindow::InitQQListMenu()
{
    //设置菜单
    //设置组菜单
    QMenu *addFriend = new QMenu(this);
    addFriend->addAction(tr("添加好友"));
    addFriend->addAction(tr("刷新"));
    addFriend->addSeparator();
    addFriend->addAction(tr("删除该组"));
    connect(addFriend, SIGNAL(triggered(QAction*)), this, SLOT(onAddFriendMenuDidSelected(QAction*)));
    ui->frindListWidget_2->setGroupPopMenu(addFriend);

    // 设置子菜单
    QMenu *childMenu = new QMenu(this);
    childMenu->addAction(tr("发送即时消息"));
    childMenu->addSeparator();
    childMenu->addAction("移动至黑名单");
    childMenu->addAction("删除联系人");

    QMenu *groupListMenu = new QMenu(tr("移动联系人至"));
    childMenu->addMenu(groupListMenu);

    // childMenu->addAction(tr("创建讨论组"));
    connect(childMenu, SIGNAL(triggered(QAction*)), this, SLOT(onChildPopMenuDidSelected(QAction*)));
    ui->frindListWidget_2->setChildPopMenu(childMenu);

    //添加默认项
    //好友列表
    QQCell *myFriend = new QQCell;
    myFriend->groupName = QString(tr("我的好友"));
    myFriend->isOpen = false;
    myFriend->type = QQCellType_Group;
    myFriend->name = QString(tr("我的好友"));
    myFriend->subTitle = QString("(0/0)");
    ui->frindListWidget_2->insertQQCell(myFriend);

    QQCell *blacklist = new QQCell;
    blacklist->groupName = QString(tr("黑名单"));
    blacklist->isOpen = false;
    blacklist->type = QQCellType_Group;
    blacklist->name = QString(tr("黑名单"));
    blacklist->subTitle = QString("(0/0)");
    ui->frindListWidget_2->insertQQCell(blacklist);

    connect(ui->frindListWidget_2, SIGNAL(onChildDidDoubleClicked(QQCell*)), this, SLOT(SltFriendsClicked(QQCell*)));

    //组列表
    QMenu *myGroupMenu = new QMenu(this);
    myGroupMenu->addAction(tr("创建讨论组"));
    myGroupMenu->addAction(tr("加入讨论组"));
    myGroupMenu->addAction(tr("删除该组"));
    myGroupMenu->addSeparator();
    connect(myGroupMenu, SIGNAL(triggered(QAction*)), this, SLOT(onGroupPopMenuDidSelected(QAction*)));
    ui->groupListWidget_2->setGroupPopMenu(myGroupMenu);
    //设置子菜单
    QMenu *groupChildMen = new QMenu(this);
    groupChildMen->addAction(tr("发送即时消息"));
    ui->groupListWidget_2->setChildPopMenu(groupChildMen);

    //添加默认项
    QQCell *groupCell = new QQCell;
    groupCell->groupName = QString(tr("我的群组"));
    groupCell->isOpen = false;
    groupCell->type = QQCellType_GroupEx;
    groupCell->name = QString(tr("讨论组"));
    groupCell->subTitle = QString("(0/0)");
    ui->groupListWidget_2->insertQQCell(groupCell);

    connect(ui->groupListWidget_2, SIGNAL(onChildDidDoubleClicked(QQCell*)), this, SLOT(SltGroupsClicked(QQCell*)));
}

void MainWindow::SetSocket(ClientSocket *tcpSocket, const QString &name)
{
    if (tcpSocket != NULL) {
        m_tcpSocket = tcpSocket;
        connect(m_tcpSocket, &ClientSocket::signalMessage, this, &MainWindow::SltTcpReply);
        connect(m_tcpSocket, &ClientSocket::signalStatus, this, &MainWindow::SltTcpStatus);

        ui->labelUser->setText(name);
    }
}

void MainWindow::SltTcpReply(const quint8 &type, const QJsonValue &dataVal)
{
    qDebug() << "dataVal:" << dataVal;
    switch (type) {
    case AddFriend: //服务器返回 主动添加好友的用户 消息
        PraseAddFriendReply(dataVal);
        break;
    case AddFriendRequist: //服务器通知被添加的好友
        //{"head":"2_head_64.png","id":2,"msg":"附加消息： 你好！","name":"milo"}
        PraseAddFriendRequistReply(dataVal);
        break;
    default:
        break;
    }
}

//服务器返回 主动添加好友的用户 消息
void MainWindow::PraseAddFriendReply(const QJsonValue &dataVal)
{
    if (dataVal.isObject()) {
        QJsonObject dataJson = dataVal.toObject();
        int id = dataJson.value("id").toInt();
        QString name = dataJson.value("name").toString();
        QString head = dataJson.value("head").toString();
        int status = dataJson.value("status").toInt();

        QQCell *cell = new QQCell;
        cell->groupName = QString("我的好友");
        cell->iconPath =  QString(":/resource/head/%1").arg(head);
        cell->type = QQCellType_Child;
        cell->name = name;
        cell->subTitle = QString("当前用户状态: %1 ").arg(OnLine == status ? QString("在线") : QString("离线"));
        cell->id = id;
        cell->status = status;

        ui->frindListWidget_2->insertQQCell(cell);
    }
}

//服务器通知被添加的好友
void MainWindow::PraseAddFriendRequistReply(const QJsonValue &dataVal)
{
    if (dataVal.isObject()) {
        QJsonObject dataJson = dataVal.toObject();
        int id = dataJson.value("id").toInt();
        QString name = dataJson.value("name").toString();
        QString head = dataJson.value("head").toString();
        QString msg = dataJson.value("msg").toString();


        if (!DataBaseMagr::Instance()->isMyFriend(MyApp::m_nId, name)) {
            QQCell *cell = new QQCell;
            cell->groupName = QString("我的好友");
            cell->iconPath =  QString(":/resource/head/%1").arg(head);
            cell->type = QQCellType_Child;
            cell->name = name;
            cell->subTitle = QString("当前用户状态: 在线");
            cell->id = id;
            cell->status = OnLine;

            ui->frindListWidget_2->insertQQCell(cell);

            qDebug() << "MyApp::m_nId:"<<MyApp::m_nId <<" 添加好友, 好友id:" << id;

            //更新数据库
            DataBaseMagr::Instance()->AddFriend(cell->id, MyApp::m_nId, name);
        }

    }
}

void MainWindow::SltTcpStatus(const quint8 &state)
{
}

/**
 * @brief MainWindow::SltTrayIcoClicked
 * 托盘菜单
 * @param reason
 */
void MainWindow::SltTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::DoubleClick:
        {
            if (!this->isVisible()) {
                this->show();
            }
        }
        break;
    default:
        break;
    }
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

/**
 * @brief MainWindow::onAddFriendMenuDidSelected
 * 添加好友
 * @param action
 */
void MainWindow::onAddFriendMenuDidSelected(QAction *action)
{
    if (!action->text().compare(tr("添加好友")))
    {
        QString text = CInputDialog::GetInputText(this, "milo");

        if (!text.isEmpty()) {
            // 首先判断该用户是否已经是我的好友了
            if (DataBaseMagr::Instance()->isMyFriend(MyApp::m_nId, text)) {
                CMessageBox::Infomation(this, "该用户已经是你的好友了！");
                return;
            }

            // 构建 Json 对象
            QJsonObject json;
            json.insert("id", m_tcpSocket->GetUserId());
            json.insert("name", text);

            m_tcpSocket->SltSendMessage(AddFriend, json);
        }
    }
    else if (!action->text().compare(tr("刷新")))
    {
        // 上线的时候获取当前好友的状态
        QJsonArray friendArr = DataBaseMagr::Instance()->GetMyFriend(MyApp::m_nId);

        // 组织Jsonarror
        m_tcpSocket->SltSendMessage(RefreshFriends, friendArr);
    }
    else if (!action->text().compare(tr("删除该组")))
    {
        qDebug() << "delete group";
    }
}

void MainWindow::onGroupPopMenuDidSelected(QAction *action)
{
    if (!action->text().compare(tr("创建讨论组")))
    {
        QString text = CInputDialog::GetInputText(this, "我的朋友们");
        if (!text.isEmpty()) {
            // 构建 Json 对象
            QJsonObject json;
            json.insert("id", m_tcpSocket->GetUserId());
            json.insert("name", text);

            m_tcpSocket->SltSendMessage(CreateGroup, json);
        }
    }
    else if (!action->text().compare(tr("加入讨论组")))
    {
        QString text = CInputDialog::GetInputText(this, "我的朋友们");
        if (!text.isEmpty()) {
            // 首先判断是否已经添加该群组了
            // 这里暂时保留注释代码块，可根据实际需求决定是否启用
            // if (DataBaseMagr::Instance()->isInGroup(text)) {
            //     CMessageBox::Infomation(this, "你已经添加该群组了！");
            //     return;
            // }

            // 构建 Json 对象
            QJsonObject json;
            json.insert("id", MyApp::m_nId);
            json.insert("name", text);

            m_tcpSocket->SltSendMessage(AddGroup, json);
        }
    }
    // else if (!action->text().compare(tr("删除该组")))
    // {
    //     qDebug() << "delete group";
    // }
}

void MainWindow::onChildPopMenuDidSelected(QAction *action)
{
    QQCell *cell = ui->frindListWidget_2->GetRightClickedCell();
    if (NULL == cell) return;

    if (!action->text().compare(tr("发送即时消息")))
    {
        qDebug() << "send message" << cell->name;
        // 打开对话框
        //SltFriendsClicked(cell);
    }
    else if (!action->text().compare(tr("移动至黑名单")))
    {
        qDebug() << "balck friend list" << cell->name;
    }
    else if (!action->text().compare(tr("删除联系人")))
    {
        qDebug() << "delete my friend" << cell->name;
        ui->frindListWidget_2->removeQQCell(cell);
        // 更新数据库
        //bool bOk = DataBaseMagr::Instance()->DeleteMyFriend(cell->id, MyApp::m_nId);
        //CMessageBox::Infomation(this, bOk ? tr("用户删除成功！") : tr("用户删除失败！"));
    }
}

void MainWindow::on_btnWinMin_clicked()
{
    this->hide();
}

void MainWindow::on_btnWinClose_clicked()
{
    this->close();
}
