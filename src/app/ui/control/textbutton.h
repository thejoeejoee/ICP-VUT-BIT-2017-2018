/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "clickable.h"

/**
 * Button with text content.
 */
class TextButton : public Clickable {
    Q_OBJECT
        Q_PROPERTY(QFont font
                           READ font
                           WRITE setFont
                           NOTIFY
                           fontChanged)
        Q_PROPERTY(QColor color
                           READ color
                           WRITE setColor
                           NOTIFY
                           colorChanged)

    private:
        QFont m_font;
        QColor m_color;
        QString m_text;
        bool m_hovered = false;;

    public:
        /**
         * Create text button with given content.
         * @param text text for button
         * @param parent parent for button
         */
        explicit TextButton(const QString &text, QGraphicsItem* parent = nullptr);

        /**
         * Paints button via painter.
         * @param painter painter
         * @param option style
         * @param widget parent widget
         */
        void paint(
                QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget
        ) override;

    public:
        /**
         * Font getter.
         * @return font
         */
        QFont font() const;
        /**
         * Getter for color.
         * @return
         */
        QColor color() const;

    private slots:
        void resizeToText();

    public slots:
        /**
         * Sets new font
         * @param font  new font
         */
        void setFont(QFont font);
        /**
         * Sets new color
         * @param color new color
         */
        void setColor(QColor color);

    signals:
        /**
         * On font change.
         * @param font new font
         */
        void fontChanged(QFont font);
        /**
         * On color change.
         * @param font new color
         */
        void colorChanged(QColor color);
};

#endif // TEXTBUTTON_H
