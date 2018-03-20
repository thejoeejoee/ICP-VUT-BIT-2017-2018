#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("foo");
    w.show();
    w.setMinimumSize(200, 200);
    w.setStatusTip(QString("tip"));


    return a.exec();
}
