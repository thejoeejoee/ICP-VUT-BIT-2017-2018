#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

/**
 * Custom graphics view for application.
 */
class GraphicsView : public QGraphicsView {
    Q_OBJECT

    public:
        GraphicsView();
        virtual ~GraphicsView() {}

    protected:
        /**
         * Resize event redraws all inner widgets.
         * @param event resize event
         */
        void resizeEvent(QResizeEvent* event) override;

    signals:
        /**
         * View has been resized to new size.
         * @param size new size
         */
        void resized(QSize size);
};

#endif // GRAPHICSVIEW_H
