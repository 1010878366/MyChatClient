#ifndef LINEMESSAGE_H
#define LINEMESSAGE_H

#include <QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLabel>
typedef enum
{
    MessageUser_Self,   //自己发送的消息
    MessageUser_Friend, //好友发送的消息
}MessageUser;

typedef struct LineMessageData
{
    QString message;    //消息
    QString headImg;    //头像
}LineMessageData;

class LineMessage : public QWidget
{
    Q_OBJECT

public:
    explicit LineMessage(LineMessageData lmData, MessageUser msgUser = MessageUser_Self, QWidget *parent = nullptr);
    ~LineMessage();

private:
    int m_selfHeight;
};

#endif // LINEMESSAGE_H
