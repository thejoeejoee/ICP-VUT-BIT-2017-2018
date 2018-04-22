#include "scrollbar.h"
#include <QGraphicsAnchorLayout>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

ScrollBar::ScrollBar(Qt::Orientation orientation, QGraphicsWidget* parent): QGraphicsWidget(parent)
{
    auto parentLayout = dynamic_cast<QGraphicsAnchorLayout*>(parent->layout());
    Q_ASSERT_X(parentLayout != nullptr,
               "Scrollbar init", "Parent(ScrollArea) need to has anchor layout");

    m_orientation = orientation;
    m_mousePressed = false;
    m_handle = new ScrollBarHandle(orientation, this);
    this->setMinimumSize(0, 0);

    if(orientation == Qt::Vertical) {
        parentLayout->addCornerAnchors(this, Qt::TopRightCorner, parentLayout, Qt::TopRightCorner);
        parentLayout->addCornerAnchors(this, Qt::BottomRightCorner,
                                       parentLayout, Qt::BottomRightCorner);
    }

    else if(orientation == Qt::Horizontal) {
        parentLayout->addCornerAnchors(this, Qt::BottomLeftCorner,
                                       parentLayout, Qt::BottomLeftCorner);
        parentLayout->addCornerAnchors(this, Qt::BottomRightCorner,
                                       parentLayout, Qt::BottomRightCorner);
    }

    // resizing
    connect(this, &ScrollBar::thicknessChanged, this, &ScrollBar::resizeThickeness);

    connect(this, &ScrollBar::colorChanged, [this] { this->update(); });
    connect(this, &ScrollBar::handleColorChanged, m_handle, &ScrollBarHandle::setColor);
    connect(this, &ScrollBar::geometryChanged, this, &ScrollBar::setSlideArea);
    connect(this, &ScrollBar::sizeRatioChanged, this, &ScrollBar::resizeHandle);
    connect(m_handle, &ScrollBarHandle::relativePosChanged, this, &ScrollBar::relativePosChanged);
}

void ScrollBar::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    m_mousePressed = true;
    m_pressPoint = e->pos();
    m_handleOriginPos = m_handle->pos();
}

void ScrollBar::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    Q_UNUSED(e);
    m_mousePressed = false;
}

void ScrollBar::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
    if(m_orientation == Qt::Vertical)
        this->move(m_handleOriginPos, (e->pos() - m_pressPoint).y());
    else
        this->move(m_handleOriginPos, (e->pos() - m_pressPoint).x());
}

void ScrollBar::wheelEvent(QGraphicsSceneWheelEvent* e)
{
    this->artificialScroll((e->delta() < 0) ?1 :-1);
}

void ScrollBar::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setBrush(m_color);
    painter->setPen(QColor(Qt::transparent));
    painter->drawRect(this->boundingRect());
    painter->restore();
}

qreal ScrollBar::relativePos() const
{
    return m_handle->relativePos();
}

void ScrollBar::resizeThickeness()
{
    if(m_orientation == Qt::Vertical) {
        this->setPreferredWidth(m_thickness);
        m_handle->setPreferredWidth(m_thickness);
    }
    else if(m_orientation == Qt::Horizontal) {
        this->setPreferredHeight(m_thickness);
        m_handle->setPreferredHeight(m_thickness);
    }
}

void ScrollBar::setSlideArea()
{
    m_handle->setSlideArea(this->geometry().toRect().size());
}

void ScrollBar::resizeHandle()
{
    if(m_orientation == Qt::Vertical)
        m_handle->setPreferredHeight(m_sizeRatio * this->size().height());

    else if(m_orientation == Qt::Horizontal)
        m_handle->setPreferredWidth(m_sizeRatio * this->size().width());
}

void ScrollBar::artificialScroll(qreal delta)
{
    const qreal speed = 25.;
    if(m_orientation == Qt::Vertical)
        this->move(m_handle->pos(), delta * m_handle->slideArea().height() / speed);
    else
        this->move(m_handle->pos(), delta * m_handle->slideArea().width() / speed);
}

void ScrollBar::move(QPointF handleOriginPos, qreal delta)
{
    QPointF newPos = handleOriginPos + QPointF(delta, delta);
    const QSizeF handleSize = m_handle->size();
    // new position of point of handle on the other side
    const QPointF newHandleOtherPos = newPos + QPointF(handleSize.width(), handleSize.height());

    if(m_orientation == Qt::Vertical) {
        newPos.rx() = handleOriginPos.x();    // allow only movement in vertical axis
        if(newHandleOtherPos.y() > m_handle->slideArea().height())
            newPos.ry() = m_handle->slideArea().height() - handleSize.height();
        if(newPos.y() < 0)
            newPos.ry() = 0;
    }


    else {
        newPos.ry() = handleOriginPos.ry();   // allow only movement in horizontal axis
        if(newHandleOtherPos.x() > m_handle->slideArea().width())
            newPos.rx() = m_handle->slideArea().width() - handleSize.width();
        else if(newPos.x() < 0)
            newPos.rx() = 0;
    }

    m_handle->setPos(newPos);
}

int ScrollBar::thickness() const
{
    return m_thickness;
}

QColor ScrollBar::color() const
{
    return m_color;
}

QColor ScrollBar::handleColor() const
{
    return m_handleColor;
}

qreal ScrollBar::sizeRatio() const
{
    return m_sizeRatio;
}

void ScrollBar::setThickness(int thickness)
{
    if (m_thickness == thickness)
        return;

    m_thickness = thickness;
    emit thicknessChanged(m_thickness);
}

void ScrollBar::setColor(const QColor& color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(m_color);
}

void ScrollBar::setHandleColor(const QColor& handleColor)
{
    if (m_handleColor == handleColor)
        return;

    m_handleColor = handleColor;
    emit handleColorChanged(m_handleColor);
}

void ScrollBar::setSizeRatio(qreal sizeRation)
{
    if (qFuzzyCompare(m_sizeRatio, sizeRation))
        return;

    m_sizeRatio = sizeRation;
    emit sizeRatioChanged(m_sizeRatio);
}

void ScrollBarHandle::setSlideArea(QSize slideArea)
{
    m_slideArea = slideArea;
}

ScrollBarHandle::ScrollBarHandle(Qt::Orientation orientation, QGraphicsWidget* parent):
    QGraphicsWidget(parent)
{
    m_orientation = orientation;

    connect(this, &ScrollBarHandle::colorChanged, [this] { this->update(); });
    connect(this, &ScrollBarHandle::geometryChanged, this, &ScrollBarHandle::calculateRelativePos);
}

void ScrollBarHandle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setBrush(m_color);
    painter->setPen(QColor(Qt::transparent));
    painter->drawRect(this->boundingRect());
    painter->restore();
}

QSize ScrollBarHandle::slideArea() const
{
    return m_slideArea;
}

QColor ScrollBarHandle::color() const
{
    return m_color;
}

qreal ScrollBarHandle::relativePos() const
{
    return m_relativePos;
}

void ScrollBarHandle::calculateRelativePos()
{
    m_relativePos = 0;
    if(m_orientation == Qt::Vertical) {
        if(qRound(this->size().height()) != m_slideArea.height())
            m_relativePos = this->y() / (m_slideArea.height() - this->size().height());
    }

    else {
        if(qRound(this->size().width()) != m_slideArea.width())
            m_relativePos = this->x() / (m_slideArea.width() - this->size().width());
    }

    emit this->relativePosChanged(m_relativePos);
}

void ScrollBarHandle::setColor(const QColor& color)
{
    if(color == m_color)
        return;
    m_color = color;
    emit colorChanged(color);
}
