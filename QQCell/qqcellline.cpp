#include "qqcellline.h"
#include "ui_qqcellline.h"

QQCellLine::QQCellLine(const QString &name,bool isOnline,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQCellLine)
{
    ui->setupUi(this);

    ui->lblFriendName->setText(name);

    if(isOnline)
    {
        ui->lblStatus->setText(QString("当前用户状态：在线"));
    }
    else
    {
        ui->lblStatus->setText(QString("当前用户状态：离线"));
    }
}

QQCellLine::~QQCellLine()
{
    delete ui;
}

void QQCellLine::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255));
    p.drawRect(rect());
}
