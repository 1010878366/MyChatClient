#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include"animationstackedwidget.h"

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

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
