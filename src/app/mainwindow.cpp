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
    m_blockSelection = new BlocksSelection(this);
    m_blockSelection->setPos(50, 20);
    m_blockSelection->setPreferredWidth(100);
    m_blockSelection->setPreferredHeight(120);

    auto b = Block::createNew(AddBlock::staticClassId(), this);
    b->view()->moveBy(300, 100);
    /*auto t = new TextEdit(this);
    t->setFont(QFont("Montserrat Light"));

    t->setInvalidBorderColor(QColor("#d10000"));
    t->setValidBorderColor(QColor("#666666"));
    t->setPlainText("0");
    t->moveBy(40, 40);
    t->setValidator(QRegularExpression("^\\d+\\.?(\\d{1,4})?$"));*/

    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    //layout->addCornerAnchors(layout, Qt::TopLeftCorner, m_blockSelection, Qt::TopLeftCorner);
}

void AppWindow::resizeWindow(QSize size)
{
    this->resize(size);
}
