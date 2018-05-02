#include "toolbar.h"
#include <QGraphicsAnchorLayout>
#include <QGraphicsLinearLayout>
#include <QPainter>

ToolBar::ToolBar(QGraphicsItem* parent): QGraphicsWidget (parent)
{
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

    auto mainLayout = new QGraphicsAnchorLayout{this};
    auto layout = new QGraphicsLinearLayout;
    auto subLayout = new QGraphicsLinearLayout;

    mainLayout->setContentsMargins(0, 0, 0, 0);
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

    this->setMinimumWidth(580);
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

void ToolBar::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();
    painter->setPen(QColor(Qt::transparent));
    painter->setBrush(QColor("#c6c5c5"));
    painter->drawRect(this->boundingRect());

    QPolygonF polygon;
    const QSizeF size = this->size();
    polygon << QPointF{size.width(), 0}
            << QPointF{size.width(), size.height()}
            << QPointF{size.width() / 1.40 - size.height(), size.height()}
            << QPointF{size.width() / 1.40, 0}
            << QPointF{size.width(), 0};

    painter->setBrush(QColor("#dbdbda"));
    painter->drawPolygon(polygon);
    painter->restore();
}
