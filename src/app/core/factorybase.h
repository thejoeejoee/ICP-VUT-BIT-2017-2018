#ifndef FACTORYBASE_H
#define FACTORYBASE_H


#include <QMap>
#include <QDebug>
#include <QGraphicsWidget>
#include <functional>

template<typename ItemT>
class FactoryBase
{
    private:
        static QMap<QString, std::function<ItemT*(QGraphicsWidget*)> > s_factories;
        static QList<QString> s_registeredItems;

    public:
        template<typename SubItemT>
        static void registerItem();
        static QList<QString> registeredItems();
        static ItemT* createNew(const QString& classId, QGraphicsWidget* parent);

};

template<typename ItemT>
QMap<QString, std::function<ItemT*(QGraphicsWidget*)> > FactoryBase<ItemT>::s_factories;

template<typename ItemT>
QList<QString> FactoryBase<ItemT>::s_registeredItems;

template<typename ItemT>
template<typename SubItemT>
void FactoryBase<ItemT>::registerItem()
{
    FactoryBase<ItemT>::s_registeredItems.append(SubItemT::staticClassId());
    FactoryBase<ItemT>::s_factories.insert(SubItemT::staticClassId(), SubItemT::createNew);
}

template<typename ItemT>
QList<QString> FactoryBase<ItemT>::registeredItems()
{
    return FactoryBase<ItemT>::s_registeredItems;
}

template<typename ItemT>
ItemT* FactoryBase<ItemT>::createNew(const QString& classId, QGraphicsWidget* parent)
{
    if(!FactoryBase<ItemT>::s_factories.keys().contains(classId)) {
        qWarning() << "Factoriable item" << classId << "not registered.";
        return nullptr;
    }

    return FactoryBase<ItemT>::s_factories[classId](parent);
}
//#include "factorybase.tpp"

#endif // FACTORYBASE_H
