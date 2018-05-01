#include "warningpopup.h"

#include <QPainter>

WarningPopUp::WarningPopUp(QGraphicsWidget* parent): QGraphicsWidget (parent)
{
    m_animation = new QVariantAnimation{this};
    m_animation->setDuration(250);
    this->setOpacity(0);

    connect(&m_timer, &QTimer::timeout, this, &WarningPopUp::hideAnimate);
    connect(m_animation, &QVariantAnimation::valueChanged, [this](const QVariant& v) {
        this->setOpacity(v.toDouble());
    });
}

void WarningPopUp::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();
    painter->setBrush(QColor(Qt::yellow));
    painter->drawRect(this->boundingRect());
    painter->restore();
}

void WarningPopUp::hideAnimate()
{
    m_animation->setStartValue(this->opacity());
    m_animation->setEndValue(0);
    m_animation->start();
}

void WarningPopUp::popUp(const QString& msg, int seconds)
{
    m_msg = msg;
    m_timer.stop();
    m_timer.start(seconds * 1000);

    m_animation->setStartValue(this->opacity());
    m_animation->setEndValue(1);
    m_animation->start();
}
