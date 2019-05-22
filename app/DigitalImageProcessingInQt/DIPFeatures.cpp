#include "DIPFeatures.h"
#include "DADIP_Convert.h"
#include "DADIP_BMP.h"

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
