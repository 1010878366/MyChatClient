#include "animationstackedwidget.h"
#include<QPropertyAnimation>
#include<QPainter>
#include<QTransform>

AnimationStackedWidget::AnimationStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    // 构造函数实现
    m_nextPageIndex = 0;
}

AnimationStackedWidget::~AnimationStackedWidget()
{
    // 析构函数实现
}

void AnimationStackedWidget::someVirtualFunction()
{
    // 虚函数实现
}



void AnimationStackedWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap pix(":/resource/head/head-48.png");
    if (iRotateVal > 0 && iRotateVal <= 90) { //
        QPixmap pix(currentWidget()->size());
        currentWidget()->render(&pix);

        //旋转
        QTransform transform;
        transform.translate(width()/2,0);
        transform.rotate(iRotateVal, Qt::YAxis);
        p.setTransform(transform);
        p.drawPixmap(-1*width()/2, 0,pix);
    } else if (iRotateVal > 90 && iRotateVal <= 180) { //
        QPixmap pix(widget(m_nextPageIndex)->size());
        widget(m_nextPageIndex)->render(&pix);

        //旋转
        QTransform transform;
        transform.translate(width()/2,0);
        transform.rotate(iRotateVal+180, Qt::YAxis);
        p.setTransform(transform);
        p.drawPixmap(-1*width()/2, 0,pix);
    }
    else if (iRotateVal > -180 && iRotateVal <= -90) { //
        QPixmap pix(widget(m_nextPageIndex)->size());
        widget(m_nextPageIndex)->render(&pix);

        //旋转
        QTransform transform;
        transform.translate(width()/2,0);
        transform.rotate(iRotateVal+180, Qt::YAxis);
        p.setTransform(transform);
        p.drawPixmap(-1*width()/2, 0,pix);
    } else if (iRotateVal > -90 && iRotateVal < 0) { //
        QPixmap pix(currentWidget()->size());
        currentWidget()->render(&pix);

        //旋转
        QTransform transform;
        transform.translate(width()/2,0);
        transform.rotate(iRotateVal, Qt::YAxis);
        p.setTransform(transform);
        p.drawPixmap(-1*width()/2, 0,pix);
    }
}
void AnimationStackedWidget::animation(int pageIndex)
{
    m_nextPageIndex = pageIndex;
    //propertyName
    QPropertyAnimation *animation = new QPropertyAnimation(this, "rotateVal");

    //设置动画持续时间
    animation->setDuration(700);

    animation->setEasingCurve(QEasingCurve::Linear);

    //设置动画起始值
    animation->setStartValue(m_startVal);

    //设置动画结束值
    animation->setEndValue(m_endVal);

    QObject::connect(animation, &QPropertyAnimation::valueChanged, this, &AnimationStackedWidget::onValueChanged);
    QObject::connect(animation, &QPropertyAnimation::finished, this, &AnimationStackedWidget::onFinished);

    currentWidget()->hide();
    animation->start();

}

void AnimationStackedWidget::onValueChanged(const QVariant &value)
{
    //值改变后
    repaint();
}

void AnimationStackedWidget::onFinished()
{
    //动画结束
    widget(m_nextPageIndex)->show();
    widget(m_nextPageIndex)->raise();

    setCurrentWidget(widget(m_nextPageIndex));
}
