﻿#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include<QFile>
#include"animationstackedwidget.h"
#include"mainwindow.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_btnWinMenu_clicked();

    void on_btnCancel_clicked();

    void on_btnLogin_clicked();

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
