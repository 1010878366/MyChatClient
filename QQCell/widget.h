#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPainter>
#include"qqcell.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onCellStatusChange(QQCell *);

private:
    QQCell *m_cellMyFriend;
    QQCell *m_cellBlack;

protected:
    void paintEvent(QPaintEvent *event);

};
#endif // WIDGET_H
