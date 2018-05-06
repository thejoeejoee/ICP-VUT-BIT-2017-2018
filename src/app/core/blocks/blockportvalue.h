/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef BLOCKPORTVALUE_H
#define BLOCKPORTVALUE_H

#include "blockport.h"
#include <app/core/identified.h>
#include <QGraphicsWidget>


/**
 * Value of port in block.
 */
class BlockPortValue : public BlockPort {
    public:
        BlockPortValue(Identifier blockId, Type::TypeE type, QGraphicsItem* parent = nullptr);

        /**
         * Keys of port.
         * @return list of labels
         */
        QStringList labels() const override;
        /**
         * Set new value for port.
         * @param v new value for port
         */
        void setValue(MappedDataValues v) override;
        /**
         * Is port output?
         * @param v state
         */
        void setIsOutput(bool v) override;
};

#endif // BLOCKPORTVALUE_H
