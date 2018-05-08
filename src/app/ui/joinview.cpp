/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "joinview.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <app/core/block.h>
#include <app/core/blockmanager.h>
#include <QStyleOptionGraphicsItem>

JoinView::JoinView(Identifier dataId, QGraphicsItem* parent)
        : QObject{}, QGraphicsLineItem(parent) {
    m_dataId = dataId;
    m_pen = QPen{QColor{"#8c8c8c"}, 3};
    m_opacityAnimation = new QVariantAnimation(this);
    m_opacityAnimation->setDuration(150);

    this->setPen(m_pen);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(ItemIsFocusable);
    this->setAcceptHoverEvents(true);

    connect(m_opacityAnimation, &QVariantAnimation::valueChanged, [this](const QVariant &v) {
        m_currentOpacity = v.toDouble();
        this->update();
    });
}

void JoinView::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Delete) {
        for (auto item: this->scene()->selectedItems()) {
            auto blockView = dynamic_cast<BlockView*>(item);
            auto joinView = dynamic_cast<JoinView*>(item);

            if (blockView != nullptr)
                    emit blockView->deleteRequest(blockView->blockData()->id());
            else if (joinView != nullptr)
                    emit joinView->deleteRequest(joinView->dataId());
        }
    }

    QGraphicsLineItem::keyPressEvent(event);
}

void JoinView::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    if (!this->shape().contains(e->pos()))
        e->ignore();
}

void JoinView::hoverMoveEvent(QGraphicsSceneHoverEvent* e) {
    bool newVal = this->shape().contains(e->pos());
    if (newVal == m_hovered)
        return;
    m_hovered = newVal;
    m_opacityAnimation->setStartValue(m_currentOpacity);
    m_opacityAnimation->setEndValue((m_hovered) ? 1. : 0.);
    m_opacityAnimation->start();
}

void JoinView::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    Q_UNUSED(e);

    m_hovered = false;
    m_opacityAnimation->setStartValue(m_currentOpacity);
    m_opacityAnimation->setEndValue(0.);
    m_opacityAnimation->start();
}

QVariant JoinView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemSelectedChange) {
        if (value == true) {
            this->setFocus();
            m_pen.setColor(QColor{"#0f81bc"});
        } else
            m_pen.setColor(QColor{"#8c8c8c"});
        this->setPen(m_pen);
        this->update();
    }

    return QGraphicsLineItem::itemChange(change, value);
}

QPainterPath JoinView::nonStrokedShape() const {
    QPainterPath path;

    QPointF p1 = this->line().p1();
    QPointF p2 = this->line().p2();

    path.moveTo(p1);
    double startX = qMin(p1.x(), p2.x());
    const QPointF c1{startX + qAbs((p1.x() - p2.x()) / 2.), p1.y()};
    const QPointF c2{startX + qAbs((p1.x() - p2.x()) / 2.), p2.y()};

    path.cubicTo(c1, c2, p2);

    return path;
}

void JoinView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->save();
    painter->setPen(this->pen());
    painter->drawPath(this->nonStrokedShape());

    if (m_blockManager != nullptr && m_blockManager->join(m_dataId) != nullptr) {
        painter->setOpacity(m_currentOpacity);
        Join* join = m_blockManager->join(m_dataId);
        const QString value = m_blockManager->block(join->fromBlock())
                ->outputPort()->view()->rawValue(true);
        painter->setFont(QFont("Montserrat Light", 12));

        QFontMetrics fm{painter->font()};
        painter->setBrush(QColor(Qt::white));
        painter->setPen(QPen("#969696"));
        painter->drawRect(fm.boundingRect(this->boundingRect().toRect(), Qt::AlignCenter, value)
                                  .adjusted(-5, -5, 5, 5));

        painter->setPen(QPen(QColor(Qt::black)));
        painter->drawText(this->boundingRect(), value, QTextOption(Qt::AlignCenter));
    }

    painter->restore();
}

QPainterPath JoinView::shape() const {
    QPainterPathStroker stroker;
    stroker.setWidth(20);

    return stroker.createStroke(this->nonStrokedShape());
}

Identifier JoinView::dataId() const {
    return m_dataId;
}

void JoinView::setBlockManager(BlockManager* m) {
    m_blockManager = m;
}

void JoinView::adjustJoin() {
    if (m_blockManager == nullptr)
        return;

    Join* data = m_blockManager->join(m_dataId);
    BlockPortView* fromPortView = m_blockManager->block(data->fromBlock())->outputPort()->view();
    BlockPortView* toPortView = m_blockManager->block(data->toBlock())->inputPorts()
            .at(data->toPort())->view();

    QPointF start = fromPortView->mapToItem(this->parentItem(), QPointF(
            0,
            fromPortView->size().height() / 2.));
    QPointF end = toPortView->mapToItem(this->parentItem(), QPointF(
            toPortView->size().width(),
            toPortView->size().height() / 2.));
    this->setLine(QLineF(start, end));
    this->update();
}
