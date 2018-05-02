#ifndef WARNINGPOPUP_H
#define WARNINGPOPUP_H

#include <QGraphicsWidget>
#include <QSvgRenderer>
#include <QTimer>
#include <QVariantAnimation>

/**
 * Utility graphics class for warning pop-up.
 */
class WarningPopUp : public QGraphicsWidget {
    Q_OBJECT
    private:
        QVariantAnimation* m_animation;
        QTimer m_timer;
        QString m_msg;
        QSvgRenderer m_renderer;
        QFont m_font;

    public:
        explicit WarningPopUp(QGraphicsWidget* parent = nullptr);

        /**
         * Paints pop-up into widget.
         * @param painter painter
         * @param option style
         * @param widget parent widget
         */
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    protected slots:
        /**
         * Hide animation.
         */
        void hideAnimate();

    public slots:
        /**
         * Shows pop-up with text on seconds.
         * @param msg text for warning
         * @param seconds time duration
         */
        void popUp(const QString &msg, int seconds);
};

#endif // WARNINGPOPUP_H
