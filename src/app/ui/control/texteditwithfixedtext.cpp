#include "texteditwithfixedtext.h"

#include <QPainter>
#include <QTextDocument>

TextEditWithFixedText::TextEditWithFixedText(QGraphicsItem* parent): QGraphicsWidget (parent)
{
    m_textEdit = new TextEdit{this};
    m_textEdit->setDrawBorders(false);
    m_fixedText = new QGraphicsTextItem{this};
    m_fixedText->setTextInteractionFlags(Qt::TextSelectableByMouse);

    connect(this, &TextEditWithFixedText::fontChanged, m_textEdit, &TextEdit::setFont);
    connect(this, &TextEditWithFixedText::fontChanged, m_fixedText, &QGraphicsTextItem::setFont);
    connect(m_textEdit, &TextEdit::currentBorderColorChanged, [this]() { this->update(); });
    connect(m_textEdit, &TextEdit::contentChanged, this, &TextEditWithFixedText::resizeToContent);
    connect(m_fixedText->document(), &QTextDocument::contentsChanged,
            this, &TextEditWithFixedText::resizeToContent);
}

void TextEditWithFixedText::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();
    painter->setPen(m_textEdit->currentBorderColor());
    painter->drawRect(this->boundingRect());
    painter->restore();
}

bool TextEditWithFixedText::valid() const
{
    return m_textEdit->valid();
}

QColor TextEditWithFixedText::validBorderColor() const
{
    return m_textEdit->validBorderColor();
}

QColor TextEditWithFixedText::invalidBorderColor() const
{
    return m_textEdit->invalidBorderColor();
}

QFont TextEditWithFixedText::font() const
{
    return m_font;
}

QString TextEditWithFixedText::toPlainText() const
{
    return m_textEdit->toPlainText();
}

void TextEditWithFixedText::resizeToContent()
{
    m_textEdit->setX(m_fixedText->boundingRect().size().width());
    const QRectF contentRect = m_fixedText->boundingRect() |
                               m_textEdit->boundingRect().translated(m_textEdit->pos());

    this->resize(contentRect.size());
}

void TextEditWithFixedText::setTextColor(const QColor& color)
{
    m_textEdit->setTextColor(color);
}

void TextEditWithFixedText::setValidator(const QRegularExpression& validator)
{
    m_textEdit->setValidator(validator);
}

void TextEditWithFixedText::setPlainText(const QString& str)
{
    m_textEdit->setPlainText(str);
}

void TextEditWithFixedText::setFixedText(const QString& str)
{
    m_fixedText->setPlainText(str);
}

void TextEditWithFixedText::setFixedTextColor(const QColor& color)
{
    m_fixedText->setDefaultTextColor(color);
}

void TextEditWithFixedText::setTextInteractionFlags(Qt::TextInteractionFlags flags)
{
    m_textEdit->setTextInteractionFlags(flags);
    if(flags == Qt::NoTextInteraction)
        m_fixedText->setTextInteractionFlags(Qt::NoTextInteraction);
}

void TextEditWithFixedText::setValidBorderColor(QColor validBorderColor)
{
    m_textEdit->setValidBorderColor(validBorderColor);
}

void TextEditWithFixedText::setInvalidBorderColor(QColor invalidBorderColor)
{
    m_textEdit->setInvalidBorderColor(invalidBorderColor);
}

void TextEditWithFixedText::setFont(const QFont& font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(m_font);
}
