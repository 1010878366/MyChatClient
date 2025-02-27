#include "qqcell.h"

QQCell::QQCell(const QString &groupTitleName,int offsetCellY,QWidget *parent) :
    QWidget(parent)
{

    //this->setStyleSheet("background-color:rgb(255,255,255);");

    m_onlineCount = 0;
    m_groupCount = 0;
    m_isOpen=false;
    m_offsetCellY = offsetCellY;

    m_cellTitle = new QQCellTitle(groupTitleName,this);
    m_cellTitle->setGeometry(0,0,QQ_CELL_TITLE_WIDTH,QQ_CELL_TITLE_HEIGHT);
    m_cellContent = new QWidget(this);
    m_cellContent->setGeometry(0,QQ_CELL_TITLE_HEIGHT,QQ_CELL_WIDTH,0);
    m_cellContent->hide();

    connect(m_cellTitle,&QQCellTitle::signCellStatusChange,this,&QQCell::onCellStatusChange);

    this->setGeometry(0,offsetCellY,QQ_CELL_WIDTH,QQ_CELL_TITLE_HEIGHT);

}

QQCell::~QQCell()
{

}

void QQCell::resizeGeometry(int offsetCellY)
{
    int newHeight = QQ_CELL_LINE_HEIGHT*m_cellLines.size();
    m_cellContent->setMinimumHeight(newHeight);
    m_cellContent->setMaximumHeight(newHeight);

    this->setMinimumHeight(newHeight + QQ_CELL_TITLE_HEIGHT);
    this->setMaximumHeight(newHeight + QQ_CELL_TITLE_HEIGHT);

    this->setGeometry(0,offsetCellY,QQ_CELL_WIDTH,newHeight + QQ_CELL_TITLE_HEIGHT);

}

void QQCell::addCellFriend(const QString &name,bool isOnline)
{
    QQCellLine *cellLine = new QQCellLine(name,isOnline,m_cellContent);
    m_cellLines.append(cellLine);

    //计算偏移量
    int offsetCellLineY = (m_cellLines.size()-1) * QQ_CELL_LINE_HEIGHT;
    cellLine->setGeometry(0,offsetCellLineY,QQ_CELL_LINE_WIDTH,QQ_CELL_LINE_HEIGHT);


}

void QQCell::onCellStatusChange(bool isOpen)
{
    if(!isOpen)
    {
        //设置大小
        resizeGeometry(m_offsetCellY);
        m_cellContent->show();
    }
    else
    {
        int newHeight = QQ_CELL_LINE_HEIGHT*m_cellLines.size();
        m_cellContent->setMinimumHeight(0);
        m_cellContent->setMaximumHeight(0);

        this->setMinimumHeight(QQ_CELL_TITLE_HEIGHT);
        this->setMaximumHeight(QQ_CELL_TITLE_HEIGHT);

        this->setGeometry(0,m_offsetCellY,QQ_CELL_WIDTH,QQ_CELL_LINE_HEIGHT);
        m_cellContent->hide();
    }
    emit signCellStatusChange(this);
}
