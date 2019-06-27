#include "DIPFeatures.h"
#include "DADIP_Convert.h"
#include "DADIP_Rotate.h"
#include "DADIP_BMP.h"
#include "DADIP_Math.h"
#include "DADIP_Overlay.h"

// The static instance of DIPFeatures
static DIPFeatures *myDIPFeatures = NULL;

// The method to access Instance of DIPFeatures
DIPFeatures* DIPFeatures::getInstance()
{
    // Create new one in case of NULL
    if(!myDIPFeatures) {
        myDIPFeatures = new DIPFeatures();
    }

    // Return the available instance
    return myDIPFeatures;
}

// Default Initialization
DIPFeatures::DIPFeatures()
{

}

// Implementation to start timer
void DIPFeatures::dipStartTimer()
{
    m_timer.start();
}

// Implementation to return elapsed time in ms unit
float DIPFeatures::dipStopTimer()
{
    return m_timer.elapsed();
}

// Implementation to set image input
void DIPFeatures::dipSetImageSource(const QString& source)
{
    m_imageSource = source;
}

// Implementation to load image
void DIPFeatures::dipLoadImage()
{
    QByteArray array;

    // Convert QString to char array
    array = m_imageSource.toLocal8Bit();

    // Check the image is supported or not
    if(DaDip_Check_Image_Type(&m_input, (dadip_char*)array.data()) == DADIP_OK)
    {
        // In case of completely parsing image, update state to DIP_LOADED
        if(m_input->parseImage(m_input) == DADIP_OK)
        {
            m_state = DIP_LOADED;
        }
    }
}

// Implementation of getting input image data
int DIPFeatures::getInputWidth()
{
    if(m_input) return WIDTH(m_input);
    return 0;
}

int DIPFeatures::getInputHeight()
{
    if(m_input) return HEIGHT(m_input);
    return 0;
}

int DIPFeatures::getInputDepth()
{
    if(m_input) return DEPTH(m_input);
    return 0;
}

// Implementation of getting output image data
int DIPFeatures::getOutputWidth()
{
    if(m_output) return WIDTH(m_output);
    return 0;
}

int DIPFeatures::getOutputHeight()
{
    if(m_output) return HEIGHT(m_output);
    return 0;
}

int DIPFeatures::getOutputDepth()
{
    if(m_output) return DEPTH(m_output);
    return 0;
}

// Implementation to reset application data
void DIPFeatures::dipResetData()
{
    m_state = DIP_UNINIT;
    m_imageSource = "";
    if(m_input != NULL) m_input->destroy(m_input);
    if(m_output != NULL) m_output->destroy(m_output);
    m_input = NULL;
    m_output = NULL;
}

// Implementation of writing BMP image
void DIPFeatures::dipWriteBmp(const QString& source)
{
    if(m_output != NULL) {
        QByteArray array;
        array = source.toLocal8Bit();
        DaDip_Write_Bmp(m_output, (dadip_char*)array.data());
    }
}

// Implement to Calculate Histogram for Input image
void DIPFeatures::dipCalculateHistogramInput()
{
    if(m_state == DIP_LOADED) {
        if(m_histogramInput != NULL) DaDip_Free_Histogram(m_histogramInput);
        m_histogramInput = DaDip_Calculate_Histogram(m_input);
    }
}

// Implement to Calculate Histogram for Output image
void DIPFeatures::dipCalculateHistogramOutput()
{
    if(m_state == DIP_LOADED) {
        if(m_histogramOutput != NULL) DaDip_Free_Histogram(m_histogramOutput);
        m_histogramOutput = DaDip_Calculate_Histogram(m_output);
    }
}

// Implement to Get Histogram data at specific position of Input image
int DIPFeatures::dipGetHistogramInputAt(int channel, int pos)
{
    if(m_state == DIP_LOADED) {
        if((m_histogramInput != NULL) && pos >= 0 && pos <= 255) {
            if(channel == DADIP_R) {
                return m_histogramInput->histogramchannel1[pos];
            }else if(channel == DADIP_G) {
                return m_histogramInput->histogramchannel2[pos];
            }else if(channel == DADIP_B) {
                return m_histogramInput->histogramchannel3[pos];
            }
        }
    }
    return 0;
}

// Implement to Get Histogram data at specific position of Output image
int DIPFeatures::dipGetHistogramOutputAt(int channel, int pos)
{
    if(m_state == DIP_LOADED) {
        if((m_histogramOutput != NULL) && pos >= 0 && pos <= 255) {
            if(channel == DADIP_R) {
                return m_histogramOutput->histogramchannel1[pos];
            }else if(channel == DADIP_G) {
                return m_histogramOutput->histogramchannel2[pos];
            }else if(channel == DADIP_B) {
                return m_histogramOutput->histogramchannel3[pos];
            }
        }
    }
    return 0;
}

