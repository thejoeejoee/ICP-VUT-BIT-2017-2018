#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include "clickable.h"
#include <QSvgRenderer>

/**
 * Button widget with icon.
 */
class IconButton : public Clickable {
    Q_OBJECT
        Q_PROPERTY(QString imagePath
                           READ imagePath
                           WRITE setImagePath
                           NOTIFY
                           imagePathChanged)

    private:
        QSvgRenderer m_imageRenderer;
        QString m_imagePath;

    public:
        /**
         * New icon from icon path.
         * @param imagePath icon for button
         * @param parent qt parent
         */
        explicit IconButton(const QString &imagePath, QGraphicsItem* parent = nullptr);
        explicit IconButton(QGraphicsItem* parent = nullptr);

        /**
         * Paints method.
         * @param painter painter
         * @param option style
         * @param widget qt parent
         */
        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget) override;

        /**
         * Getter for current icon path.
         * @return icon path
         */
        QString imagePath() const;

    public slots:
        /**
         * Changes image path.
         * @param imagePath
         */
        void setImagePath(const QString &imagePath);

    signals:
        /**
         * On change of image path.
         * @param imagePath new path
         */
        void imagePathChanged(const QString &imagePath);
};

#endif // ICONBUTTON_H
