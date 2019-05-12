#ifndef DIPFEATURES_H
#define DIPFEATURES_H

#include <QObject>
#include <QColor>
#include <QPainter>
#include <QElapsedTimer>
#include "DADIP_ImageIO.h"

class DIPFeatures : public QObject
{
    Q_OBJECT
public:
    enum DIP_STATE
    {
        DIP_UNINIT, // Not set image input
        DIP_LOADED, // When Image can be read OK
    };

    // Define method to access this class as singleton
    static DIPFeatures* getInstance();
    DIPFeatures();

public slots:
    // Timer Elapsed
    void dipStartTimer();
    float dipStopTimer();

    // Set Image Input
    void dipSetImageSource(const QString& source);

    // Load Image
    void dipLoadImage();

    // Reset data
    void dipResetData();

    // Convert Input Image to QImage for display on QML
    QImage dipConvertInput2QImage();

    // Convert Output Image to QImage for display on QML
    QImage dipConvertOutput2QImage();

    // Convert RGB to grayscale
    void dipConvertRGBToGrayScale();

private:
    // Use for measuring processing time
    QElapsedTimer m_timer;

    // Hold the state of application
    int m_state = DIP_UNINIT;

    // Hold location for user input image
    QString m_imageSource = "";

    // Input/Output image with DADIP_IMAGE structure
    DADIP_IMAGE* m_input = NULL;
    DADIP_IMAGE* m_output = NULL;
};

#endif // DIPFEATURES_H
