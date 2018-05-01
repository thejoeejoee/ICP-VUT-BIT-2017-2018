#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include "clickable.h"
#include <QSvgRenderer>


class IconButton : public Clickable
{
        Q_OBJECT
        Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)

    private:
        QSvgRenderer m_imageRenderer;
        QString m_imagePath;

    public:
        IconButton(const QString& imagePath, QGraphicsItem* parent = nullptr);
        IconButton(QGraphicsItem* parent = nullptr);

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;

        QString imagePath() const;

    public slots:
        void setImagePath(const QString& imagePath);

    signals:
        void imagePathChanged(const QString& imagePath);
};

#endif // ICONBUTTON_H
