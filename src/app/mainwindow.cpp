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

//MainWindow::MainWindow(QWidget *parent)
//    : QWidget(parent)
//{

//    /*PortView* portView = new PortView(this);
//    portView->move(100, 100);
//    m_portRegister->registerPort(portView);
//    portView = new PortView(this);
//    portView->move(10, 10);
//    m_portRegister->registerPort(portView);*/

//    this->resize(800, 500);
//}

//void MainWindow::mouseMoveEvent(QMouseEvent* event)
//{
//    /*PortView* port = m_portRegister->attachedPort(event->pos());
//    if(port != nullptr) {
//        qDebug() << port->geometry();
//    }*/
//}

AppWindow::AppWindow(QGraphicsWidget* parent): QGraphicsWidget{parent}
{
    m_blockSelection = new BlocksSelection{this};
    m_blockSelection->setMaximumWidth(195);
    m_blockSelection->setMinimumWidth(m_blockSelection->maximumWidth());

    m_blockCanvas = new BlockCanvas{this};


    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addCornerAnchors(layout, Qt::TopLeftCorner, m_blockSelection, Qt::TopLeftCorner);
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
