#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsWidget>
#include <QMainWindow>
#include <app/ui/container/blockcanvas.h>
#include <app/ui/container/blocksselection.h>
#include "ui/portregister.h"

//class MainWindow : public QWidget
//{
//        Q_OBJECT

//    private:
//        PortRegister* m_portRegister;
//        BlocksSelection* m_blocksSelection;

//    public:
//        MainWindow(QWidget *parent = 0);
//        ~MainWindow();

//    protected:
//        void paintEvent(QPaintEvent * event) override;
//        void mouseMoveEvent(QMouseEvent* event) override;
//};

class AppWindow: public QGraphicsWidget
{
        Q_OBJECT
    private:
        BlocksSelection* m_blockSelection;
        BlockCanvas* m_blockCanvas;

    public:
        AppWindow(QGraphicsWidget* parent = nullptr);

    public slots:
        void resizeWindow(QSize size);
};
#endif // MAINWINDOW_H
