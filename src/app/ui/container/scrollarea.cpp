/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "scrollarea.h"

#include <QPainter>
#include <QGraphicsAnchorLayout>
#include <QDebug>

ScrollArea::ScrollArea(QGraphicsItem* parent) : QGraphicsWidget(parent) {
    m_container = new StretchContainer(this);
    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_horizontalScrollBar = new ScrollBar(Qt::Horizontal, this);
    m_verticalScrollBar = new ScrollBar(Qt::Vertical, this);
    m_verticalScrollBar->setHandleColor(QColor(Qt::red));

    m_horizontalScrollBar->setThickness(5);
    m_horizontalScrollBar->setColor(QColor(Qt::green));
    m_horizontalScrollBar->setHandleColor(QColor(Qt::red));

    m_verticalScrollBar->setThickness(5);
    m_verticalScrollBar->setColor(QColor(Qt::green));
    this->setFlags(QGraphicsItem::ItemClipsChildrenToShape);

    connect(m_container, &QGraphicsWidget::geometryChanged,
            this, &ScrollArea::manageScrollbarsVisibility);
    connect(this, &QGraphicsWidget::geometryChanged, this, &ScrollArea::manageScrollbarsVisibility);
    connect(m_verticalScrollBar, &ScrollBar::relativePosChanged,
            this, &ScrollArea::repositionVerticalContent);
    connect(m_horizontalScrollBar, &ScrollBar::relativePosChanged,
            this, &ScrollArea::repositionHorizontalContent);
}

void ScrollArea::wheelEvent(QGraphicsSceneWheelEvent* e) {
    m_verticalScrollBar->artificialScroll((e->delta() < 0) ? 1 : -1);
}

StretchContainer* ScrollArea::container() const {
    return m_container;
}

void ScrollArea::manageScrollbarsVisibility() {
    const QSize containerSize = m_container->geometry().size().toSize();
    const QSize visibleArea = this->geometry().size().toSize();

    if (containerSize.height() > visibleArea.height()) {
        m_verticalScrollBar->setVisible(true);
        m_verticalScrollBar->m_handle->setVisible(true);
        m_verticalScrollBar->setSizeRatio(visibleArea.height() /
                                          static_cast<double>(containerSize.height()));
    } else {
        m_verticalScrollBar->setSizeRatio(1);
        m_verticalScrollBar->setVisible(false);
        m_container->setY(0);
    }

    if (containerSize.width() > visibleArea.width()) {
        m_horizontalScrollBar->setVisible(true);
        m_horizontalScrollBar->m_handle->setVisible(true);
        m_horizontalScrollBar->setSizeRatio(visibleArea.width() /
                                            static_cast<double>(containerSize.width()));
    } else {
        m_horizontalScrollBar->setSizeRatio(1);
        m_horizontalScrollBar->setVisible(false);
        m_container->setX(0);
    }

}

void ScrollArea::repositionVerticalContent(qreal relPos) {
    const qreal range = this->size().height() - m_container->size().height();
    m_container->setY(relPos * range);
}

void ScrollArea::repositionHorizontalContent(qreal relPos) {
    const qreal range = this->size().width() - m_container->size().width();
    m_container->setX(relPos * range);
}

void ScrollArea::setHandleColor(const QColor &color) {
    m_verticalScrollBar->setHandleColor(color);
    m_horizontalScrollBar->setHandleColor(color);
}

void ScrollArea::setGrooveColor(const QColor &color) {
    m_verticalScrollBar->setColor(color);
    m_horizontalScrollBar->setColor(color);
}

StretchContainer::StretchContainer(QGraphicsItem* parent) : QGraphicsWidget(parent) {}

QVariant StretchContainer::itemChange(GraphicsItemChange change, const QVariant &value) {
    QVariant res = QGraphicsWidget::itemChange(change, value);

    if (change == GraphicsItemChange::ItemChildAddedChange
        || change == GraphicsItemChange::ItemChildRemovedChange) {
        QGraphicsWidget* newItem = qgraphicsitem_cast<QGraphicsWidget*>(
                qvariant_cast<QGraphicsItem*>(value));
        if (newItem == nullptr)
            return res;
        connect(newItem, &QGraphicsWidget::geometryChanged, this, &StretchContainer::resizeToChildren);
        this->resizeToChildren();
    }

    return res;
}

void StretchContainer::resizeToChildren() {
    QRectF completeRect{0, 0, 1, 1};
    for (auto child: this->childItems())
        completeRect |= child->boundingRect().translated(child->pos());
    this->resize(completeRect.size());
}
