#ifndef BLOCKPORTVALUEVIEW_H
#define BLOCKPORTVALUEVIEW_H

#include <app/core/blocks/blockport.h>
#include <app/ui/blockportview.h>
#include <app/ui/control/texteditwithfixedtext.h>

class BlockPort;

/**
 * Concrete implementation for view of port in block.
 */
class BlockPortValueView : public BlockPortView {
    Q_OBJECT
    private:
        TextEditWithFixedText* m_input;
        Type::TypeE m_type;

    public:
        /**
         * Creates value view from core port and type of port.
         * @param portData port data
         * @param type type of port
         * @param parent optional qt parent
         */
        BlockPortValueView(BlockPort* portData, Type::TypeE type, QGraphicsItem* parent = nullptr);

        /**
         * Getter for value of port
         * @return value
         */
        MappedDataValues value() const override;
        /**
         * Getter for raw value of port, without validation.
         * @param typed should be value typed?
         * @return value
         */
        QString rawValue(bool typed = false) const override;
        /**
         * Sets value to port.
         * @param v value
         */
        void setValue(MappedDataValues v) override;
        /**
         * Is port valid?
         * @return state
         */
        bool valid() const override;
        /**
         * Set editable state.
         * @param v new state
         */
        void setEditable(bool v);

    private slots:
        void resizeWithText();
};

#endif // BLOCKPORTVALUEVIEW_H
