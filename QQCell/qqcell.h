#ifndef QQCELL_H
#define QQCELL_H

#include <QWidget>
#include"qqcelltitle.h"
#include"qqcellline.h"
#include<QList>

#define QQ_CELL_WIDTH 300
#define QQ_CELL_TITLE_WIDTH 300
#define QQ_CELL_TITLE_HEIGHT 30
#define QQ_CELL_LINE_WIDTH 300
#define QQ_CELL_LINE_HEIGHT 50

class QQCell : public QWidget
{
    Q_OBJECT

public:
    explicit QQCell(const QString &groupTitleName,int offsetCellY = 0,QWidget *parent = nullptr);
    ~QQCell();

    void addCellFriend(const QString &name,bool isOnline=true);
    void resizeGeometry(int offsetCellY);

private slots:
    void onCellStatusChange(bool);

signals:
    void signCellStatusChange(QQCell *);

private:
    QQCellTitle *m_cellTitle;
    QWidget *m_cellContent;

    int m_onlineCount;
    int m_groupCount;
    int m_isOpen;   //QQCell是否展开
    int m_offsetCellY;  //偏移量

    QList<QQCellLine*>m_cellLines;  //  好友组中的好友个数
};

#endif // QQCELL_H
