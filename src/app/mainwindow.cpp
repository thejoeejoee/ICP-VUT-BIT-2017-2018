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
    m_warning = new WarningPopUp{m_blockCanvas};
    m_warning->resize(300, 40);

    m_toolbar = new ToolBar{this};
    connect(m_toolbar, &ToolBar::run, m_blockCanvas, &BlockCanvas::evaluate);
    connect(m_toolbar, &ToolBar::debug, m_blockCanvas, &BlockCanvas::debug);
    connect(m_toolbar, &ToolBar::stop, m_blockCanvas, &BlockCanvas::stopDebug);
    connect(m_blockCanvas, &BlockCanvas::error, [this](const QString& msg) {
        m_warning->popUp(msg, 2);
    });


    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addCornerAnchors(layout, Qt::TopLeftCorner, m_toolbar, Qt::TopLeftCorner);

    layout->addCornerAnchors(m_toolbar, Qt::BottomLeftCorner, m_blockSelection, Qt::TopLeftCorner);
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
