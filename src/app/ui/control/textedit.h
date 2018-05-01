#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QGraphicsTextItem>
#include <QRegularExpression>
#include <QVariantAnimation>


class TextEdit : public QGraphicsTextItem
{
        Q_OBJECT
        Q_PROPERTY(QColor validBorderColor READ validBorderColor WRITE setValidBorderColor NOTIFY validBorderColorChanged)
        Q_PROPERTY(QColor invalidBorderColor READ invalidBorderColor WRITE setInvalidBorderColor NOTIFY invalidBorderColorChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

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

        QVariantAnimation* m_borderColorAnimation;
        QVariantAnimation* m_textColorAnimation;

    public:
        TextEdit(QGraphicsItem* parent = nullptr);
        TextEdit(const QString& text, QGraphicsItem* parent = nullptr);

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;

        QColor validBorderColor() const;
        QColor invalidBorderColor() const;
        QColor currentBorderColor() const;
        bool valid() const;
        QColor textColor() const;

    public slots:
        void setValidator(const QRegularExpression& validator);
        void setValidBorderColor(QColor validBorderColor);
        void setInvalidBorderColor(QColor invalidBorderColor);
        void setDrawBorders(bool v);
        void setTextColor(QColor textColor);

    private slots:
        void validate();

    signals:
        void validBorderColorChanged(QColor validBorderColor);
        void invalidBorderColorChanged(QColor invalidBorderColor);
        void currentBorderColorChanged(const QColor& borderColor);
        void contentChanged();
        void textColorChanged(QColor textColor);
};

#endif // TEXTEDIT_H
