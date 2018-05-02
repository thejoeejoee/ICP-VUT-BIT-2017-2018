#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsWidget>
#include <QMainWindow>
#include <app/core/schemeio.h>
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
        static constexpr const char* s_fileFormat = "bsf";

        BlocksSelection* m_blockSelection;
        BlockCanvas* m_blockCanvas;
        ToolBar* m_toolbar;
        WarningPopUp* m_warning;
        QString m_currentPath = "";
        SchemeIO* m_schemeIO;
        bool m_saved = true;

    public:
        AppWindow(QGraphicsWidget* parent = nullptr);

        QString currentPath() const;
        bool saved() const;

    private slots:
        void setTitle();

    protected slots:
        bool handleUnsavedScheme();
        void setCurrentPath(const QString& path);
        void setSaved(bool saved);

    public slots:
        /**
         * Signal receiver for window resize.
         * @param size new size
         */
        void resizeWindow(QSize size);

        // TODO doc
        void schemeOpen();
        // TODO doc
        void schemeSave();
        // TODO doc
        void schemeSaveAs();
        // TODO doc
        void schemeNew();

    signals:
        void currentPathChanged(const QString& path);
        void savedChanged(bool saved);
        void error(const QString& msg);
};

#endif // MAINWINDOW_H
