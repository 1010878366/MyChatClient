#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "customwidget.h"
#include "clientsocket.h"
#include "mainwindow.h"
#include <QWidget>
#include<QFile>
#include"databasemagr.h"
#include <QJsonObject>
#include <QJsonDocument>
#include<QDebug>

namespace Ui {
class LoginWidget;
}

/////////////////////////////////////////////////////////////////////////
/// \brief The LoginWidget class
/// 登陆界面设计
class LoginWidget : public CustomMoveWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();


private slots:
    void on_btnWinMenu_clicked();

    void on_btnCancel_clicked();

    void on_btnLogin_clicked();

    void on_btnWinClose_clicked();

    void onSignalMessage(const quint8 &type,const QJsonValue &dataVal);
    void onSignalStatus(const quint8 &state);

private:
    //登录
    void ParseLogin(const QJsonValue dataVal);

private:
    Ui::LoginWidget *ui;

    ClientSocket *m_tcpSocket;
};

#endif // LOGINWIDGET_H
