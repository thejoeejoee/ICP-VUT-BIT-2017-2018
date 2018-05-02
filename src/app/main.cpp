#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ui/window/graphicsview.h"
#include <app/core/blocks/blocks.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/res/font/Montserrat-Light.ttf");
    QFontDatabase::addApplicationFont(":/res/font/Montserrat-Medium.ttf");
    QFontDatabase::addApplicationFont(":/res/font/Roboto-Light.ttf");


    Block::registerItem<AddBlock>();
    Block::registerItem<SubBlock>();
    Block::registerItem<MulBlock>();
    Block::registerItem<CosBlock>();
    Block::registerItem<SinBlock>();
    Block::registerItem<VectMagBlock>();

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
