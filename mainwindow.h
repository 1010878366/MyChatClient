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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public CustomMoveWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetSocket(ClientSocket *tcpSocket, const QString &name);

private slots:
    void on_btnWinClose_clicked();

    void SltMainPageChanged(int index);

    //托盘菜单处理
    void SltTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
    void SltTrayIconMenuClicked(QAction *action);

    //程序退出处理
    void SltQuitApp();

    //QTcpSocket信号要关联的槽函数
    void SltTcpReply(const quint8 &type, const QJsonValue &dataVal);
    void SltTcpStatus(const quint8 &state);

    void on_btnWinMin_clicked();

    // 右键菜单
    void onAddFriendMenuDidSelected(QAction *action);
    void onGroupPopMenuDidSelected(QAction *action);
    void onChildPopMenuDidSelected(QAction *action);

    // 好友列表点击
    void SltFriendsClicked(QQCell *cell);
    // 群组列表点击
    void SltGroupsClicked(QQCell *cell);

private:
    Ui::MainWindow *ui;

    ClientSocket *m_tcpSocket;

    QButtonGroup *m_btnGroup;

    QSystemTrayIcon *systemTrayIcon;

    void InitSysTrayIcon();
    void InitQQListMenu();

    void PraseAddFriendReply(const QJsonValue &dataVal);
    void PraseAddFriendRequistReply(const QJsonValue &dataVal);

};
#endif // MAINWINDOW_H
