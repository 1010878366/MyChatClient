#include "animationstackedwidget.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QTransform>

AnimationStackedWidget::AnimationStackedWidget(QWidget *parent)
    :QStackedWidget(parent)
{
    m_nextPageIndex = 0;
    m_isAnimating = false;
}

AnimationStackedWidget::~AnimationStackedWidget()
{

}

void AnimationStackedWidget::paintEvent(QPaintEvent *event)
{
    if (m_isAnimating)
    {
        QPainter p(this);
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
    } else {
        QWidget::paintEvent(event);
    }

}

void AnimationStackedWidget::animation(int pageIndex)
{
    if (m_isAnimating)
    {
        return;
    }
    m_nextPageIndex = pageIndex;

    int offsetX = frameRect().width();
    int offsetY = frameRect().height();
    widget(pageIndex)->setGeometry(0,0,offsetX, offsetY);

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

    m_isAnimating = true;

    animation->start();
}

void AnimationStackedWidget::onValueChanged(const QVariant &value)
{
    //值改变了以后
    repaint();
}

void AnimationStackedWidget::onFinished()
{
    m_isAnimating = false;
    //动画结束
    widget(m_nextPageIndex)->show();
    widget(m_nextPageIndex)->raise();

    setCurrentWidget(widget(m_nextPageIndex));

    repaint();
}
