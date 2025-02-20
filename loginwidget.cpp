#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

<<<<<<< HEAD
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

=======
>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52
    //设置QSS
    QFile file(":/qss/resource/qss/default.css");
    file.open(QIODevice::ReadOnly);

    //设置样式表
    qApp->setStyleSheet(file.readAll());
    file.close();

<<<<<<< HEAD
    ui->stackedWidget->setCurrentIndex(0);

=======
    this->setWindowFlags(Qt::FramelessWindowHint);  //去掉qt自带的标题栏
    //this->setAttribute(Qt::WA_TranslucentBackground);   //使透明生效

    ui->stackedWidget->setCurrentIndex(0);
>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52
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
<<<<<<< HEAD
=======

void LoginWidget::on_btnLogin_clicked()
{
    MainWindow *mainWindow=new MainWindow;
    mainWindow->show();

    this->hide();   //登录窗口隐藏
}
>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52
