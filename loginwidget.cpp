#include "loginwidget.h"
#include "ui_loginwidget.h"
#include<QFile>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    //设置QSS
    QFile file(":/qss/resource/qss/default.css");
    file.open(QIODevice::ReadOnly);

    //设置样式表
    qApp->setStyleSheet(file.readAll());
    file.close();

    this->setWindowFlags(Qt::FramelessWindowHint);  //去掉qt自带的标题栏
    //this->setAttribute(Qt::WA_TranslucentBackground);   //使透明生效


}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_btnWinMenu_clicked()
{
    ui->stackedWidget->setstartVal(0);
    ui->stackedWidget->setendVal(180);
    ui->stackedWidget->animation(1);
}

void LoginWidget::on_btnCancel_clicked()
{
    ui->stackedWidget->setstartVal(0);
    ui->stackedWidget->setendVal(-180);
    ui->stackedWidget->animation(0);
}
