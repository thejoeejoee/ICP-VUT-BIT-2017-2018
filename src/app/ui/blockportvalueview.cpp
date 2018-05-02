#include "blockportvalueview.h"

#include <QFont>
#include <QDebug>
#include <QGraphicsAnchorLayout>

BlockPortValueView::BlockPortValueView(BlockPort* data, Type::TypeE type, QGraphicsItem* parent)
    : BlockPortView{data, parent}
{
    this->setPreferredSize(45, 20);

    m_type = type;
    m_input = new TextEditWithFixedText{this};
    m_input->setOneLineMode(true);
    m_input->setTextColor(QColor(Qt::black));
    m_input->setFixedText(Type::toString(m_type) + ":");
    m_input->setFixedTextColor(QColor("#969696"));
    m_input->setFont(QFont("Montserrat Light", 12));
    m_input->setInvalidBorderColor(QColor("#d10000"));
    m_input->setValidBorderColor(QColor("#939393"));
    m_input->setPlainText(Type::defaultValue(type));
    m_input->setValidator(QRegularExpression(Type::validator(type)));

    this->resizeWithText();
    connect(m_input, &TextEditWithFixedText::geometryChanged,
            this, &BlockPortValueView::resizeWithText);
}

MappedDataValues BlockPortValueView::value() const
{
    if(!m_input->valid())
        return MappedDataValues{};
    if(m_type == Type::Scalar || m_type == Type::Angle)
        return MappedDataValues{{ "value", m_input->toPlainText().toDouble() }};
    else if(m_type == Type::Vector) {
        QString raw = m_input->toPlainText();
        raw = raw.remove("{").remove("}");
        QList<QVariant> values;
        for(const auto &singleVal: raw.split(","))
            values.append(QVariant(singleVal.toDouble()));

        return MappedDataValues{{ "value", QVariant(values) }};
    }

    else
        Q_ASSERT_X(false, "Parsing", "Unkown type");
}

QString BlockPortValueView::rawValue(bool typed) const
{
    if(!typed)
        return m_input->toPlainText();
    return QString("%1 %2").arg(m_input->fixedToPlainText(), m_input->toPlainText());
}

void BlockPortValueView::setValue(MappedDataValues v)
{
    if(!v.keys().contains("value")) {
        m_input->setPlainText("");
        return;
    }
    const QVariant val = v.value("value");
    QString repr = "{";

    if(val.isNull())
        repr = "";
    else if(val.type() == QVariant::Double)
        repr = QString::number(val.toDouble(), 'g', 4);
    else if(val.type() == QVariant::List) {
        int i = 0;
        QList<DataValue> values = val.value<QList<DataValue> >();
        for(const auto &v: values) {
            repr += QString::number(v.toDouble(), 'g', 4);
            if(i + 1 < values.length())
                repr += ",";
            i++;
        }
        repr += "}";
    }

    else
        Q_ASSERT_X(false, "Repr value", "Unknown type");

    m_input->setPlainText(repr);
}

bool BlockPortValueView::valid() const
{
    return m_input->valid();
}

void BlockPortValueView::setEditable(bool v)
{
    if(v)
        m_input->setTextInteractionFlags(Qt::TextEditorInteraction);
    else
        m_input->setTextInteractionFlags(Qt::NoTextInteraction);
}

void BlockPortValueView::resizeWithText()
{
    this->resize(m_input->boundingRect().size());
}