// Implement to calculate Histogram Equalization
void DIPFeatures::dipHistogramEqualization(int graylevels, int newgrays)
{
    DADIP_PTRHISTOGRAM histogramInput;
    if(m_state == DIP_LOADED) {
        histogramInput = DaDip_Calculate_Histogram(m_input);
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Histogram_Equalization(m_input, histogramInput, graylevels, newgrays);
    }
}

// Implement to convert Input Image to QImage for display on QML
QImage DIPFeatures::dipConvertInput2QImage()
{
    QRgb value;
    int gray;
    int i, j;

    QImage image(WIDTH(m_input), HEIGHT(m_input) , QImage::Format_RGB32);

    for (i = 0; i < HEIGHT(m_input); i++)
    {
        for (j = 0; j < WIDTH(m_input); j++)
        {
            // In case of 24 bit image
            if(DEPTH(m_input) == 24)
            {
                // Each pixel is set as RGB data
                value = qRgb(PIXELATIMAGE(m_input, i, j * 3 + DADIP_R),
                             PIXELATIMAGE(m_input, i, j * 3 + DADIP_G),
                             PIXELATIMAGE(m_input, i, j * 3 + DADIP_B)
                             );
                image.setPixel(j, i, value);
            }
            // In case of 8 bit image
            else if(DEPTH(m_input) == 8)
            {
                // Each pixel is set as gray data
                gray = PIXELATIMAGE(m_input, i, j);
                image.setPixel(j, i, QColor(gray, gray, gray).rgb());
            }
        }
    }

    return image;
}

// Implement to convert Output Image to QImage for display on QML
QImage DIPFeatures::dipConvertOutput2QImage()
{
    QRgb value;
    int gray;
    int i, j;

    // Return blank image in case of NULL output
    if(m_output == NULL)
    {
        QImage blank_image(1, 1 , QImage::Format_RGB32);

        return blank_image;
    }

    QImage image((m_output->width), (m_output->height) , QImage::Format_RGB32);

    for (i = 0; i < (m_output->height); i++)
    {
        for (j = 0; j < (m_output->width); j++)
        {
            // In case of 24 bit image
            if(m_output->depth == 24)
            {
                // Each pixel is set as RGB data
                value = qRgb(PIXELATIMAGE(m_output, i, j * 3 + DADIP_R),
                             PIXELATIMAGE(m_output, i, j * 3 + DADIP_G),
                             PIXELATIMAGE(m_output, i, j * 3 + DADIP_B)
                             );
                image.setPixel(j, i, value);
            }
            // In case of 8 bit image
            else if(m_output->depth == 8)
            {
                // Each pixel is set as gray data
                gray = PIXELATIMAGE(m_output, i, j);
                image.setPixel(j, i, QColor(gray, gray, gray).rgb());
            }
        }
    }

    return image;
}

// Implement to convert RGB to grayscale
void DIPFeatures::dipConvertRGBToGrayScale()
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Convert_RGB_To_GrayScale(m_input);
    }
}

// Implementation of Vertical Flipping
void DIPFeatures::dipFlipVertical()
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Flip_Vertical(m_input);
    }
}

// Implementation of Horizontal Flipping
void DIPFeatures::dipFlipHorizontal()
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Flip_Horizontal(m_input);
    }
}

// Implementation of 90 Degree Rotation
void DIPFeatures::dipRotation90()
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Rotation_90_Degree(m_input);
    }
}

// Implementation of 180 Degree Rotation
void DIPFeatures::dipRotation180()
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Rotation_180_Degree(m_input);
    }
}

// Implementation of 270 Degree Rotation
void DIPFeatures::dipRotation270()
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Rotation_270_Degree(m_input);
    }
}

// Implementation of Rotation for any degree
void DIPFeatures::dipRotation(int xorigin, int yorigin, double angle)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Rotation(m_input, xorigin, yorigin, angle);
    }
}

// Implementation of Mathematic Add
void DIPFeatures::dipMathAdd(int value)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Math_Add(m_input, value);
    }
}

// Implementation of Mathematic Subtract
void DIPFeatures::dipMathSubtract(int value)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Math_Subtract(m_input, value);
    }
}

// Implementation of Mathematic And
void DIPFeatures::dipMathAnd(int value)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Math_And(m_input, value);
    }
}

