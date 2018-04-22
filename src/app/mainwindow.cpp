#include "mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QGraphicsAnchorLayout>
#include "ui/portview.h"
#include "core/blocks/addblock.h"
#include <QGraphicsScene>

//MainWindow::MainWindow(QWidget *parent)
//    : QWidget(parent)
//{
//    m_blocksSelection = new BlocksSelection(this);
//    m_blocksSelection->setMaximumWidth(300);
//    m_portRegister = new PortRegister(this);
//    QHBoxLayout* layout = new QHBoxLayout(this);
//    layout->setMargin(0);

//    layout->addWidget(m_blocksSelection);

//    // TODO register blocks
//    m_blocksSelection->addItem(Block::createNew(AddBlock::staticClassId(), this)->view());
//    m_blocksSelection->addItem(Block::createNew(AddBlock::staticClassId(), this)->view());
//    m_blocksSelection->addSpacer();
////    for(int i = 0; i < 4; i++) {
////        break;
////        QPushButton* button = new QPushButton(QString("ahoj %1").arg(i));
////        m_blocksSelection->addItem(button);
////    }


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
    m_blockSelection = new BlocksSelection(this);
    m_blockSelection->setPos(50, 20);
    m_blockSelection->setPreferredWidth(80);
    m_blockSelection->setPreferredHeight(120);

    for(int i = 0; i < 3; i++) {
        m_blockSelection->addItem(Block::createNew("add_block", this)->view());
        m_blockSelection->addItem(Block::createNew("add_block", this)->view());
    }

    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    //layout->addCornerAnchors(layout, Qt::TopLeftCorner, m_blockSelection, Qt::TopLeftCorner);
}

void AppWindow::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    Q_UNUSED(e);
    qDebug() << m_blockSelection->geometry();
    qDebug() << m_blockSelection->contentsRect();
    qDebug() << m_blockSelection->layout()->geometry();
}

void AppWindow::resizeWindow(QSize size)
{
    this->resize(size);
}
