/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef BLOCK_H
#define BLOCK_H


#include "base.h"
#include "identified.h"
#include "factoriable.h"
#include "factorybase.h"
#include "blocks/blockport.h"
#include "../ui/blockview.h"

/**
 * Base class for block implementation.
 */
class Block : public QObject, public Identified, public Factoriable, public FactoryBase<Block> {
    Q_OBJECT

    private:
        QGraphicsWidget* m_parent;
        BlockView* m_view = nullptr;
        BlockPort* m_outputPort = nullptr;
        QList<BlockPort*> m_inputPorts;
        static QMap<QString, int> s_blocksInputsCount;

    protected:
        /**
         * Set new output port.
         * @param p output port
         */
        void setOutputPort(BlockPort* p);
        /**
         * Sets inputs port.
         * @param inputPorts inputs ports
         */
        void setInputPorts(const QList<BlockPort*> &inputPorts);

    public:
        explicit Block(QGraphicsWidget* parent = nullptr);
        ~Block() override;

        /**
         * Evaluate block operation.
         * @param inputData data to eval
         * @return computed value
         */
        virtual MappedDataValues evaluate(const QList<MappedDataValues> &inputData) = 0;
        /**
         * Getter for all input ports.
         * @return ports
         */
        virtual QList<BlockPort*> inputPorts() const;
        /**
         * Getter for output port
         * @return output port
         */
        BlockPort* outputPort() const;

        /**
         * Checks, if input data matchs inputs ports.
         * @param inputData data to check
         * @return state, if is ok
         */
        bool inputMatchesPorts(const QList<MappedDataValues> &inputData) const;

        /**
         * Registers new type of block into all enumeration.
         * @tparam T type of block
         * @param inputPortsCount count of input ports
         */
        template<typename T>
        static void registerBlock(int inputPortsCount);
        /**
         * Gets count of ports in block given by class string resp.
         * @param classId block identification
         * @return count of ports
         */
        static int blockInputsCount(const QString &classId);

        /**
         * Getter for qt parent.
         * @return parent
         */
        QGraphicsWidget* parent() const;
        /**
         * Getter for block view.
         * @return block view
         */
        BlockView* view() const;

        /**
         * Is inputs valids?
         * @return state
         */
        bool validInputs() const;

    signals:
        /**
         * Request for block delete.
         * @param blockId block to delete
         */
        void deleteRequest(Identifier blockId);
};


template<typename T>
void Block::registerBlock(int inputPortsCount) {
    Block::registerItem<T>();
    Block::s_blocksInputsCount.insert(T::staticClassId(), inputPortsCount);
}

#endif //BLOCK_H
