/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ui/window/graphicsview.h"
#include <app/core/blocks/blocks.h>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/res/font/Montserrat-Light.ttf");
    QFontDatabase::addApplicationFont(":/res/font/Montserrat-Medium.ttf");
    QFontDatabase::addApplicationFont(":/res/font/Roboto-Light.ttf");


    Block::registerBlock<AddBlock>(2);
    Block::registerBlock<SubBlock>(2);
    Block::registerBlock<MulBlock>(2);
    Block::registerBlock<CosBlock>(1);
    Block::registerBlock<SinBlock>(1);
    Block::registerBlock<VectMagBlock>(1);
    Block::registerBlock<VectInitBlock>(2);

    auto scene = new QGraphicsScene;

    auto widget = new AppWindow;
    scene->addItem(widget);

    auto view = new GraphicsView;
    QObject::connect(view, &GraphicsView::resized, widget, &AppWindow::resizeWindow);

    view->setScene(scene);

    view->resize(1500, 800);
    view->setWindowTitle("Block Editor");
    view->show();

    return a.exec();
}
