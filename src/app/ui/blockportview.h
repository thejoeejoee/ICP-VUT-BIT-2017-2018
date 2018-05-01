#ifndef BLOCKPORTVIEW_H
#define BLOCKPORTVIEW_H

#include <app/core/base.h>
#include <QGraphicsWidget>
#include <app/core/identified.h>
#include <QVariantAnimation>

class BlockPort;

class BlockPortView: public QGraphicsWidget
{
        Q_OBJECT
    private:
        QVariantAnimation* m_opacityAnimation;
        BlockPort* m_data;

    public:
        BlockPortView(BlockPort* portData, QGraphicsItem* parent = nullptr);

        virtual ~BlockPortView() {}
        virtual MappedDataValues value() const = 0;
        virtual void setValue(MappedDataValues v) = 0;

        BlockPort* portData() const;

    public slots:
        void animateHide(bool animate = true);
        void animateShow(bool animate = true);
};

#endif // BLOCKPORTVIEW_H
