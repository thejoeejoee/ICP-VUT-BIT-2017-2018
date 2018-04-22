#include "graphicsview.h"
#include <QResizeEvent>

GraphicsView::GraphicsView(): QGraphicsView()
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void GraphicsView::resizeEvent(QResizeEvent* event) {
    if (scene())
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    QGraphicsView::resizeEvent(event);
    emit this->resized(event->size());
}
