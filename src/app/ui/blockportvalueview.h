#ifndef BLOCKPORTVALUEVIEW_H
#define BLOCKPORTVALUEVIEW_H

#include <app/ui/blockportview.h>
#include <app/ui/control/texteditwithfixedtext.h>

class BlockPort;

class BlockPortValueView: public BlockPortView
{
        Q_OBJECT
    private:
        TextEditWithFixedText* m_input;

    public:
        BlockPortValueView(BlockPort* portData, bool editable = true, QGraphicsItem* parent = nullptr);

        MappedDataValues value() const override;
        void setValue(MappedDataValues v) override;

    private slots:
        void resizeWithText();
};

#endif // BLOCKPORTVALUEVIEW_H
