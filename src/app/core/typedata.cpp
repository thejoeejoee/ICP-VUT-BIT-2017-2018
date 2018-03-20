#include "typedata.h"

QString TypeData::label() const {
    return m_label;
}

KeyList TypeData::keys() const {
    return m_keys;
}

TypeData::TypeData(QString &label, KeyList &keys) {
    m_label = label;
    m_keys = keys;
}

TypeData::TypeData() {}
