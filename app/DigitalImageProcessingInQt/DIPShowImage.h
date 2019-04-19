#ifndef DIPSHOWIMAGE_H
#define DIPSHOWIMAGE_H

#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPainter>

class DIPShowImage : public QQuickPaintedItem
{
    Q_OBJECT
    // Property use to input QImage
    Q_PROPERTY(QImage image WRITE setImage)
public:
    DIPShowImage(QQuickItem *parent = 0);

    // Method use to set the input of QImage
    void setImage(const QImage &image);

    // Method to display QImage on screen
    void paint(QPainter *painter);

public slots:
    // Free the QImage
    void freeImage();

private:
    bool isImage;
    QImage m_image;
};

#endif // DIPSHOWIMAGE_H
