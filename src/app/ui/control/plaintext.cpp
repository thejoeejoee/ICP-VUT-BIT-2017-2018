#include "plaintext.h"

#include <QGraphicsSceneMouseEvent>

#include <QDebug>

PlainText::PlainText(QGraphicsItem* parent): QGraphicsTextItem(parent)
{
    this->setTextInteractionFlags(Qt::NoTextInteraction);
}

void PlainText::setPropagateMouse(bool v)
{
    m_propagateMouse = v;
}

void PlainText::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    if(m_propagateMouse) {
        QGraphicsTextItem::mousePressEvent(e);
        return;
    }

void PlainText::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    e->accept();
    emit this->clicked();
}
