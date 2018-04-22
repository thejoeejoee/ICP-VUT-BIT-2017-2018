#include "scrollarea.h"

#include <QPainter>
#include <QGraphicsAnchorLayout>
#include <QDebug>

ScrollArea::ScrollArea(QGraphicsWidget* parent) : QGraphicsWidget(parent)
{
    // TODO change
    m_container = new Rect(this);
    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_horizontalScrollBar = new ScrollBar(Qt::Horizontal, this);
    m_verticalScrollBar=  new ScrollBar(Qt::Vertical, this);

    m_horizontalScrollBar->setThickness(4);
    m_horizontalScrollBar->setColor(QColor(Qt::green));

    m_verticalScrollBar->setThickness(4);
    m_verticalScrollBar->setColor(QColor(Qt::green));

    // TODO on condition
    m_horizontalScrollBar->setVisible(false);

    connect(m_container, &QGraphicsWidget::geometryChanged, this, &ScrollArea::manageScrollbarsVisibility);
    connect(this, &QGraphicsWidget::geometryChanged, this, &ScrollArea::manageScrollbarsVisibility);
    connect(m_verticalScrollBar, &ScrollBar::relativePosChanged,
            this, &ScrollArea::repositionVerticalContent);
    connect(m_horizontalScrollBar, &ScrollBar::relativePosChanged,
            this, &ScrollArea::repositionHorizontalContent);
}

QGraphicsWidget*ScrollArea::container() const
{
    return m_container;
}

void ScrollArea::manageScrollbarsVisibility()
{
    // TODO implement
    // TODO horizontal
    const QSize containerSize = m_container->geometry().size().toSize();
    const QSize visibleArea = this->geometry().size().toSize();

    if(containerSize.height() > visibleArea.height()) {
        m_verticalScrollBar->setSizeRatio(visibleArea.height() /
                                          static_cast<double>(containerSize.height()));
    }

    else {
        m_verticalScrollBar->setSizeRatio(1);
        m_container->setY(0);
    }
}

void ScrollArea::repositionVerticalContent(qreal relPos)
{
    qreal range = this->size().height() - m_container->size().height();
    m_container->setY(relPos * range);
}

void ScrollArea::repositionHorizontalContent(qreal relPos)
{

}

void Rect::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setPen(QColor(Qt::red));
    painter->drawRect(this->boundingRect());
    painter->restore();
}
