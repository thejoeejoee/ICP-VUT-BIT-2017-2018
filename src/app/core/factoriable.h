/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef FACTORIABLE_H
#define FACTORIABLE_H

#include <QObject>
#include "base.h"

#define _FACTORIABLE_ID_3(baseClass, className, alias) \
    public: \
        static QString staticClassId() {return alias;} \
        static baseClass* createNew(QGraphicsWidget* parent) {return new className{parent};} \
        QString classId() const override {return className::staticClassId();}

#define _FACTORIABLE_ID_2(baseClass, className) \
    _Q_FACTORIABLE_ID_4(baseClass, className, #className)

#define FACTORIABLE_ID(...) GET_OVERLOADED_MACRO23(__VA_ARGS__, _FACTORIABLE_ID_3, _FACTORIABLE_ID_2)(__VA_ARGS__)

#define FACTORY_BASE_ID() \
    public: \
        virtual QString classId() = 0;

/**
 * @brief The Factoriable class is base class for all factoriable items.
 */
class Factoriable {
    public:
        Factoriable() = default;

        /**
         * @brief id Returns id of item.
         */
        virtual QString classId() const = 0;
};

#endif // FACTORIABLE_H
