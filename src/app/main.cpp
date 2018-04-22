#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "core/blocks/addblock.h"
#include "ui/window/graphicsview.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Block::registerItem<AddBlock>();
    // TODO remove
    /*Block* b = Block::createNew("add_block", &w);
    qDebug() << b->classId() << b->evaluate(QList<MappedDataValues>{
                                                MappedDataValues{{"value", 33}},
                                                MappedDataValues{{"value", 45}}});

    */

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
