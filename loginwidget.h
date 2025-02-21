#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "customwidget.h"
#include "clientsocket.h"
#include "mainwindow.h"
#include <QWidget>
#include<QFile>
//#include"databasemagr.h"
#include <QJsonObject>
#include <QJsonDocument>

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

private:
    Ui::LoginWidget *ui;

    ClientSocket *m_tcpSocket;
};

#endif // LOGINWIDGET_H
