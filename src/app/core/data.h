#ifndef DATA_H
#define DATA_H


#include "base.h"
#include "typedata.h"

using DataValues = QMap<QString, DataValue>;

class Data {
    public:
        TypeData type;
        DataValues values;

};


#endif //DATA_H
