#include "textedit.h"
#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QInputMethodEvent>
#include <QTextDocument>

TextEdit::TextEdit(QGraphicsItem* parent): TextEdit{"", parent} {}

TextEdit::TextEdit(const QString& text, QGraphicsItem* parent): QGraphicsTextItem{text, parent}
{
    m_borderColorAnimation = new QVariantAnimation(this);
    m_borderColorAnimation->setDuration(300);
    m_valid = true;

    this->setTextInteractionFlags(Qt::TextEditorInteraction);

    connect(this->document(), &QTextDocument::contentsChanged, this, &TextEdit::validate);
    connect(m_borderColorAnimation, &QVariantAnimation::valueChanged, [this](const QVariant& v) {
        m_currentBorderColor = v.value<QColor>();
        this->setDefaultTextColor(m_currentBorderColor);
        this->update();
    });
}

void TextEdit::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    painter->save();
    painter->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing, false);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setPen(m_currentBorderColor);
    painter->drawRect(this->boundingRect());
    painter->restore();

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

bool TextEdit::valid() const
{
    return m_valid;
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

void TextEdit::validate()
{
    QTextDocument* document = this->document();

    QRegularExpressionMatch match = m_validator.match(document->toPlainText());

    if(!match.hasMatch() && m_currentBorderColor != m_invalidBorderColor) {
        m_borderColorAnimation->setStartValue(m_currentBorderColor);
        m_borderColorAnimation->setEndValue(m_invalidBorderColor);
        m_valid = false;
        m_borderColorAnimation->start();
    }

    else if(match.hasMatch() && m_currentBorderColor != m_validBorderColor){
        m_borderColorAnimation->setStartValue(m_currentBorderColor);
        m_borderColorAnimation->setEndValue(m_validBorderColor);
        m_valid = true;
        m_borderColorAnimation->start();
    }
}


