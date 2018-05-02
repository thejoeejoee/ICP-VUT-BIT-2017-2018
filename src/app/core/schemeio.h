#ifndef SCHEMEIO_H
#define SCHEMEIO_H

#include <app/core/blockmanager.h>

/**
 * Class for managing schema save and load.
 */
class SchemeIO : public QObject {
    Q_OBJECT
    private:
        BlockManager* m_manager;

    public:
        explicit SchemeIO(BlockManager* manager, QObject* parent = nullptr);

        QString jsonValid(const QJsonObject& scheme) const;
        /**
         * Exports manager into json.
         * @return serialized
         */
        QJsonObject exportToJson() const;
        /**
         * Loads from scheme into manager.
         * @param scheme to load
         * @param parent qt parent
         */
        void loadFromJson(QJsonObject scheme, QGraphicsWidget* parent);

    signals:
        /**
         * On load error.
         * @param msg error description
         */
        void error(const QString &msg);
};

#endif // SCHEMEIO_H
