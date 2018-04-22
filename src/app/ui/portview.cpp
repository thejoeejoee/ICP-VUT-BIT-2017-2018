#include "portview.h"

#include <QPainter>

PortView::PortView(QWidget *parent) : QWidget(parent)
{
    this->resize(50, 50);
}

void PortView::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setBrush(Qt::red);
    painter.drawEllipse(this->rect());
}
