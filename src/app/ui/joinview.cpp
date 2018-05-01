#include "joinview.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <app/core/block.h>
#include <app/ui/blockview.h>

JoinView::JoinView(Identifier dataId, QGraphicsItem* parent)
    : QObject{}, QGraphicsLineItem(parent)
{
    m_dataId = dataId;
    m_pen = QPen{QColor{"#4c4c4c"}, 3};
    this->setPen(m_pen);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(ItemIsFocusable);
}

void JoinView::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Delete) {
        for(auto item: this->scene()->selectedItems()) {
            auto blockView = dynamic_cast<BlockView*>(item);
            auto joinView = dynamic_cast<JoinView*>(item);

            if(blockView != nullptr)
                emit blockView->deleteRequest(blockView->blockData()->id());
            else if(joinView != nullptr)
                emit joinView->deleteRequest(joinView->dataId());
        }
    }

    QGraphicsLineItem::keyPressEvent(event);
}

QVariant JoinView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if(change == QGraphicsItem::ItemSelectedChange) {
        if(value == true) {
            this->setFocus();
            m_pen.setColor(QColor{"#0f81bc"});
        }
        else
            m_pen.setColor(QColor{"#4c4c4c"});
        this->setPen(m_pen);
        this->update();
    }

    return QGraphicsLineItem::itemChange(change, value);
}

void JoinView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(this->pen());
    painter->drawLine(this->line());
}

Identifier JoinView::dataId() const
{
    return m_dataId;
}
