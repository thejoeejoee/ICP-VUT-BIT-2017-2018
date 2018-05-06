/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "warningpopup.h"

#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>

WarningPopUp::WarningPopUp(QGraphicsWidget* parent) : QGraphicsWidget(parent) {
    m_animation = new QVariantAnimation{this};
    m_animation->setDuration(350);
    this->setOpacity(0);
    m_renderer.load(QString(":/res/image/warning_icon.svg"));
    m_font = QFont{"Montserrat", 20};

    connect(&m_timer, &QTimer::timeout, this, &WarningPopUp::hideAnimate);
    connect(m_animation, &QVariantAnimation::valueChanged, [this](const QVariant &v) {
        this->setOpacity(v.toDouble());
    });
}

void WarningPopUp::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->save();
    painter->setClipRect(option->exposedRect);
    painter->setOpacity(0.4 * this->opacity());
    painter->setPen(QColor{Qt::transparent});
    painter->setBrush(QColor("#f8a61a"));

    const double height = this->size().height();
    const double width = this->size().width();

    // draw background
    QPolygonF polygon;
    polygon << QPointF(0, 0) << QPointF(width, 0) << QPointF(width - height, height)
            << QPointF(0, width) << QPointF(0, 0);
    painter->drawPolygon(polygon);

    // render icon
    painter->setOpacity(1.0 * this->opacity());
    constexpr int iconOffset = 3;
    m_renderer.render(painter, QRectF(
            10 + iconOffset,
            iconOffset,
            height - 2 * iconOffset,
            height - 2 * iconOffset));

    // draw text
    painter->setPen(QColor{"#ca7a29"});
    painter->setFont(m_font);
    painter->drawText(this->boundingRect().adjusted(20 + height, 0, 0, 0),
                      Qt::AlignVCenter, m_msg);

    painter->restore();
}

void WarningPopUp::hideAnimate() {
    m_animation->setStartValue(this->opacity());
    m_animation->setEndValue(0.);
    m_animation->start();
}

void WarningPopUp::popUp(const QString &msg, int seconds) {
    m_msg = msg;
    QFontMetrics fm(m_font);
    this->resize(fm.width(m_msg) + 25 + this->size().height() * 2, this->size().height());

    m_timer.stop();
    m_timer.start(seconds * 1000);
    m_animation->setStartValue(this->opacity());
    m_animation->setEndValue(1.);
    m_animation->start();
}
