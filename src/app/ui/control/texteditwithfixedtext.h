#ifndef TEXTEDITWITHFIXEDTEXT_H
#define TEXTEDITWITHFIXEDTEXT_H

#include <QGraphicsWidget>
#include <QRegularExpression>
#include "textedit.h"
#include <app/ui/control/plaintext.h>


/**
 * Editable text with fixed value.
 */
class TextEditWithFixedText : public QGraphicsWidget {
    Q_OBJECT
        Q_PROPERTY(QFont
                           font
                           READ
                           font
                           WRITE
                           setFont
                           NOTIFY
                           fontChanged
        )

    private:
        TextEdit* m_textEdit;
        PlainText* m_fixedText;
        QFont m_font;

    public:
        explicit TextEditWithFixedText(QGraphicsItem* parent = nullptr);
        /**
         * Paints field into widget.
         * @param painter painter
         * @param option style
         * @param widget qt parent
         */
        void paint(
                QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget
        ) override;

        /**
         * Is input valid?
         * @return state
         */
        bool valid() const;
        /**
         * Getter for valid border color.
         * @return color
         */
        QColor validBorderColor() const;

        /**
         * Getter for invalid border color.
         * @return color
         */
        QColor invalidBorderColor() const;
        /**
         * Returns font.
         * @return font
         */
        QFont font() const;
        /**
         * Returns fixed text as string.
         * @return string
         */
        QString fixedToPlainText() const;
        /**
         * Returns text as string.
         * @return string
         */
        QString toPlainText() const;

    private slots:
        void resizeToContent();
        // TODO doc
        void passFocus();

    public slots:
        /**
         * Sets new text color.
         * @param color new color
         */
        void setTextColor(const QColor &color);
        /**
         * Sets regex validator
         * @param validator regex validator
         */
        void setValidator(const QRegularExpression &validator);
        /**
         * Sets text to input.
         * @param str string
         */
        void setPlainText(const QString &str);
        /**
         * Sets fixed text.
         * @param str fixed text
         */
        void setFixedText(const QString &str);
        /**
         * Sets new color.
         * @param color fixed color
         */
        void setFixedTextColor(const QColor &color);
        /**
         * Sets interaction flags.
         * @param flags new flags
         */
        // TODO doc
        void setOneLineMode(bool v);
        void setTextInteractionFlags(Qt::TextInteractionFlags flags);
        /**
         * Set new color of valid
         * @param validBorderColor color
         */
        void setValidBorderColor(QColor validBorderColor);
        /**
         * Set new color of invalid
         * @param validBorderColor color
         */
        void setInvalidBorderColor(QColor invalidBorderColor);
        /**
         * Sets new font.
         * @param font new font
         */
        void setFont(const QFont &font);

    signals:
        /**
         * On font chnaged.
         * @param font new font
         */
        void fontChanged(const QFont &font);
};

#endif // TEXTEDITWITHFIXEDTEXT_H
