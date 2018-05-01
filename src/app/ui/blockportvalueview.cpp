#include "blockportvalueview.h"

#include <QFont>
#include <QDebug>
#include <QGraphicsAnchorLayout>
#include <app/core/exceptions.h>

BlockPortValueView::BlockPortValueView(BlockPort* data, bool editable, QGraphicsItem* parent)
    : BlockPortView{data, parent}
{
    this->setPreferredSize(45, 20);

    m_input = new TextEditWithFixedText{this};
    m_input->setTextColor(QColor(Qt::black));
    m_input->setFixedText("Vector:");
    m_input->setFixedTextColor(QColor("#969696"));
    m_input->setFont(QFont("Montserrat Light"));
    m_input->setInvalidBorderColor(QColor("#d10000"));
    m_input->setValidBorderColor(QColor("#939393"));
    m_input->setPlainText("0");
    m_input->setValidator(QRegularExpression("^\\d+\\.?(\\d{1,4})?$"));
    if(!editable)
        m_input->setTextInteractionFlags(Qt::NoTextInteraction);

    this->resizeWithText();
    connect(m_input, &TextEditWithFixedText::geometryChanged,
            this, &BlockPortValueView::resizeWithText);
}

MappedDataValues BlockPortValueView::value() const
{
    if(!m_input->valid())
        throw InvalidInputError("Invalid block input");
    return MappedDataValues{{ "value", m_input->toPlainText().toDouble() }};
}

void BlockPortValueView::setValue(MappedDataValues v)
{
    Q_ASSERT(v.keys().contains("value"));
    m_input->setPlainText(QString::number(v["value"]));
}

void BlockPortValueView::resizeWithText()
{
    this->resize(m_input->boundingRect().size());
}
