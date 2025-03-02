#include "widget.h"
#include "ui_widget.h"
#include<QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    LineMessageData lmData;
    m_layout = new QVBoxLayout();


    for (int i = 0; i < 6; i++)
    {
        LineMessage *lineMsg = nullptr;
        if(i%2 == 1)
        {
            lmData.headImg = QString(":/images/0.bmp");
            lmData.message = QString("正在\n学习\nQt...");
            lineMsg = new LineMessage(lmData,MessageUser_Self,this);
        }
        else
        {
            lmData.headImg = QString(":/images/1.bmp");
            lmData.message = QString("你在做什么？");
            lineMsg = new LineMessage(lmData,MessageUser_Friend,this);
        }
        m_layout->addWidget(lineMsg);
    }
    ui->scrollArea->widget()->setLayout(m_layout);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    LineMessageData lmData;
    //LineMessage *lineMsg = nullptr;
    lmData.headImg = QString(":/images/0.bmp");
    lmData.message = ui->textEdit->toPlainText();
    LineMessage *lineMsg = new LineMessage(lmData,MessageUser_Self,this);
    m_layout->addWidget(lineMsg);
}
