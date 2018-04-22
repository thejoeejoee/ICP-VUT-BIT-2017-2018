#include <QDebug>

template<typename ItemT>
template<typename SubItemT>
void FactoryBase<ItemT>::registerItem()
{
    FactoryBase<ItemT>::s_factories.insert(SubItemT::staticClassId(), SubItemT::createNew);
}

template<typename ItemT>
ItemT* FactoryBase<ItemT>::createNew(const QString& classId)
{
    if(!FactoryBase<ItemT>::s_factories.keys().contains(classId)) {
        qWarning() << "Factoriable item" << classId << "not registered.";
        return nullptr;
    }

    return FactoryBase<ItemT>::s_factories[classId]();
}
