/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "texteditwithfixedtext.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QTextDocument>

TextEditWithFixedText::TextEditWithFixedText(QGraphicsItem* parent) : QGraphicsWidget(parent) {
    m_textEdit = new TextEdit{this};
    m_textEdit->setDrawBorders(false);
    m_fixedText = new PlainText{this};

    connect(m_fixedText, &PlainText::clicked, this, &TextEditWithFixedText::passFocus);
    connect(this, &TextEditWithFixedText::fontChanged, m_textEdit, &TextEdit::setFont);
    connect(this, &TextEditWithFixedText::fontChanged, m_fixedText, &QGraphicsTextItem::setFont);
    connect(m_textEdit, &TextEdit::currentBorderColorChanged, [this]() { this->update(); });
    connect(m_textEdit, &TextEdit::contentChanged, this, &TextEditWithFixedText::resizeToContent);
    connect(m_fixedText->document(), &QTextDocument::contentsChanged,
            this, &TextEditWithFixedText::resizeToContent);
}

void TextEditWithFixedText::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(widget);
    painter->setClipRect(option->exposedRect);

    painter->save();
    painter->setPen(m_textEdit->currentBorderColor());
    painter->drawRect(this->boundingRect().adjusted(1, 1, -1, -1));
    painter->restore();
}

bool TextEditWithFixedText::valid() const {
    return m_textEdit->valid();
}

QColor TextEditWithFixedText::validBorderColor() const {
    return m_textEdit->validBorderColor();
}

QColor TextEditWithFixedText::invalidBorderColor() const {
    return m_textEdit->invalidBorderColor();
}

QFont TextEditWithFixedText::font() const {
    return m_font;
}

QString TextEditWithFixedText::fixedToPlainText() const {
    return m_fixedText->toPlainText();
}

QString TextEditWithFixedText::toPlainText() const {
    return m_textEdit->toPlainText();
}

void TextEditWithFixedText::resizeToContent() {
    m_textEdit->setX(m_fixedText->boundingRect().size().width());
    const QRectF contentRect = m_fixedText->boundingRect() |
                               m_textEdit->boundingRect().translated(m_textEdit->pos());

    this->resize(contentRect.size());
}

void TextEditWithFixedText::passFocus() {
    if (m_textEdit->flags() == Qt::NoTextInteraction)
        return;
    m_textEdit->setFocus();
}

void TextEditWithFixedText::setPropagateMouse(bool v) {
    m_fixedText->setPropagateMouse(v);
}

void TextEditWithFixedText::setOneLineMode(bool v) {
    m_textEdit->setOneLineMode(v);
}

void TextEditWithFixedText::setTextColor(const QColor &color) {
    m_textEdit->setTextColor(color);
}

void TextEditWithFixedText::setValidator(const QRegularExpression &validator) {
    m_textEdit->setValidator(validator);
}

void TextEditWithFixedText::setPlainText(const QString &str) {
    m_textEdit->setPlainText(str);
}

void TextEditWithFixedText::setFixedText(const QString &str) {
    m_fixedText->setPlainText(str);
}

void TextEditWithFixedText::setFixedTextColor(const QColor &color) {
    m_fixedText->setDefaultTextColor(color);
}

void TextEditWithFixedText::setTextInteractionFlags(Qt::TextInteractionFlags flags) {
    m_textEdit->setTextInteractionFlags(flags);
}

void TextEditWithFixedText::setValidBorderColor(QColor validBorderColor) {
    m_textEdit->setValidBorderColor(validBorderColor);
}

void TextEditWithFixedText::setInvalidBorderColor(QColor invalidBorderColor) {
    m_textEdit->setInvalidBorderColor(invalidBorderColor);
}

void TextEditWithFixedText::setFont(const QFont &font) {
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(m_font);
}
