/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "blockport.h"

void BlockPort::setView(BlockPortView* v) {
    m_view = v;
}

BlockPort::BlockPort(Identifier blockId, Type::TypeE type) {
    m_type = type;
    m_view = nullptr;
    m_blockId = blockId;
}

BlockPort::~BlockPort() {
    m_view->deleteLater();
}

MappedDataValues BlockPort::value() const {
    return m_view->value();
}

void BlockPort::setIsOutput(bool v) {
    m_isOutput = v;
}

BlockPortView* BlockPort::view() const {
    return m_view;
}

Identifier BlockPort::blockId() const {
    return m_blockId;
}

bool BlockPort::isOutput() const {
    return m_isOutput;
}

Type::TypeE BlockPort::type() const {
    return m_type;
}

bool BlockPort::valid() const {
    return m_view->valid();
}

bool BlockPort::isConnected() const {
    return m_view->opacity() == 0.;
}

QString Type::toString(Type::TypeE type) {
    if (type == Type::Angle)
        return "Angle";
    if (type == Type::Scalar)
        return "Scalar";
    if (type == Type::Vector)
        return "Vector";
    return "";
}

Type::TypeE Type::fromString(const QString &str) {
    if (str == "Angle")
        return Type::Angle;
    if (str == "Scalar")
        return Type::Scalar;
    if (str == "Vector")
        return Type::Vector;
    Q_ASSERT_X(false, "Type conversion", "Uknown type");
}

QString Type::validator(Type::TypeE type) {
    if (type == Type::Scalar || type == Type::Angle)
        return R"(^-?\d+\.?(\d*)?$)";
    else if (type == Type::Vector)
        return R"(^\{-?\d+\.?(\d*)?(, *-?\d+\.?(\d*)?)*\}$)";
    return ".*";
}

QString Type::defaultValue(Type::TypeE type) {
    if (type == Type::Scalar || type == Type::Angle)
        return "0";
    else if (type == Type::Vector)
        return "{0, 0}";
    return "";
}
