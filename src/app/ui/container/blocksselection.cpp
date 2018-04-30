#include "blocksselection.h"
#include <QDebug>
#include <QPainter>
#include <app/core/blocks/blocks.h>

BlocksSelection::BlocksSelection(QGraphicsWidget* parent): ScrollArea(parent)
{
    m_layout = new QGraphicsLinearLayout(Qt::Vertical, this->container());

    for(const QString& singleBlockClassId: Block::registeredItems())
        this->addItem(Block::createNew(singleBlockClassId, this)->view());

    this->setFlags(QGraphicsItem::ItemClipsChildrenToShape);
}

void BlocksSelection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setPen(QColor(Qt::black));
    painter->drawRect(this->boundingRect());
    painter->restore();
}

void BlocksSelection::addItem(QGraphicsWidget* item)
{
    Q_ASSERT(item != nullptr);

    item->setParentItem(this->container());
    m_layout->addItem(item);
}
