/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

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

        QString jsonValid(const QJsonObject &scheme) const;
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
