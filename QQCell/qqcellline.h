#ifndef QQCELLLINE_H
#define QQCELLLINE_H

#include <QWidget>
#include<QPainter>

namespace Ui {
class QQCellLine;
}

class QQCellLine : public QWidget
{
    Q_OBJECT

public:
    explicit QQCellLine(const QString &name,bool isOnline = true,QWidget *parent = nullptr);
    ~QQCellLine();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::QQCellLine *ui;


};

#endif // QQCELLLINE_H
