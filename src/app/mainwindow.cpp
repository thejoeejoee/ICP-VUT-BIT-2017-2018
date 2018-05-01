#include "mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QGraphicsAnchorLayout>
#include "ui/blockportview.h"
#include "core/blocks/addblock.h"
#include <QGraphicsScene>
#include <app/ui/control/textedit.h>

// TODO remove portregister

AppWindow::AppWindow(QGraphicsWidget* parent): QGraphicsWidget{parent}
{
    m_blockSelection = new BlocksSelection{this};
    m_blockSelection->setMaximumWidth(195);
    m_blockSelection->setMinimumWidth(m_blockSelection->maximumWidth());

    m_blockCanvas = new BlockCanvas{this};

    m_button = new IconButton{this};
    m_button->setMinimumHeight(20);
    m_button->setMaximumHeight(20);
    connect(m_button, &IconButton::clicked, m_blockCanvas, &BlockCanvas::evaluate);



    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addCornerAnchors(layout, Qt::TopLeftCorner, m_button, Qt::TopLeftCorner);
    layout->addCornerAnchors(layout, Qt::TopRightCorner, m_button, Qt::TopRightCorner);

    layout->addCornerAnchors(m_button, Qt::BottomLeftCorner, m_blockSelection, Qt::TopLeftCorner);
    layout->addCornerAnchors(layout, Qt::BottomLeftCorner,
                             m_blockSelection, Qt::BottomLeftCorner);

    layout->addCornerAnchors(m_blockSelection, Qt::TopRightCorner,
                             m_blockCanvas, Qt::TopLeftCorner);
    layout->addCornerAnchors(m_blockCanvas, Qt::BottomRightCorner,
                             layout, Qt::BottomRightCorner);
}

void AppWindow::resizeWindow(QSize size)
{
    this->resize(size);
}
