#ifndef BLOCKPORTVIEW_H
#define BLOCKPORTVIEW_H

#include <app/core/base.h>
#include <QGraphicsWidget>
#include <app/core/identified.h>
#include <QVariantAnimation>

class BlockPort;

/**
 * View for port assigned to block.
 */
class BlockPortView : public QGraphicsWidget {
    Q_OBJECT
    private:
        QVariantAnimation* m_opacityAnimation;
        BlockPort* m_data;

    public:
        /**
         * Construct from port data and optional qt parent.
         * @param portData
         * @param parent
         */
        explicit BlockPortView(BlockPort* portData, QGraphicsItem* parent = nullptr);

        ~BlockPortView() override;
        /**
         * Getter for value of port.
         * @return value
         */
        virtual MappedDataValues value() const = 0;
        /**
         * Setter for port value.
         * @param v new value
         */
        virtual void setValue(MappedDataValues v) = 0;
        /**
         * Getter for value without validation.
         * @param typed flag if values should be type
         * @return value
         */
        virtual QString rawValue(bool typed) const = 0;
        /**
         * Getter, if port is valid.
         * @return state
         */
        virtual bool valid() const = 0;

        /**
         * Returns data of view.
         * @return
         */
        BlockPort* portData() const;

    public slots:
        /**
         * Receiver for animation to hide.
         * @param animate flag
         */
        void animateHide(bool animate = true);

        /**
         * Receiver for animation to show.
         * @param animate flag
         */
        void animateShow(bool animate = true);

        /**
         * Partial hide element.
         * @param v state
         * @param animate with animation?
         */
        void animatePartialHide(double v, bool animate = true);
};

#endif // BLOCKPORTVIEW_H
