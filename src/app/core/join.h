/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef CONNECTION_H
#define CONNECTION_H


#include "identified.h"
#include <app/ui/joinview.h>

class BlockManager;

/**
 * Represents one join in schema.
 */
class Join : public QObject, public Identified {
    Q_OBJECT

    private:
        Identifier m_fromBlock;
        PortIdentifier m_fromPort;

        Identifier m_toBlock;
        PortIdentifier m_toPort;
        JoinView* m_view;

    public:
        Join(
                Identifier fromBlock,
                PortIdentifier fromPort,
                Identifier toBlock,
                PortIdentifier toPort, QGraphicsItem* parent = nullptr
        );
        ~Join() override;

        /**
         * Source block getter.
         * @return block identifier
         */
        Identifier fromBlock() const;
        /**
         * Source port index getter.
         * @return port index
         */
        PortIdentifier fromPort() const;
        /**
         * Target block getter.
         * @return block identifier
         */
        Identifier toBlock() const;
        /**
         * Target port index getter.
         * @return port index
         */
        PortIdentifier toPort() const;
        /**
         * Returns view representing this join.
         * @return
         */
        JoinView* view() const;

        /**
         * Sets block manager for handling schema.
         * @param m manager
         */
        void setBlockManager(BlockManager* m);

    signals:
        /**
         * Request for delete join.
         * @param joinId id of join
         */
        void deleteRequest(Identifier joinId);
};


#endif //CONNECTION_H
