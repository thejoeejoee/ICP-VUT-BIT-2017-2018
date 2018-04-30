#ifndef BLOCKPORTVALUEVIEW_H
#define BLOCKPORTVALUEVIEW_H

#include <app/ui/blockportview.h>
#include <app/ui/control/textedit.h>

class BlockPort;

class BlockPortValueView: public BlockPortView
{
        Q_OBJECT
    private:
        TextEdit* m_input;

    public:
        BlockPortValueView(BlockPort* data, bool editable = true, QGraphicsItem* parent = nullptr);

        MappedDataValues value() const override;
        void setValue(MappedDataValues v) override;

    private slots:
        void resizeWithText();
};

#endif // BLOCKPORTVALUEVIEW_H
