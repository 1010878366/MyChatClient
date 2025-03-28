#ifndef ANIMATIONSTACKEDWIDGET_H
#define ANIMATIONSTACKEDWIDGET_H

#include <QStackedWidget>

class AnimationStackedWidget : public QStackedWidget
{
    Q_OBJECT
    //Qt提供的属性系统,独立于编译器和平台的库
    //Qt属性是基于元数据对象系统 信号和槽
    //需要用moc进行编译,需要继承QObject
    Q_PROPERTY(float rotateVal READ rotateVal WRITE setRotateVal)

public:
    AnimationStackedWidget(QWidget *parent = 0);
    ~AnimationStackedWidget();

    //动画效果
    void animation(int pageIndex);

    float rotateVal() {
        return iRotateVal;
    }
    void setRotateVal(float val) {
        iRotateVal = val;
    } //设置旋转值

    float startVal() {
        return m_startVal;
    }
    void setStartVal(float val) {
        m_startVal = val;
    }

    float endVal() {
        return m_endVal;
    }
    void setEndVal(float val) {
        m_endVal = val;
    }

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void onValueChanged(const QVariant &value);
    void onFinished();

private:
    float iRotateVal;   //旋转值
    int m_startVal;     //动画起始值
    int m_endVal;       //动画结束值

    int m_nextPageIndex;    //下一页

    bool m_isAnimating;
};

#endif // ANIMATIONSTACKEDWIDGET_H

