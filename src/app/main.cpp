#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ui/window/graphicsview.h"
#include <app/core/blocks/blocks.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Block::registerItem<AddBlock>();
    Block::registerItem<SubBlock>();
    Block::registerItem<MulBlock>();
    Block::registerItem<CosBlock>();
    Block::registerItem<SinBlock>();

    auto scene = new QGraphicsScene;

    auto widget = new AppWindow;
    scene->addItem(widget);

    auto view = new GraphicsView;
    QObject::connect(view, &GraphicsView::resized, widget, &AppWindow::resizeWindow);

    view->setScene(scene);

    view->setWindowTitle("Block editor");
    view->resize(800, 500);
    view->show();

    return a.exec();
}
