#include "widget.h"
#include"qqcell.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(300,600);



    int offsetCellY = 0;

    m_cellMyFriend=new QQCell(QString("我的好友"),offsetCellY,this);
    m_cellMyFriend->addCellFriend(QString("zhangsan"),true);
    m_cellMyFriend->addCellFriend(QString("lisi"),false);

    offsetCellY = m_cellMyFriend->height();

    m_cellBlack=new QQCell(QString("黑名单"),offsetCellY,this);
    m_cellBlack->addCellFriend(QString("wangwu"),true);
    m_cellBlack->addCellFriend(QString("zhaoliu"),false);

    connect(m_cellMyFriend,&QQCell::signCellStatusChange,this,&Widget::onCellStatusChange);
    connect(m_cellBlack,&QQCell::signCellStatusChange,this,&Widget::onCellStatusChange);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255));
    p.drawRect(rect());
}

void Widget::onCellStatusChange(QQCell *cell)
{
    if(cell == m_cellMyFriend)
    {
        int offsetCellY = m_cellMyFriend->height();
        m_cellBlack->resizeGeometry(offsetCellY);
    }
    else if(cell == m_cellBlack)
    {
        int offsetCellY = m_cellMyFriend->height();
        m_cellBlack->resizeGeometry(offsetCellY);
    }
}
