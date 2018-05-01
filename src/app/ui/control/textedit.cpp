#include "textedit.h"
#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QInputMethodEvent>
#include <QTextDocument>

TextEdit::TextEdit(QGraphicsItem* parent): TextEdit{"", parent} {}

TextEdit::TextEdit(const QString& text, QGraphicsItem* parent): QGraphicsTextItem{text, parent}
{
    m_textColorAnimation = new QVariantAnimation{this};
    m_textColorAnimation->setDuration(300);

    m_borderColorAnimation = new QVariantAnimation(this);
    m_borderColorAnimation->setDuration(300);
    m_valid = true;

    this->setTextInteractionFlags(Qt::TextEditorInteraction);

    connect(this, &TextEdit::textColorChanged, [this]() { this->update(); });
    connect(this->document(), &QTextDocument::contentsChanged, this, &TextEdit::contentChanged);
    connect(this->document(), &QTextDocument::contentsChanged, this, &TextEdit::validate);
    connect(m_borderColorAnimation, &QVariantAnimation::valueChanged, [this](const QVariant& v) {
        m_currentBorderColor = v.value<QColor>();
        this->update();
        emit this->currentBorderColorChanged(m_currentBorderColor);
    });

    connect(m_textColorAnimation, &QVariantAnimation::valueChanged, [this](const QVariant& v) {
        m_currentTextColor = v.value<QColor>();
        this->setDefaultTextColor(m_currentTextColor);
    });
}

void TextEdit::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    if(m_drawBorders) {
        painter->save();
        painter->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing, false);
        painter->setRenderHint(QPainter::TextAntialiasing);
        painter->setPen(m_currentBorderColor);
        painter->drawRect(this->boundingRect());
        painter->restore();
    }

    QStyleOptionGraphicsItem option2 = *option;
    option2.state = QStyle::State_None;
    QGraphicsTextItem::paint(painter, &option2, widget);
}

void TextEdit::setValidator(const QRegularExpression& validator)
{
    m_validator = validator;
}

QColor TextEdit::validBorderColor() const
{
    return m_validBorderColor;
}

QColor TextEdit::invalidBorderColor() const
{
    return m_invalidBorderColor;
}

QColor TextEdit::currentBorderColor() const
{
    return m_currentBorderColor;
}

bool TextEdit::valid() const
{
    return m_valid;
}

QColor TextEdit::textColor() const
{
    return m_textColor;
}

void TextEdit::setValidBorderColor(QColor validBorderColor)
{
    if (m_validBorderColor == validBorderColor)
        return;

    m_validBorderColor = validBorderColor;
    emit validBorderColorChanged(m_validBorderColor);
}

void TextEdit::setInvalidBorderColor(QColor invalidBorderColor)
{
    if (m_invalidBorderColor == invalidBorderColor)
        return;

    m_invalidBorderColor = invalidBorderColor;
    emit invalidBorderColorChanged(m_invalidBorderColor);
}

void TextEdit::setDrawBorders(bool v)
{
    m_drawBorders = v;
    this->update();
}

void TextEdit::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    m_currentTextColor = m_textColor;
    emit textColorChanged(m_textColor);
}

void TextEdit::validate()
{
    QTextDocument* document = this->document();

    QRegularExpressionMatch match = m_validator.match(document->toPlainText());

    if(!match.hasMatch() && m_currentBorderColor != m_invalidBorderColor) {
        m_borderColorAnimation->setStartValue(m_currentBorderColor);
        m_borderColorAnimation->setEndValue(m_invalidBorderColor);

        m_textColorAnimation->setStartValue(m_currentTextColor);
        m_textColorAnimation->setEndValue(m_invalidBorderColor);

        m_valid = false;
        m_borderColorAnimation->start();
        m_textColorAnimation->start();
    }

    else if(match.hasMatch() && m_currentBorderColor != m_validBorderColor){
        m_borderColorAnimation->setStartValue(m_currentBorderColor);
        m_borderColorAnimation->setEndValue(m_validBorderColor);

        m_textColorAnimation->setStartValue(m_currentTextColor);
        m_textColorAnimation->setEndValue(m_textColor);

        m_valid = true;
        m_borderColorAnimation->start();
        m_textColorAnimation->start();
    }
}


