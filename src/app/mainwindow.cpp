/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "mainwindow.h"
#include <QHBoxLayout>

#include <QPainter>
#include <QGraphicsAnchorLayout>
#include <QJsonDocument>
#include <QMessageBox>
#include <QGraphicsScene>
#include <app/ui/control/textedit.h>
#include <QFileDialog>
#include <app/ui/window/graphicsview.h>

AppWindow::AppWindow(QGraphicsWidget* parent) : QGraphicsWidget{parent} {
    m_blockSelection = new BlocksSelection{this};
    m_blockSelection->setMaximumWidth(195);
    m_blockSelection->setMinimumWidth(m_blockSelection->maximumWidth());

    m_blockCanvas = new BlockCanvas{this};
    m_warning = new WarningPopUp{m_blockCanvas};
    m_warning->resize(300, 40);
    m_schemeIO = new SchemeIO{m_blockCanvas->manager(), this};

    m_toolbar = new ToolBar{this};

    this->setTitle();

    connect(m_toolbar, &ToolBar::evaluate, m_blockCanvas, &BlockCanvas::evaluate);
    connect(m_toolbar, &ToolBar::debug, m_blockCanvas, &BlockCanvas::debug);
    connect(m_toolbar, &ToolBar::stop, m_blockCanvas, &BlockCanvas::stopDebug);
    connect(m_blockCanvas, &BlockCanvas::debugStateChanged,
            m_toolbar, &ToolBar::setDebugIconVisiblity);
    connect(m_blockCanvas, &BlockCanvas::error, [this](const QString &msg) {
        m_warning->popUp(msg, 3);
    });

    connect(m_schemeIO, &SchemeIO::error, [this](const QString &msg) {
        m_warning->popUp(msg, 3);
    });

    connect(this, &AppWindow::error, [this](const QString &msg) {
        m_warning->popUp(msg, 3);
    });

    connect(m_toolbar, &ToolBar::openFile, this, &AppWindow::schemeOpen);
    connect(m_toolbar, &ToolBar::saveFile, this, &AppWindow::schemeSave);
    connect(m_toolbar, &ToolBar::newFile, this, &AppWindow::schemeNew);
    connect(m_toolbar, &ToolBar::saveAsFile, this, &AppWindow::schemeSaveAs);

    connect(m_blockCanvas, &BlockCanvas::blockAdded, [this]() { this->setSaved(false); });
    connect(m_blockCanvas, &BlockCanvas::joinAdded, [this]() { this->setSaved(false); });
    connect(m_blockCanvas, &BlockCanvas::blockDeleted, [this]() { this->setSaved(false); });
    connect(m_blockCanvas, &BlockCanvas::joinDeleted, [this]() { this->setSaved(false); });

    connect(this, &AppWindow::savedChanged, this, &AppWindow::setTitle);
    connect(this, &AppWindow::currentPathChanged, this, &AppWindow::setTitle);


    auto layout = new QGraphicsAnchorLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addCornerAnchors(layout, Qt::TopLeftCorner, m_toolbar, Qt::TopLeftCorner);

    layout->addCornerAnchors(m_toolbar, Qt::BottomLeftCorner, m_blockSelection, Qt::TopLeftCorner);
    layout->addCornerAnchors(layout, Qt::BottomLeftCorner,
                             m_blockSelection, Qt::BottomLeftCorner);

    layout->addCornerAnchors(m_blockSelection, Qt::TopRightCorner,
                             m_blockCanvas, Qt::TopLeftCorner);
    layout->addCornerAnchors(m_blockCanvas, Qt::BottomRightCorner,
                             layout, Qt::BottomRightCorner);
}

QString AppWindow::currentPath() const {
    return m_currentPath;
}

bool AppWindow::saved() const {
    return m_saved;
}

void AppWindow::setTitle() {
    QString title{"%1%4%2%3"};
    title = title
            .arg(tr("Block Editor"))
            .arg(m_currentPath)
            .arg((!m_saved && !m_currentPath.isEmpty()) ? "*" : "")
            .arg((m_currentPath.isEmpty()) ? "" : " - ");
    if (this->scene() != nullptr && this->scene()->views().length())
        this->scene()->views().at(0)->setWindowTitle(title);
}

void AppWindow::setCurrentPath(const QString &path) {
    if (path == m_currentPath)
        return;
    m_currentPath = path;
    emit this->currentPathChanged(path);
}

void AppWindow::setSaved(bool saved) {
    if (saved == m_saved)
        return;
    m_saved = saved;
    emit this->savedChanged(saved);
}

void AppWindow::resizeWindow(QSize size) {
    this->resize(size);
}

bool AppWindow::handleUnsavedScheme() {
    if (m_saved)
        return false;
    auto reply = QMessageBox::question(
            nullptr,
            tr("Unsaved scheme"),
            tr("Do you want to save scheme?"));
    if (reply == QMessageBox::Yes)
        this->schemeSave();
    return true;
}

void AppWindow::schemeOpen() {
    this->handleUnsavedScheme();

    const QString filePath = QFileDialog::getOpenFileName(
            nullptr,
            tr("Open file"),
            QString(),
            QString("%1 (*.%2);;All Files (*.*)")
                    .arg(tr("Block schemes"))
                    .arg(AppWindow::s_fileFormat));
    if (filePath.isEmpty())
        return;

    this->setCurrentPath(filePath);
    QFile file(m_currentPath);

    if (!file.open(QIODevice::ReadOnly)) {
        emit this->error(tr("File could not be open."));
        return;
    }

    m_blockCanvas->clear();
    this->setSaved(true);

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) {
        emit this->error(tr("Json parse error"));
        return;
    }
    m_schemeIO->loadFromJson(doc.object(), m_blockCanvas->container());
}

void AppWindow::schemeSave() {
    if (m_currentPath.isEmpty()) {
        const QString filePath = QFileDialog::getSaveFileName(
                nullptr,
                tr("Save file"),
                QString(),
                QString("%1 (*.%2);;All Files (*.*)")
                        .arg(tr("Block schemes"))
                        .arg(AppWindow::s_fileFormat));
        if (filePath.isEmpty())
            return;
        this->setCurrentPath(filePath);
    }


    QJsonDocument doc{m_schemeIO->exportToJson()};
    QFile file(m_currentPath);

    if (!file.open(QIODevice::WriteOnly)) {
        emit this->error(tr("File could not be open."));
        return;
    }

    this->setSaved(true);
    file.write(doc.toJson());
}

void AppWindow::schemeSaveAs() {
    const QString filePath = QFileDialog::getSaveFileName(
            nullptr,
            tr("Save file as"),
            QString(),
            QString("%1 (*.%2);;All Files (*.*)")
                    .arg(tr("Block schemes"))
                    .arg(AppWindow::s_fileFormat));
    if (filePath.isEmpty())
        return;
    this->setCurrentPath(filePath);

    QJsonDocument doc{m_schemeIO->exportToJson()};
    QFile file(m_currentPath);

    if (!file.open(QIODevice::WriteOnly)) {
        emit this->error(tr("File could not be open."));
        return;
    }

    this->setSaved(true);
    file.write(doc.toJson());
}

void AppWindow::schemeNew() {
    this->handleUnsavedScheme();

    m_blockCanvas->clear();
    this->setSaved(true);
    this->setCurrentPath("");
}
