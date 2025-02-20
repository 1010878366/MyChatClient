#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

<<<<<<< HEAD
//#include "customwidget.h"
//#include "clientsocket.h"
#include "mainwindow.h"
#include <QWidget>
#include<QFile>
=======
#include <QWidget>
#include<QFile>
#include"animationstackedwidget.h"
#include"mainwindow.h"
>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52

namespace Ui {
class LoginWidget;
}

<<<<<<< HEAD
/////////////////////////////////////////////////////////////////////////
/// \brief The LoginWidget class
/// 登陆界面设计
=======
>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52
class LoginWidget : public QWidget
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();


=======
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52
private slots:
    void on_btnWinMenu_clicked();

    void on_btnCancel_clicked();

<<<<<<< HEAD
private:
    Ui::LoginWidget *ui;


=======
    void on_btnLogin_clicked();

private:
    Ui::LoginWidget *ui;
>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52
};

#endif // LOGINWIDGET_H
