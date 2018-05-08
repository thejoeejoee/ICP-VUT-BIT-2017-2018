/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

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
        ~GraphicsView() override {}

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
