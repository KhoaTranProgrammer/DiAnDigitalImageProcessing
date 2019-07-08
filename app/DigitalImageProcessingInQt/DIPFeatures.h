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
    // Calculate Histogram Equalization
    void dipHistogramEqualization(int graylevels, int newgrays);

    // Convert Input Image to QImage for display on QML
    QImage dipConvertInput2QImage();

    // Convert Output Image to QImage for display on QML
    QImage dipConvertOutput2QImage();

    // Convert RGB to grayscale
    void dipConvertRGBToGrayScale();

    // Group of Image Rotation Features
    void dipFlipVertical();     // Vertical Flipping
    void dipFlipHorizontal();   // Horizontal Flipping
    void dipRotation90();       // 90 Degree Rotation
    void dipRotation180();      // 180 Degree Rotation
    void dipRotation270();      // 270 Degree Rotation
    void dipRotation(int xorigin, int yorigin, double angle);   // Rotation for any degree

    // Group of Mathematic Features
    void dipMathAdd(int value);
    void dipMathSubtract(int value);
    void dipMathAnd(int value);
    void dipMathOr(int value);
    void dipMathXor(int value);
    void dipMathNot();
    void dipMathNand(int value);
    void dipMathNor(int value);

    // Image Overlay by Non Zero mode
    void dipOverlayNonZero(int startrowofimg1, int startrowofimg2, int newheight,
                  int startcolofimg1, int startcolofimg2, int newwidth);
    // Image Overlay by Zero mode
    void dipOverlayZero(int startrowofimg1, int startrowofimg2, int newheight,
                  int startcolofimg1, int startcolofimg2, int newwidth);
    // Image Overlay by Greater mode
    void dipOverlayGreater(int startrowofimg1, int startrowofimg2, int newheight,
                  int startcolofimg1, int startcolofimg2, int newwidth);
    // Image Overlay by Less mode
    void dipOverlayLess(int startrowofimg1, int startrowofimg2, int newheight,
                  int startcolofimg1, int startcolofimg2, int newwidth);
    // Image Overlay by Average mode
    void dipOverlayAverage(int startrowofimg1, int startrowofimg2, int newheight,
                  int startcolofimg1, int startcolofimg2, int newwidth);

    // Image Geometry
    void dipInvert();
    void dipGeometry(float angle, float xstretch, float ystretch,
                     int xdisplace, int ydisplace, float xcross, float ycross);
    void dipStretch(float xstretch, float ystretch);
    void dipCrop(int startrow, int startcol, int newheight, int newwidth);
    void dipPaste(int startrowofimg1, int startrowofimg2, int newheight,
                  int startcolofimg1, int startcolofimg2, int newwidth);
    void dipWarp(int xcontrol, int ycontrol);
    void dipObjectWarp(int x1, int y1, int x2, int y2,
                       int x3, int y3, int x4, int y4);

    // Filter features
    void dipFilterImage(int masktype, int lowhigh);
    void dipMedianFilter(int size);
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
