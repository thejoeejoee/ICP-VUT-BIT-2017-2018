#ifndef SCHEMEIO_H
#define SCHEMEIO_H

#include <app/core/blockmanager.h>

// TODO doc
class SchemeIO: public QObject
{
        Q_OBJECT
    private:
        BlockManager* m_manager;

    public:
        SchemeIO(BlockManager* manager, QObject* parent = nullptr);

        QString jsonValid(const QJsonObject& scheme) const;
        QJsonObject exportToJson() const;
        void loadFromJson(QJsonObject scheme, QGraphicsWidget* parent);

    signals:
        void error(const QString& msg);
};

#endif // SCHEMEIO_H
