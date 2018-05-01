#ifndef WARNINGPOPUP_H
#define WARNINGPOPUP_H

#include <QGraphicsWidget>
#include <QTimer>
#include <QVariantAnimation>


class WarningPopUp : public QGraphicsWidget
{
        Q_OBJECT
    private:
        QVariantAnimation* m_animation;
        QTimer m_timer;
        QString m_msg;

    public:
        WarningPopUp(QGraphicsWidget* parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    protected slots:
        void hideAnimate();

    public slots:
        void popUp(const QString& msg, int seconds);
};

#endif // WARNINGPOPUP_H