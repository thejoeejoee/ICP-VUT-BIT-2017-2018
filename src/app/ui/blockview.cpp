#include "blockview.h"

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QPainter>
#include <QMimeData>
#include <QGraphicsScene>
#include <QWidget>
#include <QJsonDocument>
#include <app/core/block.h>
#include <app/core/blockmanager.h>

const QSize BlockView::s_blockSize = QSize{80 + 2 * BlockView::s_portsOffset, 80};

BlockView::BlockView(Block* block, QGraphicsItem* parent) : QGraphicsWidget(parent)
{
    m_data = block;
    this->setMinimumSize(BlockView::s_blockSize.width(), BlockView::s_blockSize.height());
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setFlags(ItemIsFocusable | QGraphicsItem::ItemSendsScenePositionChanges);

    connect(this, &BlockView::geometryChanged, this, &BlockView::repositionPorts);
    connect(this, &BlockView::outputPortVisibleChanged, this, &BlockView::resizeBoundingBox);
    connect(this, &BlockView::inputPortsVisibleChanged, this, &BlockView::resizeBoundingBox);
}

void BlockView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(!m_copyable) {
        QGraphicsWidget::mousePressEvent(event);
        return;
    }

    this->setCursor(Qt::ClosedHandCursor);
}

void BlockView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(!m_copyable) {
        QGraphicsWidget::mouseMoveEvent(event);
        return;
    }

    auto drag = new QDrag{event->widget()};
    auto mime = new QMimeData;
    QJsonDocument doc{BlockManager::blockToJson(m_data)};
    QByteArray data;
    QDataStream dataStream{&data, QIODevice::WriteOnly};

    dataStream << (event->pos().toPoint() + QPoint(BlockView::portOffset(), 0))
               << doc.toJson();
    mime->setData(BlockManager::blockMimeType(), data);
    drag->setMimeData(mime);

    drag->setPixmap(this->pixmap());
    drag->setHotSpot(event->pos().toPoint());

    drag->exec();
    this->setCursor(Qt::OpenHandCursor);
}

void BlockView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(!m_copyable) {
        QGraphicsWidget::mouseReleaseEvent(event);
        return;
    }

    this->setCursor(Qt::OpenHandCursor);
}

void BlockView::keyPressEvent(QKeyEvent* event)
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

    QGraphicsWidget::keyPressEvent(event);
}

QVariant BlockView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if(change == QGraphicsItem::ItemSelectedChange) {
        this->update();
        if(value == true)
            this->setFocus();
    }

    else if(change == QGraphicsItem::ItemPositionChange) {
        const QPointF newPos = value.toPointF();
        if(newPos.x() < 0 || newPos.y() < 0)
            return QPointF{qMax(newPos.x(), 0.), qMax(newPos.y(), 0.)};
    }

    return QGraphicsWidget::itemChange(change, value);
}

void BlockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    const QRectF blockRect = this->boundingRect().adjusted(
        BlockView::s_portsOffset * static_cast<int>(m_inputPortsVisible), 0,
        -BlockView::s_portsOffset * static_cast<int>(m_outputPortVisible), 0
    );
    const double halfHeight = blockRect.height() / 2.;
    constexpr int margin = BlockView::s_portsMargin;

    // Draw background
    painter->setPen(QColor(Qt::transparent));
    if(this->isSelected())
        painter->setBrush(QColor("#0f81bc"));
    else
        painter->setBrush(m_backgroundColor);
    painter->drawRect(blockRect);

    // draw port connection lines

    painter->setPen(QPen(m_backgroundColor, 3, Qt::SolidLine, Qt::FlatCap));
    if(m_outputPortVisible) {
        painter->drawLine(QLineF{
                              blockRect.width() + BlockView::s_portsOffset, halfHeight,
                              blockRect.width() +2* BlockView::s_portsOffset, halfHeight
                          });
    }

    if(m_inputPortsVisible && m_data->inputPorts().length()) {
        const double portHeight = m_data->inputPorts().at(0)->view()->size().height();
        const int portsCount = m_data->inputPorts().length();
        const double availableHeight = this->size().height() - 2 * margin - portHeight;

        if(portsCount == 1)
            painter->drawLine(QLineF{0, halfHeight, BlockView::s_portsOffset, halfHeight});

        else {
            for(int i = 0; i < m_data->inputPorts().length(); i++) {
                BlockPortView* inputPortView = m_data->inputPorts().at(0)->view();
                const double yPos = inputPortView->size().height() / 2. +
                                    i * (availableHeight / (portsCount - 1)) + margin;
                painter->drawLine(QLineF{0, yPos, BlockView::s_portsOffset, yPos});
            }
        }
    }

    // draw icon
    m_imageRenderer.render(painter, blockRect);
    painter->restore();
}

