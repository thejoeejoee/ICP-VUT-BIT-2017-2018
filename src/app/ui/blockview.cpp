#include "blockview.h"

#include <QPainter>
#include <app/core/block.h>

BlockView::BlockView(Block* block, QGraphicsItem* parent) : QGraphicsWidget(parent)
{
    m_data = block;
    this->setMinimumSize(BlockView::s_blockSize, BlockView::s_blockSize);

    connect(this, &BlockView::geometryChanged, this, &BlockView::repositionPorts);
}

void BlockView::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    // TODO move somewhere
    QList<MappedDataValues> vals;
    for(auto port: m_data->ports())
        vals.append(port->value());
    m_data->outputPort()->setValue(m_data->evaluate(vals));

}

void BlockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    // TODO selection
    painter->setBrush(m_backgroundColor);
    painter->drawRect(this->rect());

    m_imageRenderer.render(painter, this->boundingRect());
    painter->restore();
}

Block* BlockView::blockData() const
{
    return m_data;
}

void BlockView::repositionPorts()
{
    if(!m_data->ports().length() || m_data->outputPort() == nullptr)
        return;

    const double portHeight = m_data->ports().at(0)->view()->size().height();
    constexpr int margin = BlockView::s_portsMargin;
    const int portsCount = m_data->ports().length();
    const double availableHeight = this->size().height() - 2 * margin - portHeight;

    for(int i = 0; i < m_data->ports().length(); i++) {
        BlockPortView* portView = m_data->ports().at(i)->view();
        portView->setPos(-portView->size().width() - BlockView::s_portsOffset,
                         i * (availableHeight / (portsCount - 1)) + margin);
    }

    BlockPortView* outputPortView = m_data->outputPort()->view();
    outputPortView->setPos(
                this->size().width() + BlockView::s_portsOffset,
                (this->size().height() - outputPortView->size().height()) / 2.);
}

void BlockView::setOutputVisible(bool visible, bool animate)
{
    if(visible)
        m_data->outputPort()->view()->animateShow(animate);
    else
        m_data->outputPort()->view()->animateHide(animate);

}

void BlockView::setInputsVisible(bool visible, bool animate)
{
    if(visible) {
        for(auto port: m_data->ports())
            port->view()->animateShow(animate);
    }

    else {
        for(auto port: m_data->ports())
            port->view()->animateHide(animate);
    }
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
