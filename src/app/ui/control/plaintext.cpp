/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "plaintext.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

PlainText::PlainText(QGraphicsItem* parent) : QGraphicsTextItem(parent) {
    this->setTextInteractionFlags(Qt::NoTextInteraction);
}

void PlainText::setPropagateMouse(bool v) {
    m_propagateMouse = v;
}

void PlainText::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    if (m_propagateMouse) {
        QGraphicsTextItem::mousePressEvent(e);
        return;
    }
    e->accept();
    emit this->clicked();
}
