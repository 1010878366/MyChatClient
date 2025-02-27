#include "qqcelltitle.h"
#include "ui_qqcelltitle.h"

QQCellTitle::QQCellTitle(const QString &groupName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQCellTitle)
{
    ui->setupUi(this);

    ui->lblGroupName->setText(groupName);
    ui->lblNumber->setText(QString("[%1/%2]").arg(0).arg(0));

    this->setAttribute(Qt::WA_Hover,true);  //开启悬停事件
    this->installEventFilter(this);         //安装事件过滤器

    m_isOpen=false;
    m_isHover=false;

}

QQCellTitle::~QQCellTitle()
{
    delete ui;
}

void QQCellTitle::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    if(m_isHover)
    {
        p.setBrush(QColor(100,100,100));
    }
    else
    {
        p.setBrush(QColor(255,255,255));
    }
    p.drawRect(rect());
}

void QQCellTitle::setOnlineAndGroup(int onlineCount,int groupCount)
{
    ui->lblNumber->setText(QString("[%1/%2]").arg(onlineCount).arg(groupCount));
}

bool QQCellTitle::eventFilter(QObject *obj,QEvent *event)
{
    if(obj == this)
    {
        if(event->type() == QEvent::HoverEnter) //进入悬停
        {
            m_isHover = true;
        }
        else if(event->type() == QEvent::HoverLeave)    //离开悬停
        {
            m_isHover = false;

            repaint();
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)  //鼠标点击
        {
            //发送信号
            emit signCellStatusChange(m_isOpen);
            m_isOpen = !m_isOpen;
            if(m_isOpen)
            {
                ui->lblImage->setPixmap(QPixmap(":/images/aio_arrow_down.png"));
            }
            else
            {
                ui->lblImage->setPixmap(QPixmap(":/images/aio_arrow_right.png"));
            }
        }
    }
    return QWidget::eventFilter(obj,event);

}
