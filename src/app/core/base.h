/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef ICP18_BASE_H
#define ICP18_BASE_H

#include <cstddef>
#include <QMap>
#include <QVariant>

#define GET_OVERLOADED_MACRO34(_1, _2, _3, _4, NAME, ...) NAME
#define GET_OVERLOADED_MACRO23(_1, _2, _3, NAME, ...) NAME
#define GET_OVERLOADED_MACRO12(_1, _2, NAME, ...) NAME

using Identifier = unsigned int;
using PortIdentifier = unsigned int;
using DataValue = QVariant;
using MappedDataValues = QMap<QString, DataValue>;

#endif //ICP18_BASE_H
