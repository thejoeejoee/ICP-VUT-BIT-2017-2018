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

    private:
        QString m_prevText;
        QRegularExpression m_validator;
        QColor m_currentBorderColor;
        QColor m_validBorderColor;
        QColor m_invalidBorderColor;
        bool m_valid;

        QVariantAnimation* m_borderColorAnimation;

    public:
        TextEdit(QGraphicsItem* parent = nullptr);
        TextEdit(const QString& text, QGraphicsItem* parent = nullptr);

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;

        QColor validBorderColor() const;
        QColor invalidBorderColor() const;
        bool valid() const;

    public slots:
        void setValidator(const QRegularExpression& validator);
        void setValidBorderColor(QColor validBorderColor);
        void setInvalidBorderColor(QColor invalidBorderColor);

    private slots:
        void validate();

    signals:
        void validBorderColorChanged(QColor validBorderColor);
        void invalidBorderColorChanged(QColor invalidBorderColor);

};

#endif // TEXTEDIT_H
