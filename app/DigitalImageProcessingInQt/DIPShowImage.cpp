#include "DIPShowImage.h"

// Default initialization
DIPShowImage::DIPShowImage(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    isImage = false;
}

// Implementation of method use to set the input of QImage
void DIPShowImage::paint(QPainter *painter)
{
    if(isImage == true) {
        float scale = (this->width() / m_image.width()) < (this->height() / m_image.height()) ?
                    (this->width() / m_image.width()) : (this->height() / m_image.height());
        float startX, startY;
        startX = this->width() / 2 - (m_image.width() * scale) / 2;
        startY = this->height() / 2 - (m_image.height() * scale) / 2;
        QRectF r1(startX, startY, m_image.width() * scale, m_image.height() * scale);
        painter->drawImage(r1, m_image);
    }else{
        QRectF r1(0, 0, this->width(), this->height());
        painter->fillRect(r1, Qt::transparent);
    }
}

// Implementation of method use to set the input of QImage
void DIPShowImage::setImage(const QImage &image)
{
    this->isImage = true;
    this->m_image = image;
    update();
}

// Implementation of method free the QImage
void DIPShowImage::freeImage()
{
    this->isImage = false;
    update();
}

