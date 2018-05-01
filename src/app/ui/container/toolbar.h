#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QGraphicsWidget>
#include <app/ui/control/textbutton.h>
#include <app/ui/control/iconbutton.h>


class ToolBar : public QGraphicsWidget
{
        Q_OBJECT
    private:
        TextButton* m_newButton;
        TextButton* m_saveButton;
        TextButton* m_openButton;
        IconButton* m_runButton;
        IconButton* m_debugButton;
        IconButton* m_stopButton;

    public:
        ToolBar(QGraphicsItem* parent = nullptr);

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;
};

#endif // TOOLBAR_H
