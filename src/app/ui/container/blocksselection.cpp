#include "blocksselection.h"
#include <QDebug>
#include <QPainter>
#include <app/core/blocks/blocks.h>

BlocksSelection::BlocksSelection(QGraphicsWidget* parent): ScrollArea(parent)
{
    m_layout = new QGraphicsLinearLayout(Qt::Vertical, this->container());
    m_layout->setSpacing(30);
    m_layout->setContentsMargins(30, 75, 30, 30);

    for(const QString& singleBlockClassId: Block::registeredItems()) {
        auto newBlock = Block::createNew(singleBlockClassId, this);
        newBlock->view()->setInputsVisible(false);
        newBlock->view()->setOutputVisible(false);
        this->addItem(newBlock->view());
    }

    this->setFlags(QGraphicsItem::ItemClipsChildrenToShape);
    this->setGrooveColor(QColor(Qt::transparent));
    this->setHandleColor(QColor("#4c4c4c"));

    connect(this->container(), &QGraphicsWidget::geometryChanged, [this]() { this->update(); });
}

void BlocksSelection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setPen(QColor("#0f81bc"));
    painter->setFont(QFont("Montserrat Light", 35));
    painter->drawText(QPointF(25, 55), tr("Blocks"));

    painter->setPen(QColor(Qt::transparent));
    painter->setBrush(QColor(Qt::white));
    painter->drawRect(
                0, static_cast<int>(this->container()->y()) + 65,
                static_cast<int>(this->size().width()), 55
    );

    painter->setPen(QColor("#e0e0df"));
    painter->setBrush(QColor(Qt::transparent));
    painter->drawRect(this->boundingRect());
    painter->restore();
}

void BlocksSelection::addItem(QGraphicsWidget* item)
{
    Q_ASSERT(item != nullptr);

    item->setParentItem(this->container());
    m_layout->addItem(item);
}
