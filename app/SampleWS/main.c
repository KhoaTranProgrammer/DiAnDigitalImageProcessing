#include "DADIP_ImageIO.h"
#include "DADIP_BMP.h"
#include "DADIP_Geometry.h"

void main(int argc, char *argv[])
{
    DADIP_PTRIMAGE inputimg, outputimg;
    
    /* Confirm the format of Input Image type */
    if (DADIP_OK == DaDip_Check_Image_Type(&inputimg, argv[1]))
    {
        /* Parse Image Data */
        if (DADIP_OK == inputimg->parseImage(inputimg))
        {
            /* Invert Input Image and store to Output Image */
            outputimg = DaDip_Invert(inputimg);

            /* Write Output Image to file */
            DaDip_Write_Bmp(outputimg, argv[2]);

            /* Free Images */
            inputimg->destroy(inputimg);
            outputimg->destroy(outputimg);
        }
    }
}
