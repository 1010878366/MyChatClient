#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

//#include "customwidget.h"
//#include "clientsocket.h"
#include "mainwindow.h"
#include <QWidget>
#include<QFile>

namespace Ui {
class LoginWidget;
}

/////////////////////////////////////////////////////////////////////////
/// \brief The LoginWidget class
/// 登陆界面设计
class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();


private slots:
    void on_btnWinMenu_clicked();

    void on_btnCancel_clicked();

private:
    Ui::LoginWidget *ui;


};

#endif // LOGINWIDGET_H
