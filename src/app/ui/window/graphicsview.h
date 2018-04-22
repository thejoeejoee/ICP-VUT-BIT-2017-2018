#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
        Q_OBJECT

    public:
        GraphicsView();
        virtual ~GraphicsView() {}

    protected:
        void resizeEvent(QResizeEvent *event) override;

    signals:
        void resized(QSize size);
};

#endif // GRAPHICSVIEW_H
