#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsWidget>
#include <QMainWindow>
#include <app/ui/container/blockcanvas.h>
#include <app/ui/container/blocksselection.h>
#include <app/ui/container/toolbar.h>
#include <app/ui/view/warningpopup.h>
#include "ui/portregister.h"

/**
 * Main app window.
 */
class AppWindow : public QGraphicsWidget {
    Q_OBJECT
    private:
        BlocksSelection* m_blockSelection;
        BlockCanvas* m_blockCanvas;
        ToolBar* m_toolbar;
        WarningPopUp* m_warning;

    public:
        AppWindow(QGraphicsWidget* parent = nullptr);

    public slots:
        /**
         * Signal receiver for window resize.
         * @param size new size
         */
        void resizeWindow(QSize size);
};

#endif // MAINWINDOW_H
