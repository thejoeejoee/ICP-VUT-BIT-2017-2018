/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "toolbar.h"
#include <QGraphicsAnchorLayout>
#include <QGraphicsLinearLayout>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

ToolBar::ToolBar(QGraphicsItem* parent) : QGraphicsWidget(parent) {
    m_newButton = new TextButton{tr("New"), this};
    m_openButton = new TextButton{tr("Open"), this};
    m_saveButton = new TextButton{tr("Save"), this};
    m_saveAsButton = new TextButton{tr("Save As"), this};

    m_newButton->setFont(QFont{"Montserrat", 18});
    m_openButton->setFont(m_newButton->font());
    m_saveButton->setFont(m_newButton->font());
    m_saveAsButton->setFont(m_newButton->font());

    m_runButton = new IconButton{":/res/image/play_icon.svg", this};
    m_debugButton = new IconButton{":/res/image/play_iter_icon.svg", this};
    m_stopButton = new IconButton{":/res/image/stop_icon.svg", this};
    m_bugRenderer.load(QString{":/res/image/bug_icon.svg"});

    auto mainLayout = new QGraphicsAnchorLayout{this};
    auto layout = new QGraphicsLinearLayout;
    auto subLayout = new QGraphicsLinearLayout;

    mainLayout->setContentsMargins(0, 0, 45, 0);
    mainLayout->setSpacing(40);
    layout->setContentsMargins(10, 0, 5, 0);
    subLayout->setContentsMargins(0, 0, 0, 0);

    layout->addItem(m_newButton);
    layout->addItem(m_openButton);
    layout->addItem(m_saveButton);
    layout->addItem(m_saveAsButton);
    layout->addItem(subLayout);

    subLayout->addItem(m_runButton);
    subLayout->addItem(m_debugButton);
    subLayout->addItem(m_stopButton);

    mainLayout->addCornerAnchors(mainLayout, Qt::TopLeftCorner, layout, Qt::TopLeftCorner);
    mainLayout->addCornerAnchors(mainLayout, Qt::BottomLeftCorner, layout, Qt::BottomLeftCorner);

    mainLayout->addCornerAnchors(mainLayout, Qt::TopRightCorner, subLayout, Qt::TopRightCorner);
    mainLayout->addCornerAnchors(mainLayout, Qt::BottomRightCorner,
                                 subLayout, Qt::BottomRightCorner);

    this->setMinimumWidth(580 + 45);
    this->setMinimumHeight(45);
    this->setMaximumHeight(45);

    connect(m_newButton, &Clickable::clicked, this, &ToolBar::newFile);
    connect(m_saveButton, &Clickable::clicked, this, &ToolBar::saveFile);
    connect(m_saveAsButton, &Clickable::clicked, this, &ToolBar::saveAsFile);
    connect(m_openButton, &Clickable::clicked, this, &ToolBar::openFile);

    connect(m_runButton, &Clickable::clicked, this, &ToolBar::evaluate);
    connect(m_debugButton, &Clickable::clicked, this, &ToolBar::debug);
    connect(m_stopButton, &Clickable::clicked, this, &ToolBar::stop);
}

void ToolBar::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->save();
    painter->setPen(QColor(Qt::transparent));
    painter->setBrush(QColor("#c6c5c5"));
    const QSizeF size = this->size();
    painter->drawRect(this->boundingRect().adjusted(0, 0, -size.height(), 0));

    QPolygonF polygon;
    polygon << QPointF{size.width() - size.height(), 0}
            << QPointF{size.width() - size.height(), size.height()}
            << QPointF{size.width() / 1.40 - size.height() * 2, size.height()}
            << QPointF{size.width() / 1.40 - size.height(), 0}
            << QPointF{size.width() - size.height(), 0};

    painter->setBrush(QColor("#dbdbda"));
    painter->drawPolygon(polygon);
    if (m_debugIconVisible) {
        painter->setPen(QColor(Qt::transparent));
        painter->setBrush(QColor{"#0f81bc"});
        const QRectF iconRect = QRectF(size.width() - size.height(),
                                       0,
                                       size.height(),
                                       size.height());
        painter->drawRect(iconRect);
        m_bugRenderer.render(painter, iconRect.adjusted(5, 5, -5, -5));
    }

    painter->restore();
}

void ToolBar::setDebugIconVisiblity(bool v) {
    m_debugIconVisible = v;
    this->update();
}
