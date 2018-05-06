/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef PLAINTEXT_H
#define PLAINTEXT_H

#include <QGraphicsTextItem>

/**
 * Plain text as widget.
 */
class PlainText : public QGraphicsTextItem {
    Q_OBJECT
    private:
        bool m_propagateMouse = false;

    public:
        explicit PlainText(QGraphicsItem* parent = nullptr);

        /**
         * Should be mouse event propagated backward?
         * @param v
         */
        void setPropagateMouse(bool v);

    protected:
        /**
         * On mouse click.
         * @param e mouse event
         */
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

    signals:
        /**
         * On widget click.
         */
        void clicked();
};

#endif // PLAINTEXT_H
