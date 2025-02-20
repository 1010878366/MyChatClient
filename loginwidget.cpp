#include "loginwidget.h"
#include "ui_loginwidget.h"
#include"mainwindow.h"

LoginWidget::LoginWidget(QWidget *parent) :
    CustomMoveWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    //设置QSS
    QFile file(":/qss/resource/qss/default.css");
    file.open(QIODevice::ReadOnly);

    //设置样式表
    qApp->setStyleSheet(file.readAll());
    file.close();

    ui->stackedWidget->setCurrentIndex(0);

    //给lineEditUser添加图片
    ui->lineEditUser->SetIcon(QPixmap(":/resource/common/ic_user.png"));
    ui->lineEditPasswd->SetIcon(QPixmap(":/resource/common/ic_lock.png"));
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

void LoginWidget::on_btnLogin_clicked()
{
    MainWindow *mainWindow=new MainWindow;
    mainWindow->show();

    this->hide();   //登录窗口隐藏
}
