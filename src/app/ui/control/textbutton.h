#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "clickable.h"


class TextButton : public Clickable
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

    private:
        QFont m_font;
        QColor m_color;
        QString m_text;
        bool m_hovered = false;;

    public:
        TextButton(const QString& text, QGraphicsItem* parent = nullptr);

        void paint(
                QPainter * painter,
                const QStyleOptionGraphicsItem * option,
                QWidget * widget = nullptr) override;

    public:
        QFont font() const;
        QColor color() const;

    private slots:
        void resizeToText();

    public slots:
        void setFont(QFont font);
        void setColor(QColor color);

    signals:
        void fontChanged(QFont font);
        void colorChanged(QColor color);
};

#endif // TEXTBUTTON_H
