#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QGraphicsTextItem>
#include <QRegularExpression>
#include <QVariantAnimation>


/**
 * Interactive widget for editable text.
 */
class TextEdit : public QGraphicsTextItem {
    Q_OBJECT
        Q_PROPERTY(QColor validBorderColor
                           READ
                                   validBorderColor
                           WRITE
                                   setValidBorderColor
                           NOTIFY
                           validBorderColorChanged)
        Q_PROPERTY(QColor invalidBorderColor
                           READ
                                   invalidBorderColor
                           WRITE
                                   setInvalidBorderColor
                           NOTIFY
                           invalidBorderColorChanged)
        Q_PROPERTY(QColor
                           textColor
                           READ
                           textColor
                           WRITE
                           setTextColor
                           NOTIFY
                           textColorChanged
        )

    private:
        QString m_prevText;
        QRegularExpression m_validator;
        QColor m_currentBorderColor;
        QColor m_validBorderColor;
        QColor m_invalidBorderColor;
        bool m_valid;
        bool m_drawBorders = true;
        QColor m_textColor;
        QColor m_currentTextColor;
        bool m_oneLineMode = false;

        QVariantAnimation* m_borderColorAnimation;
        QVariantAnimation* m_textColorAnimation;

    public:
        explicit TextEdit(QGraphicsItem* parent = nullptr);
        /**
         * Create edit text with given text.
         * @param text text to set
         * @param parent qt parent
         */
        explicit TextEdit(const QString &text, QGraphicsItem* parent = nullptr);

        /**
         * Paints widget.
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
         * Getter for current border color.
         * @return color
         */
        QColor currentBorderColor() const;
        /**
         * Getter for validity state.
         * @return state
         */
        bool valid() const;
        /**
         * Getter for text color.
         * @return color
         */
        QColor textColor() const;

    private slots:
        // TODO doc
        void removeNewLines();

    public slots:
        /**
         * Sets new validator.
         * @param validator new validator.
         */
        void setValidator(const QRegularExpression &validator);
        /**
         * Sets new validator.
         * @param validBorderColor new validator.
         */
        void setValidBorderColor(QColor validBorderColor);
        /**
         * Sets new validator.
         * @param invalidBorderColor new validator.
         */
        void setInvalidBorderColor(QColor invalidBorderColor);
        /**
         * Sets new state, if borders should be drawn.
         * @param v new validator.
         */
        void setDrawBorders(bool v);
        /**
         * Sets new text color.
         * @param textColor new text color.
         */
        void setTextColor(QColor textColor);

        // TODO doc
        void setOneLineMode(bool v);


    private slots:
        void validate();

    signals:
        /**
         * On change valid color of border.
         * @param validBorderColor new color
         */
        void validBorderColorChanged(QColor validBorderColor);
        /**
         * On change invalid color of border.
         * @param invalidBorderColor new color
         */
        void invalidBorderColorChanged(QColor invalidBorderColor);
        /**
         * On change current color of border.
         * @param borderColor new color
         */
        void currentBorderColorChanged(const QColor &borderColor);
        /**
         * On change content.
         */
        void contentChanged();
        /**
         * On change color of text.
         * @param textColor new color
         */
        void textColorChanged(QColor textColor);
};

#endif // TEXTEDIT_H
