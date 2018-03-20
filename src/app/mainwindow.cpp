#include "mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::red));

    painter.drawRect(50, 50, 60, 60);


}