int BlockView::portOffset()
{
    return BlockView::s_portsOffset;
}

Block* BlockView::blockData() const
{
    return m_data;
}

QPixmap BlockView::pixmap()
{
    QPixmap pixmap(this->size().toSize());
    QPainter painter(&pixmap);

    painter.setBrush(m_backgroundColor);
    painter.drawRect(this->rect());

    m_imageRenderer.render(&painter, this->boundingRect());

    return pixmap;
}

void BlockView::repositionPorts()
{
    if(!m_data->inputPorts().length() || m_data->outputPort() == nullptr)
        return;

    const double portHeight = m_data->inputPorts().at(0)->view()->size().height();
    constexpr int margin = BlockView::s_portsMargin;
    const int portsCount = m_data->inputPorts().length();
    const double availableHeight = this->size().height() - 2 * margin - portHeight;

    BlockPortView* outputPortView = m_data->outputPort()->view();
    outputPortView->setPos(
                this->size().width(),
                (this->size().height() - outputPortView->size().height()) / 2.);

    if(portsCount == 1) {
        BlockPortView* inputPortView = m_data->inputPorts().at(0)->view();
        inputPortView->setPos(
                    -inputPortView->size().width(),
                    (this->size().height() - inputPortView->size().height()) / 2.);
        return;
    }

    for(int i = 0; i < m_data->inputPorts().length(); i++) {
        BlockPortView* portView = m_data->inputPorts().at(i)->view();
        portView->setPos(-portView->size().width(),
                         i * (availableHeight / (portsCount - 1)) + margin);
    }
}

void BlockView::resizeBoundingBox()
{
    const int count = static_cast<int>(m_outputPortVisible) +
                      static_cast<int>(m_inputPortsVisible);

    this->setMinimumSize(BlockView::s_blockSize.height() + count * BlockView::s_portsOffset,
                         BlockView::s_blockSize.height());
}

void BlockView::setCopyable(bool copyable)
{
    m_copyable = copyable;
}

void BlockView::setOutputVisible(bool visible, bool animate)
{
    if(visible)
        m_data->outputPort()->view()->animateShow(animate);
    else
        m_data->outputPort()->view()->animateHide(animate);
    if(m_outputPortVisible == visible)
        return;
    m_outputPortVisible = visible;
    emit this->outputPortVisibleChanged();
}

void BlockView::setInputsVisible(bool visible, bool animate)
{
    if(visible) {
        for(auto port: m_data->inputPorts())
            port->view()->animateShow(animate);
    }

    else {
        for(auto port: m_data->inputPorts())
            port->view()->animateHide(animate);
    }
    if(m_inputPortsVisible == visible)
        return;
    m_inputPortsVisible = visible;
    emit this->inputPortsVisibleChanged();
}

void BlockView::setSingleInputVisible(int index, bool visible, bool animate)
{
    if(index >= m_data->inputPorts().length())
        return;

    if(visible)
        m_data->inputPorts().at(index)->view()->animateShow(animate);
    else
        m_data->inputPorts().at(index)->view()->animateHide(animate);
}

void BlockView::initPortsViews()
{
    this->repositionPorts();
    if(m_data->outputPort() != nullptr) {
        connect(m_data->outputPort()->view(),
                &BlockPortView::geometryChanged, this, &BlockView::repositionPorts);
    }
}

void BlockView::setSvgImage(const QString& image)
{
    m_imageRenderer.load(image);
    this->update();
}

void BlockView::setBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    this->update();
}

void BlockView::setBackgroundSelectionColor(const QColor& color)
{
    m_backgroundSelectionColor = color;
}
