#ifndef DIPFEATURES_H
#define DIPFEATURES_H

#include <QObject>
#include <QColor>
#include <QPainter>
#include <QElapsedTimer>
#include "DADIP_ImageIO.h"
#include "DADIP_Histogram.h"

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

    // Get image data
    int getInputWidth();
    int getInputHeight();
    int getInputDepth();
    int getOutputWidth();
    int getOutputHeight();
    int getOutputDepth();

    // Reset data
    void dipResetData();

    // Write BMP image
    void dipWriteBmp(const QString& source);

    // Calculate Histogram for Input image
    void dipCalculateHistogramInput();
    // Calculate Histogram for Output image
    void dipCalculateHistogramOutput();
    // Get Histogram data at specific position of Input image
    int dipGetHistogramInputAt(int channel, int pos);
    // Get Histogram data at specific position of Output image
    int dipGetHistogramOutputAt(int channel, int pos);

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

    // Stores histogram data of Input/Output image
    DADIP_HISTOGRAM* m_histogramInput = NULL;
    DADIP_HISTOGRAM* m_histogramOutput = NULL;
};

#endif // DIPFEATURES_H
