/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QGraphicsWidget>
#include <app/ui/control/textbutton.h>
#include <app/ui/control/iconbutton.h>


/**
 * Main toolbar to control editor.
 */
class ToolBar : public QGraphicsWidget {
    Q_OBJECT
    private:
        TextButton* m_newButton;
        TextButton* m_saveButton;
        TextButton* m_saveAsButton;
        TextButton* m_openButton;
        IconButton* m_runButton;
        IconButton* m_debugButton;
        IconButton* m_stopButton;
        bool m_debugIconVisible = false;
        QSvgRenderer m_bugRenderer;

    public:
        ToolBar(QGraphicsItem* parent = nullptr);

        /**
         * Paints bar to widget via painter.
         * @param painter painter
         * @param option style
         * @param widget qt parent
         */
        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget) override;

    public slots:
        void setDebugIconVisiblity(bool v);

    signals:
        /**
         * New file to edit.
         */
        void newFile();
        /**
         * Save current schema to file.
         */
        void saveFile();
        /**
         * Open file with schema.
         */
        void openFile();
        /**
         * Run evaluator.
         */
        void evaluate();
        /**
         * Start debugging.
         */
        void debug();
        /**
         * Stop debugging.
         */
        void stop();

        /**
         * Save schema as file.
         */
        void saveAsFile();
};

#endif // TOOLBAR_H
