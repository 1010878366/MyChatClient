#ifndef QQCELLTITLE_H
#define QQCELLTITLE_H

#include <QWidget>
#include<QPainter>

namespace Ui {
class QQCellTitle;
}

class QQCellTitle : public QWidget
{
    Q_OBJECT

public:
    explicit QQCellTitle(const QString &groupName, QWidget *parent = nullptr);
    ~QQCellTitle();

    void setOnlineAndGroup(int onlineCount = 0,int groupCount = 0);

signals:
    void signCellStatusChange(bool);

protected:
    bool eventFilter(QObject *obj,QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::QQCellTitle *ui;
    bool m_isHover;
    bool m_isOpen;
};

#endif // QQCELLTITLE_H
