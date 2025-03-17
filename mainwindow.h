#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"customwidget.h"
#include<QButtonGroup>
#include<QSystemTrayIcon>
#include"chatstackedwidget.h"
#include "clientsocket.h"
#include<QMenu>
#include"qqcell.h"
#include"myapp.h"
#include "global.h"
#include "databasemagr.h"
#include "chatwindow.h"
#include"unit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QQCell;

class MainWindow : public CustomMoveWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SetSocket(ClientSocket *tcpSocket, const QString &name);

private slots:
    void SltMainPageChanged(int index);

    //托盘菜单处理
    void SltTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
    void SltTrayIconMenuClicked(QAction *action);

    // 程序退出处理
    void SltQuitApp();

    //好友点击
    void SltFriendsClicked(QQCell*);
    //群组点击
    void SltGroupsClicked(QQCell*);

    void SltFriendChatWindowClose();

    // 右键菜单
    void onAddFriendMenuDidSelected(QAction *action);
    void onGroupPopMenuDidSelected(QAction *action);
    void onChildPopMenuDidSelected(QAction *action);

    //QTcpSocket信号要关联的槽函数
    void SltTcpReply(const quint8 &type, const QJsonValue &dataVal);
    void SltTcpStatus(const quint8 &state);

    void on_btnWinMin_clicked();
    void on_btnWinClose_clicked();

private:
    Ui::MainWindow *ui;

    ClientSocket *m_tcpSocket;

    QButtonGroup *m_btnGroup;
    QSystemTrayIcon *systemTrayIcon;

    // 聊天窗管理
    QList<ChatWindow *> m_chatFriendWindows;
    QList<ChatWindow *> m_chatGroupWindows;

    void InitQQListMenu();
    void InitSysTrayIcon();

    void SltReadMessages(const QJsonValue &json, const int &id);

    void PraseAddFriendReply(const QJsonValue &dataVal);
    void PraseAddFriendRequistReply(const QJsonValue &dataVal);


    void ParseAddGroupReply(const QJsonValue &dataVal);
    void ParseAddGroupRequest(const QJsonValue &dataVal);
    void ParseCreateGroupReply(const QJsonValue &dataVal);
    void ParseGetGroupFriendsReply(const QJsonValue &dataVal);
    void ParseRefreshGroupFriendsReply(const QJsonValue &dataVal);
    void ParseFriendMessageReply(const QJsonValue &dataVal);
    void ParseFaceMessageReply(const QJsonValue &dataVal);
    void ParseGroupMessageReply(const QJsonValue &dataVal);

    void AddMyGroups(const QJsonValue &dataVal);


    QString GetHeadPixmap(const QString &name) const;

};

#endif // MAINWINDOW_H
