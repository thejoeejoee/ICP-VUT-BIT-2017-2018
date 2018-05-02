#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QGraphicsWidget>

/**
 * Handle for scroll bar.
 */
class ScrollBarHandle : public QGraphicsWidget {
    Q_OBJECT
        Q_PROPERTY(QColor color
                           READ
                                   color
                           WRITE
                                   setColor
                           NOTIFY
                           colorChanged)

    private:
        Qt::Orientation m_orientation;
        QSize m_slideArea;
        QColor m_color;
        qreal m_relativePos;

    public:
        explicit ScrollBarHandle(Qt::Orientation orientation, QGraphicsWidget* parent = nullptr);

        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget = nullptr) override;

        /**
         * Returns size of slide area.
         * @return size of area
         */
        QSize slideArea() const;
        /**
         * Returns color of slide area.
         * @return color of area
         */
        QColor color() const;
        /**
         * Returns relative position to base state.
         * @return relative position
         */
        qreal relativePos() const;

    private slots:
        void calculateRelativePos();

    public slots:
        /**
         * Sets new size of area.
         * @param area new size
         */
        void setSlideArea(QSize area);
        /**
         * Sets new color of area.
         * @param area new color
         */
        void setColor(const QColor &color);

    signals:
        /**
         * Signal for color change.
         * @param color new color
         */
        void colorChanged(QColor color);
        /**
         * Signal for change of relative position.
         * @param pos position
         */
        void relativePosChanged(qreal pos);

};

/**
 * Windget for scroll bar.
 */
class ScrollBar : public QGraphicsWidget {
    Q_OBJECT
        Q_PROPERTY(int thickness
                           READ thickness
                           WRITE setThickness
                           NOTIFY
                           thicknessChanged)
        Q_PROPERTY(QColor color
                           READ
                                   color
                           WRITE
                                   setColor
                           NOTIFY
                           colorChanged)
        Q_PROPERTY(QColor handleColor
                           READ
                                   handleColor
                           WRITE
                                   setHandleColor
                           NOTIFY
                           handleColorChanged)
        Q_PROPERTY(qreal sizeRatio
                           READ
                                   sizeRatio
                           WRITE
                                   setSizeRatio
                           NOTIFY
                           sizeRatioChanged)

    public: // TODO: change visibility to private
        Qt::Orientation m_orientation;
        int m_thickness;
        QColor m_color;
        QColor m_handleColor;
        ScrollBarHandle* m_handle;
        qreal m_sizeRatio;
        bool m_mousePressed;
        QPointF m_pressPoint;
        QPointF m_handleOriginPos;

    public:
        explicit ScrollBar(Qt::Orientation orientation, QGraphicsWidget* parent = nullptr);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;
        void wheelEvent(QGraphicsSceneWheelEvent* e) override;

    public:
        /**
         * Paints bar.
         * @param painter painter
         * @param option style
         * @param widget qt parent
         */
        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget) override;

        /**
         * Getter for relative position.
         * @return position
         */
        qreal relativePos() const;
        /**
         * Getter for bar thickness.
         * @return thickness
         */
        int thickness() const;
        /**
         * Getter for bar color.
         * @return color
         */
        QColor color() const;
        /**
         * Getter for bar handle color.
         * @return handle color
         */
        QColor handleColor() const;
        /**
         * Getter for bar size ratio.
         * @return size ratio
         */
        qreal sizeRatio() const;

    private slots:
        void move(QPointF handleOriginPos, qreal delta);

        void resizeThickeness();
        void setSlideArea();
        void resizeHandle();

    public slots:
        /**
         * Manual scroll of bar.
         * @param delta scroll value
         */
        void artificialScroll(qreal delta);

        /**
         * Sets new thickness.
         * @param thickness new thickness
         */
        void setThickness(int thickness);

        /**
         * Sets new color.
         * @param thickness new color
         */
        void setColor(const QColor &color);

        /**
         * Sets new handle color.
         * @param thickness new handle color
         */
        void setHandleColor(const QColor &handleColor);

        /**
         * Sets new size ratio.
         * @param thickness new size ratio
         */
        void setSizeRatio(qreal sizeRatio);

    signals:
        /**
         * On relative position change.
         * @param ratio new position
         */
        void relativePosChanged(qreal ratio);
        void thicknessChanged(int thickness);
        /**
         * On color change.
         * @param ratio new color
         */
        void colorChanged(QColor color);
        /**
         * On handleColor change.
         * @param ratio new handleColor
         */
        void handleColorChanged(QColor handleColor);
        /**
         * On sizeRatio change.
         * @param ratio new sizeRatio
         */
        void sizeRatioChanged(qreal sizeRatio);
};

#endif // SCROLLBAR_H
