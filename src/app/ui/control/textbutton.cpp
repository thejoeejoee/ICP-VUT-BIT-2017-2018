/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "textbutton.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

TextButton::TextButton(const QString &text, QGraphicsItem* parent) : Clickable(parent) {
    m_text = text;

    connect(this, &TextButton::fontChanged, this, &TextButton::resizeToText);
}

void TextButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->save();
    painter->setClipRect(option->exposedRect);
    painter->setFont(m_font);

    Clickable::paint(painter, option, widget);

    painter->setPen(QColor(m_color));
    painter->drawText(this->boundingRect(), Qt::AlignCenter, m_text);
    painter->restore();
}

QFont TextButton::font() const {
    return m_font;
}

QColor TextButton::color() const {
    return m_color;
}

void TextButton::resizeToText() {
    QFontMetrics fm(m_font);
    QSizeF newGeometry = fm.boundingRect(m_text).size();
    newGeometry.rwidth() *= 1.3;
    this->resize(newGeometry);
    this->setMaximumWidth(newGeometry.width());
    this->setMinimumWidth(newGeometry.width());
}

void TextButton::setFont(QFont font) {
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(m_font);
}

void TextButton::setColor(QColor color) {
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(m_color);
}
