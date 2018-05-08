#-------------------------------------------------
#
# Project created by QtCreator 2018-02-19T17:18:53
#
#-------------------------------------------------

QT       += core gui svg
CONFIG += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blockeditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#HEADERS += $$files(*.h, true) $$files(*.tpp, true)
#SOURCES += $$files(*.cc, true) $$files(*.cpp, true)

DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui


RESOURCES += \
    app/ui/resources.qrc

HEADERS += \
    app/core/blocks/addblock.h \
    app/core/blocks/blockport.h \
    app/core/blocks/blockportvalue.h \
    app/core/blocks/blocks.h \
    app/core/blocks/cosblock.h \
    app/core/blocks/mulblock.h \
    app/core/blocks/sinblock.h \
    app/core/blocks/subblock.h \
    app/core/blocks/vectinitblock.h \
    app/core/blocks/vectmagblock.h \
    app/core/base.h \
    app/core/block.h \
    app/core/blockmanager.h \
    app/core/factoriable.h \
    app/core/factorybase.h \
    app/core/identified.h \
    app/core/join.h \
    app/core/schemeio.h \
    app/ui/container/blockcanvas.h \
    app/ui/container/blocksselection.h \
    app/ui/container/scrollarea.h \
    app/ui/container/toolbar.h \
    app/ui/control/clickable.h \
    app/ui/control/iconbutton.h \
    app/ui/control/plaintext.h \
    app/ui/control/scrollbar.h \
    app/ui/control/textbutton.h \
    app/ui/control/textedit.h \
    app/ui/control/texteditwithfixedtext.h \
    app/ui/view/warningpopup.h \
    app/ui/window/graphicsview.h \
    app/ui/blockportvalueview.h \
    app/ui/blockportview.h \
    app/ui/blockview.h \
    app/ui/joinview.h \
    app/mainwindow.h

SOURCES += \
    app/core/blocks/addblock.cpp \
    app/core/blocks/blockport.cpp \
    app/core/blocks/blockportvalue.cpp \
    app/core/blocks/cosblock.cpp \
    app/core/blocks/mulblock.cpp \
    app/core/blocks/sinblock.cpp \
    app/core/blocks/subblock.cpp \
    app/core/blocks/vectinitblock.cpp \
    app/core/blocks/vectmagblock.cpp \
    app/core/block.cpp \
    app/core/blockmanager.cpp \
    app/core/identified.cpp \
    app/core/join.cpp \
    app/core/schemeio.cpp \
    app/ui/container/blockcanvas.cpp \
    app/ui/container/blocksselection.cpp \
    app/ui/container/scrollarea.cpp \
    app/ui/container/toolbar.cpp \
    app/ui/control/clickable.cpp \
    app/ui/control/iconbutton.cpp \
    app/ui/control/plaintext.cpp \
    app/ui/control/scrollbar.cpp \
    app/ui/control/textbutton.cpp \
    app/ui/control/textedit.cpp \
    app/ui/control/texteditwithfixedtext.cpp \
    app/ui/view/warningpopup.cpp \
    app/ui/window/graphicsview.cpp \
    app/ui/blockportvalueview.cpp \
    app/ui/blockportview.cpp \
    app/ui/blockview.cpp \
    app/ui/joinview.cpp \
    app/main.cpp \
    app/mainwindow.cpp
