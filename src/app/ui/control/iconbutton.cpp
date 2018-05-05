#include "iconbutton.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

IconButton::IconButton(const QString& imagePath, QGraphicsItem* parent): Clickable (parent)
{
    m_imageRenderer.load(imagePath);
    connect(this, &IconButton::imagePathChanged, [this](const QString& path) {
        m_imageRenderer.load(path);
        this->update();
    });
}

IconButton::IconButton(QGraphicsItem* parent): IconButton("", parent) {}

void IconButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();
    painter->setClipRect(option->exposedRect);
    Clickable::paint(painter, option, widget);

    const double height = this->boundingRect().height();
    const double width = this->boundingRect().width();
    m_imageRenderer.render(painter, QRectF((width - height) / 2., 0, height, height));

    painter->restore();
}

QString IconButton::imagePath() const
{
    return m_imagePath;
}

void IconButton::setImagePath(const QString& imagePath)
{
    if (m_imagePath == imagePath)
        return;

    m_imagePath = imagePath;
    emit imagePathChanged(m_imagePath);
}
