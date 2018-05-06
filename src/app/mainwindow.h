/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsWidget>
#include <QMainWindow>
#include <app/core/schemeio.h>
#include <app/ui/container/blockcanvas.h>
#include <app/ui/container/blocksselection.h>
#include <app/ui/container/toolbar.h>
#include <app/ui/view/warningpopup.h>

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
        explicit AppWindow(QGraphicsWidget* parent = nullptr);

        /**
         * Gets current path of editation scheme file.
         * @return current path
         */
        QString currentPath() const;
        /**
         * Is scheme saved?
         * @return state
         */
        bool saved() const;

    private slots:
        /**
         * On title set.
         */
        void setTitle();

    protected slots:
        /**
         * Checks, if scheme was saved.
         * @return
         */
        bool handleUnsavedScheme();
        /**
         * Sets currents scheme file path.
         * @param path new path
         */
        void setCurrentPath(const QString &path);
        /**
         * Sets, if scheme is actually saved.
         * @param saved state
         */
        void setSaved(bool saved);

    public slots:
        /**
         * Signal receiver for window resize.
         * @param size new size
         */
        void resizeWindow(QSize size);

        /**
         * Open scheme from file.
         */
        void schemeOpen();
        /**
         * Save scheme to file.
         */
        void schemeSave();
        /**
         * Save as file scheme to file.
         */
        void schemeSaveAs();
        /**
         * Creates empty scheme.
         */
        void schemeNew();

    signals:
        /**
         * On path change.
         * @param path new path
         */
        void currentPathChanged(const QString &path);
        /**
         * Set new state of schema change.
         * @param saved new state
         */
        void savedChanged(bool saved);
        /**
         * On error in window.
         * @param msg message
         */
        void error(const QString &msg);
};

#endif // MAINWINDOW_H
