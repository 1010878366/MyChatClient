#include "linemessage.h"

LineMessage::LineMessage(LineMessageData lmData, MessageUser msgUser, QWidget *parent) :
    QWidget(parent)
{

    m_selfHeight = 50;
    //------lmLayout-----
    QHBoxLayout *lmLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayoutTitleAndMsg = new QVBoxLayout(this);   //vLayout中需要显示时间，消息
    QVBoxLayout *vLayoutHead = new QVBoxLayout(this);
    QLabel *lblHeadImg = new QLabel(this);

    QWidget *wigHead = new QWidget(this);
    vLayoutHead->addWidget(lblHeadImg);
    vLayoutHead->addWidget(wigHead);

    QWidget *wigTitle = new QWidget();
    QLabel *lblTitle = new QLabel(wigTitle);

    QWidget *wigMsg = new QWidget();
    QLabel *lblMsg = new QLabel(wigMsg);

    wigTitle->setMinimumWidth(580);
    lblTitle->setMinimumWidth(560);
    wigMsg->setMinimumWidth(560);

    QString txtTitle = QString("%1 %2").arg(QString("2025/03/02 12:30:00")).arg(QString("zhangkai"));
    lblTitle->setText(txtTitle);

    lblMsg->setText(lmData.message);    //多行
    lblMsg->setMinimumWidth(580);
    vLayoutTitleAndMsg->addWidget(wigTitle);
    vLayoutTitleAndMsg->addWidget(wigMsg);

    QFontMetrics fontMet(lblMsg->font());
    int msgFontHeight = fontMet.height();   //获取字体高度
    int msgFontLeading = fontMet.leading();  //获取行间距

    //------lblHeadImg-----
    lblHeadImg->setPixmap(QPixmap(lmData.headImg));

    int msgTextHeight = 0;
    if(msgUser == MessageUser_Self)
    {
        msgTextHeight = msgFontHeight*3+msgFontLeading*2;
        lblMsg->setMinimumHeight(msgTextHeight);
        wigMsg->setMinimumHeight(msgTextHeight);

        lmLayout->addLayout(vLayoutTitleAndMsg);
        lmLayout->addLayout(vLayoutHead);
        lblTitle->setAlignment(Qt::AlignRight);
        lblMsg->setAlignment(Qt::AlignRight);
        lblHeadImg->setAlignment(Qt::AlignRight);
    }
    else if(msgUser == MessageUser_Friend)
    {
        msgTextHeight = msgFontHeight*3+msgFontLeading*2;
        lblMsg->setMinimumHeight(msgTextHeight);
        wigMsg->setMinimumHeight(msgTextHeight);

        lmLayout->addLayout(vLayoutHead);
        lmLayout->addLayout(vLayoutTitleAndMsg);

        lblTitle->setAlignment(Qt::AlignLeft);
        lblMsg->setAlignment(Qt::AlignLeft);
        lblHeadImg->setAlignment(Qt::AlignLeft);
    }

    //this->setStyleSheet("background-color:yellow");

    m_selfHeight+=msgTextHeight;
    this->setGeometry(0,0,680,m_selfHeight);
    this->setMinimumHeight(m_selfHeight);
    this->setMaximumHeight(m_selfHeight);

    this->setLayout(lmLayout);
}

LineMessage::~LineMessage()
{

}
