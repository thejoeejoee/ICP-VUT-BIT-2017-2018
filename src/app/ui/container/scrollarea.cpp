#include "scrollarea.h"

#include <QPainter>
#include <QGraphicsAnchorLayout>
#include <QDebug>

ScrollArea::ScrollArea(QGraphicsWidget* parent) : QGraphicsWidget(parent)
{
    m_container = new QGraphicsWidget(this);
    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_horizontalScrollBar = new ScrollBar(Qt::Horizontal, this);
    m_verticalScrollBar = new ScrollBar(Qt::Vertical, this);
    m_verticalScrollBar->setHandleColor(QColor(Qt::red));

    m_horizontalScrollBar->setThickness(4);
    m_horizontalScrollBar->setColor(QColor(Qt::green));
    m_horizontalScrollBar->setHandleColor(QColor(Qt::red));

    m_verticalScrollBar->setThickness(4);
    m_verticalScrollBar->setColor(QColor(Qt::green));

    connect(m_container, &QGraphicsWidget::geometryChanged,
            this, &ScrollArea::manageScrollbarsVisibility);
    connect(this, &QGraphicsWidget::geometryChanged, this, &ScrollArea::manageScrollbarsVisibility);
    connect(m_verticalScrollBar, &ScrollBar::relativePosChanged,
            this, &ScrollArea::repositionVerticalContent);
    connect(m_horizontalScrollBar, &ScrollBar::relativePosChanged,
            this, &ScrollArea::repositionHorizontalContent);
}

void ScrollArea::wheelEvent(QGraphicsSceneWheelEvent* e)
{
    m_verticalScrollBar->artificialScroll((e->delta() < 0) ?1 :-1);
}

QGraphicsWidget*ScrollArea::container() const
{
    return m_container;
}

void ScrollArea::manageScrollbarsVisibility()
{
    const QSize containerSize = m_container->geometry().size().toSize();
    const QSize visibleArea = this->geometry().size().toSize();

    if(containerSize.height() > visibleArea.height()) {
        m_verticalScrollBar->setVisible(true);
        m_verticalScrollBar->m_handle->setVisible(true);
        m_verticalScrollBar->setSizeRatio(visibleArea.height() /
                                          static_cast<double>(containerSize.height()));
    }

    else {
        m_verticalScrollBar->setSizeRatio(1);
        m_verticalScrollBar->setVisible(false);
        m_container->setY(0);
    }

    if(containerSize.width() > visibleArea.width()) {
        m_horizontalScrollBar->setVisible(true);
        m_horizontalScrollBar->m_handle->setVisible(true);
        m_horizontalScrollBar->setSizeRatio(visibleArea.width() /
                                            static_cast<double>(containerSize.width()));
    }
    else {
        m_horizontalScrollBar->setSizeRatio(1);
        m_horizontalScrollBar->setVisible(false);
        m_container->setX(0);
    }

}

void ScrollArea::repositionVerticalContent(qreal relPos)
{
    const qreal range = this->size().height() - m_container->size().height();
    m_container->setY(relPos * range);
}

void ScrollArea::repositionHorizontalContent(qreal relPos)
{
    const qreal range = this->size().width() - m_container->size().width();
    m_container->setX(relPos * range);
}

void ScrollArea::setHandleColor(const QColor& color)
{
    m_verticalScrollBar->setHandleColor(color);
    m_horizontalScrollBar->setHandleColor(color);
}

void ScrollArea::setGrooveColor(const QColor& color)
{
    m_verticalScrollBar->setColor(color);
    m_horizontalScrollBar->setColor(color);
}
