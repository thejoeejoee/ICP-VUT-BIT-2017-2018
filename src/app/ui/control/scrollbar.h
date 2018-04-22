#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QGraphicsWidget>

class ScrollBarHandle: public QGraphicsWidget
{
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

    private:
        Qt::Orientation m_orientation;
        QSize m_slideArea;
        QColor m_color;
        qreal m_relativePos;

    public:
        explicit ScrollBarHandle(Qt::Orientation orientation, QGraphicsWidget* parent = nullptr);

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;

        QSize slideArea() const;
        QColor color() const;
        qreal relativePos() const;

    private slots:
        void calculateRelativePos();

    public slots:
        void setSlideArea(QSize area);
        void setColor(const QColor& color);

    signals:
        void colorChanged(QColor color);
        void relativePosChanged(qreal pos);

};

class ScrollBar: public QGraphicsWidget
{
        Q_OBJECT
        Q_PROPERTY(int thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QColor handleColor READ handleColor WRITE setHandleColor NOTIFY handleColorChanged)
        Q_PROPERTY(qreal sizeRatio READ sizeRatio WRITE setSizeRatio NOTIFY sizeRatioChanged)

    private:
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

    public:
        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget =nullptr) override;

        qreal relativePos() const;
        int thickness() const;
        QColor color() const;
        QColor handleColor() const;
        qreal sizeRatio() const;

    private slots:
        void resizeThickeness();
        void setSlideArea();
        void resizeHandle();

    public slots:
        void setThickness(int thickness);
        void setColor(const QColor& color);
        void setHandleColor(const QColor& handleColor);
        void setSizeRatio(qreal sizeRatio);

    signals:
        void relativePosChanged(qreal ratio);
        void thicknessChanged(int thickness);
        void colorChanged(QColor color);
        void handleColorChanged(QColor handleColor);
        void sizeRatioChanged(qreal sizeRatio);
};

#endif // SCROLLBAR_H