// Implementation of Mathematic Or
void DIPFeatures::dipMathOr(int value)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Math_Or(m_input, value);
    }
}

// Implementation of Mathematic Xor
void DIPFeatures::dipMathXor(int value)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Math_Xor(m_input, value);
    }
}

// Implementation of Mathematic Not
void DIPFeatures::dipMathNot()
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Math_Not(m_input);
    }
}

// Implementation of Mathematic Nand
void DIPFeatures::dipMathNand(int value)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Math_Nand(m_input, value);
    }
}

// Implementation of Mathematic Nor
void DIPFeatures::dipMathNor(int value)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);
        m_output = DaDip_Math_Nor(m_input, value);
    }
}

// Implementation of Image Overlay by Non Zero mode
void DIPFeatures::dipOverlayNonZero(int startrowofimg1, int startrowofimg2, int newheight,
              int startcolofimg1, int startcolofimg2, int newwidth)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);

        // The second image are used for this feature
        DADIP_PTRIMAGE image2;
        QByteArray array;
        QString sala = PROJECT_PATH;
        sala += "/image/sala.bmp";
        array = sala.toLocal8Bit();
        DaDip_Check_Image_Type(&image2, (dadip_char*)array.data());
        image2->parseImage(image2);

        m_output = DaDip_Overlay_NonZero(m_input, image2, startrowofimg1, startrowofimg2, newheight,
                                                   startcolofimg1, startcolofimg2, newwidth);
    }
}

// Implementation of Image Overlay by Zero mode
void DIPFeatures::dipOverlayZero(int startrowofimg1, int startrowofimg2, int newheight,
              int startcolofimg1, int startcolofimg2, int newwidth)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);

        // The second image are used for this feature
        DADIP_PTRIMAGE image2;
        QByteArray array;
        QString sala = PROJECT_PATH;
        sala += "/image/sala.bmp";
        array = sala.toLocal8Bit();
        DaDip_Check_Image_Type(&image2, (dadip_char*)array.data());
        image2->parseImage(image2);

        m_output = DaDip_Overlay_Zero(m_input, image2, startrowofimg1, startrowofimg2, newheight,
                                                   startcolofimg1, startcolofimg2, newwidth);
    }
}

// Implementation of Image Overlay by Greater mode
void DIPFeatures::dipOverlayGreater(int startrowofimg1, int startrowofimg2, int newheight,
              int startcolofimg1, int startcolofimg2, int newwidth)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);

        // The second image are used for this feature
        DADIP_PTRIMAGE image2;
        QByteArray array;
        QString sala = PROJECT_PATH;
        sala += "/image/sala.bmp";
        array = sala.toLocal8Bit();
        DaDip_Check_Image_Type(&image2, (dadip_char*)array.data());
        image2->parseImage(image2);

        m_output = DaDip_Overlay_Greater(m_input, image2, startrowofimg1, startrowofimg2, newheight,
                                                   startcolofimg1, startcolofimg2, newwidth);
    }
}

// Implementation of Image Overlay by Less mode
void DIPFeatures::dipOverlayLess(int startrowofimg1, int startrowofimg2, int newheight,
              int startcolofimg1, int startcolofimg2, int newwidth)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);

        // The second image are used for this feature
        DADIP_PTRIMAGE image2;
        QByteArray array;
        QString sala = PROJECT_PATH;
        sala += "/image/sala.bmp";
        array = sala.toLocal8Bit();
        DaDip_Check_Image_Type(&image2, (dadip_char*)array.data());
        image2->parseImage(image2);

        m_output = DaDip_Overlay_Less(m_input, image2, startrowofimg1, startrowofimg2, newheight,
                                                   startcolofimg1, startcolofimg2, newwidth);
    }
}

// Implementation of Image Overlay by Average mode
void DIPFeatures::dipOverlayAverage(int startrowofimg1, int startrowofimg2, int newheight,
              int startcolofimg1, int startcolofimg2, int newwidth)
{
    if(m_state == DIP_LOADED) {
        if(m_output != NULL) m_output->destroy(m_output);

        // The second image are used for this feature
        DADIP_PTRIMAGE image2;
        QByteArray array;
        QString sala = PROJECT_PATH;
        sala += "/image/sala.bmp";
        array = sala.toLocal8Bit();
        DaDip_Check_Image_Type(&image2, (dadip_char*)array.data());
        image2->parseImage(image2);

        m_output = DaDip_Overlay_Average(m_input, image2, startrowofimg1, startrowofimg2, newheight,
                                                   startcolofimg1, startcolofimg2, newwidth);
    }
}
