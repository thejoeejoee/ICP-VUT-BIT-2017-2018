#ifndef TYPEDATA_H
#define TYPEDATA_H

#include <string>
#include <QList>


using std::string;

using KeyList = QList<QString>;


class TypeData {
    protected:
        QString m_label{};
        KeyList m_keys{};

    public:
        TypeData(QString &label, KeyList &keys);

        QString label() const;

        KeyList keys() const;

        TypeData();;
};


#endif //TYPEDATA_H
