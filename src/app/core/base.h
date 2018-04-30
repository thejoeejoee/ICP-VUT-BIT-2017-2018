#ifndef ICP18_BASE_H
#define ICP18_BASE_H

#include <cstddef>
#include <QMap>

#define GET_OVERLOADED_MACRO34(_1, _2, _3, _4, NAME, ...) NAME
#define GET_OVERLOADED_MACRO23(_1, _2, _3, NAME, ...) NAME
#define GET_OVERLOADED_MACRO12(_1, _2, NAME, ...) NAME

using Identifier = unsigned;
using PortIdentifier = int;
using DataValue = double;
using MappedDataValues = QMap<QString, DataValue>;

#endif //ICP18_BASE_H
