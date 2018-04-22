#ifndef PORTVIEW_H
#define PORTVIEW_H

#include <QWidget>

class PortView : public QWidget
{
        Q_OBJECT
    public:
        explicit PortView(QWidget *parent = nullptr);

    protected:
        void paintEvent(QPaintEvent*) override;
};

#endif // PORTVIEW_H
