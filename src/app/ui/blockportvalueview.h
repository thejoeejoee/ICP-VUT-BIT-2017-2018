#ifndef BLOCKPORTVALUEVIEW_H
#define BLOCKPORTVALUEVIEW_H

#include <app/core/blocks/blockport.h>
#include <app/ui/blockportview.h>
#include <app/ui/control/texteditwithfixedtext.h>

class BlockPort;

class BlockPortValueView: public BlockPortView
{
        Q_OBJECT
    private:
        TextEditWithFixedText* m_input;
        Type::TypeE m_type;

    public:
        BlockPortValueView(BlockPort* portData, Type::TypeE type, QGraphicsItem* parent = nullptr);

        MappedDataValues value() const override;
        QString rawValue(bool typed = false) const override;
        void setValue(MappedDataValues v) override;
        bool valid() const override;
        void setEditable(bool v);

    private slots:
        void resizeWithText();
};

#endif // BLOCKPORTVALUEVIEW_H
