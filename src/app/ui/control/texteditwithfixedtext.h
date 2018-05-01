#ifndef TEXTEDITWITHFIXEDTEXT_H
#define TEXTEDITWITHFIXEDTEXT_H

#include <QGraphicsWidget>
#include <QRegularExpression>
#include "textedit.h"
#include <QGraphicsTextItem>


class TextEditWithFixedText : public QGraphicsWidget
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)

    private:
        TextEdit* m_textEdit;
        QGraphicsTextItem* m_fixedText;
        QFont m_font;

    public:
        TextEditWithFixedText(QGraphicsItem* parent = nullptr);
        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;

        bool valid() const;
        QColor validBorderColor() const;
        QColor invalidBorderColor() const;
        QFont font() const;
        QString fixedToPlainText() const;
        QString toPlainText() const;

    private slots:
        void resizeToContent();

    public slots:
        void setTextColor(const QColor& color);
        void setValidator(const QRegularExpression& validator);
        void setPlainText(const QString& str);
        void setFixedText(const QString& str);
        void setFixedTextColor(const QColor& color);
        void setTextInteractionFlags(Qt::TextInteractionFlags flags);
        void setValidBorderColor(QColor validBorderColor);
        void setInvalidBorderColor(QColor invalidBorderColor);
        void setFont(const QFont& font);

    signals:
        void fontChanged(const QFont& font);
};

#endif // TEXTEDITWITHFIXEDTEXT_H
