#include "blockportview.h"


BlockPortView::BlockPortView(QGraphicsItem* parent): QGraphicsWidget(parent)
{
    m_opacityAnimation = new QVariantAnimation{this};
    m_opacityAnimation->setDuration(200);

    connect(m_opacityAnimation, &QVariantAnimation::valueChanged, [this](const QVariant& v) {
        this->setOpacity(v.toReal());
    });
}

void BlockPortView::animateHide(bool animate)
{
    if(this->opacity() == 0.)
        return;

    if(animate) {
        m_opacityAnimation->setStartValue(1.);
        m_opacityAnimation->setEndValue(0.);
        m_opacityAnimation->start();
    }

    else
        this->setOpacity(0);
}

void BlockPortView::animateShow(bool animate)
{
    if(this->opacity() == 1.)
        return;

    if(animate) {
        m_opacityAnimation->setStartValue(0.);
        m_opacityAnimation->setEndValue(1.);
        m_opacityAnimation->start();
    }

    else
        this->setOpacity(1);
}
