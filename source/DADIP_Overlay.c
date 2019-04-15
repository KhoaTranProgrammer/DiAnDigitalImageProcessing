/*
 * Copyright (C) 2019 KhoaTran Programmer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************
 * VERSION: 1.0.0 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This file defines some methods to implement the functions that   *
 * overlay one image on top of another image                        *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-30-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Overlay_NonZero                                    *
 *         DaDip_Overlay_Zero                                       *
 *         DaDip_Overlay_Greater                                    *
 *         DaDip_Overlay_Less                                       *
 *         DaDip_Overlay_Average                                    *
 *******************************************************************/

#include "DADIP_Overlay.h"
#include "DADIP_Geometry.h"

/* Implementation of API to overlays 2 input images by Non Zero mode */
DADIP_PTRIMAGE DaDip_Overlay_NonZero(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth)
{
    DADIP_PTRIMAGE outputimg, cropimg;
    dadip_int i, j, k;
    dadip_float bytesperpixel;

    /* Checking the valid of input arguments for combination */
    if ((startrowofimg1 < 0 || startrowofimg1 >= HEIGHT(inputimg1)) ||
        (startcolofimg1 < 0 || startcolofimg1 >= WIDTH(inputimg1)) ||
        (newheight < 0 || newwidth < 0) ||
        ((startrowofimg1 + newheight) >= HEIGHT(inputimg1)) ||
        ((startcolofimg1 + newwidth) >= WIDTH(inputimg1))
        )
    {
        outputimg = NULL;
        cropimg = NULL;
    }
    else
    {
        /* Get the area of second input image */
        cropimg = DaDip_Crop(inputimg2, startrowofimg2, startcolofimg2, newheight, newwidth);
        CHECK_MEM(cropimg)

        /* Create output image with data from first input image */
        outputimg = DaDip_Create_Image_Copy(inputimg1);
    }
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg1));

    /* Copy cropping of second input image to output */
    for (i = startrowofimg1; i < (newheight + startrowofimg1); i++)
    {
        for (j = startcolofimg1; j < (newwidth + startcolofimg1); j++)
        {
            k = 0;
            do
            {
                /* Only copy in case of none zero */
                if(PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k) != 0)
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Release the crop area of second input image */
    cropimg->destroy(cropimg);

    return outputimg;
ERR_BEG
    /* Release the crop area of second input image */
    if(cropimg) cropimg->destroy(cropimg);
    return NULL;
ERR_END
}

/* Implementation of API to overlays 2 input images by Zero mode */
DADIP_PTRIMAGE DaDip_Overlay_Zero(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth)
{
    DADIP_PTRIMAGE outputimg, cropimg;
    dadip_int i, j, k;
    dadip_float bytesperpixel;

    /* Checking the valid of input arguments for combination */
    if ((startrowofimg1 < 0 || startrowofimg1 >= HEIGHT(inputimg1)) ||
        (startcolofimg1 < 0 || startcolofimg1 >= WIDTH(inputimg1)) ||
        (newheight < 0 || newwidth < 0) ||
        ((startrowofimg1 + newheight) >= HEIGHT(inputimg1)) ||
        ((startcolofimg1 + newwidth) >= WIDTH(inputimg1))
        )
    {
        outputimg = NULL;
        cropimg = NULL;
    }
    else
    {
        /* Get the area of second input image */
        cropimg = DaDip_Crop(inputimg2, startrowofimg2, startcolofimg2, newheight, newwidth);
        CHECK_MEM(cropimg)

        /* Create output image with data from first input image */
        outputimg = DaDip_Create_Image_Copy(inputimg1);
    }
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg1));

    /* Copy cropping of second input image to output */
    for (i = startrowofimg1; i < (newheight + startrowofimg1); i++)
    {
        for (j = startcolofimg1; j < (newwidth + startcolofimg1); j++)
        {
            k = 0;
            do
            {
                /* Only copy in case of zero */
                if(PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k) == 0)
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Release the crop area of second input image */
    cropimg->destroy(cropimg);

    return outputimg;
ERR_BEG
    /* Release the crop area of second input image */
    if(cropimg) cropimg->destroy(cropimg);
    return NULL;
ERR_END
}

/* Implementation of API to overlays 2 input images by Greater mode */
DADIP_PTRIMAGE DaDip_Overlay_Greater(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth)
{
    DADIP_PTRIMAGE outputimg, cropimg;
    dadip_int i, j, k;
    dadip_float bytesperpixel;

    /* Checking the valid of input arguments for combination */
    if ((startrowofimg1 < 0 || startrowofimg1 >= HEIGHT(inputimg1)) ||
        (startcolofimg1 < 0 || startcolofimg1 >= WIDTH(inputimg1)) ||
        (newheight < 0 || newwidth < 0) ||
        ((startrowofimg1 + newheight) >= HEIGHT(inputimg1)) ||
        ((startcolofimg1 + newwidth) >= WIDTH(inputimg1))
        )
    {
        outputimg = NULL;
        cropimg = NULL;
    }
    else
    {
        /* Get the area of second input image */
        cropimg = DaDip_Crop(inputimg2, startrowofimg2, startcolofimg2, newheight, newwidth);
        CHECK_MEM(cropimg)

        /* Create output image with data from first input image */
        outputimg = DaDip_Create_Image_Copy(inputimg1);
    }
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg1));

    /* Copy cropping of second input image to output */
    for (i = startrowofimg1; i < (newheight + startrowofimg1); i++)
    {
        for (j = startcolofimg1; j < (newwidth + startcolofimg1); j++)
        {
            k = 0;
            do
            {
                /* Only copy in case of greater */
                if(PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k) > 
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k))
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Release the crop area of second input image */
    cropimg->destroy(cropimg);

    return outputimg;
ERR_BEG
    /* Release the crop area of second input image */
    if(cropimg) cropimg->destroy(cropimg);
    return NULL;
ERR_END
}

/* Implementation of API to overlays 2 input images by Less mode */
DADIP_PTRIMAGE DaDip_Overlay_Less(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth)
{
    DADIP_PTRIMAGE outputimg, cropimg;
    dadip_int i, j, k;
    dadip_float bytesperpixel;

    /* Checking the valid of input arguments for combination */
    if ((startrowofimg1 < 0 || startrowofimg1 >= HEIGHT(inputimg1)) ||
        (startcolofimg1 < 0 || startcolofimg1 >= WIDTH(inputimg1)) ||
        (newheight < 0 || newwidth < 0) ||
        ((startrowofimg1 + newheight) >= HEIGHT(inputimg1)) ||
        ((startcolofimg1 + newwidth) >= WIDTH(inputimg1))
        )
    {
        outputimg = NULL;
        cropimg = NULL;
    }
    else
    {
        /* Get the area of second input image */
        cropimg = DaDip_Crop(inputimg2, startrowofimg2, startcolofimg2, newheight, newwidth);
        CHECK_MEM(cropimg)

        /* Create output image with data from first input image */
        outputimg = DaDip_Create_Image_Copy(inputimg1);
    }
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg1));

    /* Copy cropping of second input image to output */
    for (i = startrowofimg1; i < (newheight + startrowofimg1); i++)
    {
        for (j = startcolofimg1; j < (newwidth + startcolofimg1); j++)
        {
            k = 0;
            do
            {
                /* Only copy in case of less */
                if(PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k) < 
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k))
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Release the crop area of second input image */
    cropimg->destroy(cropimg);

    return outputimg;
ERR_BEG
    /* Release the crop area of second input image */
    if(cropimg) cropimg->destroy(cropimg);
    return NULL;
ERR_END
}

/* Implementation of API to overlays 2 input images by Average mode */
DADIP_PTRIMAGE DaDip_Overlay_Average(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth)
{
    DADIP_PTRIMAGE outputimg, cropimg;
    dadip_int i, j, k;
    dadip_float bytesperpixel;

    /* Checking the valid of input arguments for combination */
    if ((startrowofimg1 < 0 || startrowofimg1 >= HEIGHT(inputimg1)) ||
        (startcolofimg1 < 0 || startcolofimg1 >= WIDTH(inputimg1)) ||
        (newheight < 0 || newwidth < 0) ||
        ((startrowofimg1 + newheight) >= HEIGHT(inputimg1)) ||
        ((startcolofimg1 + newwidth) >= WIDTH(inputimg1))
        )
    {
        outputimg = NULL;
        cropimg = NULL;
    }
    else
    {
        /* Get the area of second input image */
        cropimg = DaDip_Crop(inputimg2, startrowofimg2, startcolofimg2, newheight, newwidth);
        CHECK_MEM(cropimg)

        /* Create output image with data from first input image */
        outputimg = DaDip_Create_Image_Copy(inputimg1);
    }
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg1));

    /* Copy cropping of second input image to output */
    for (i = startrowofimg1; i < (newheight + startrowofimg1); i++)
    {
        for (j = startcolofimg1; j < (newwidth + startcolofimg1); j++)
        {
            k = 0;
            do
            {
                /* Count the average */
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = (PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) + 
                    PIXELATIMAGE(cropimg, i - startrowofimg1, (j - startcolofimg1) * (int)bytesperpixel + k)) / 2;
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Release the crop area of second input image */
    cropimg->destroy(cropimg);

    return outputimg;
ERR_BEG
    /* Release the crop area of second input image */
    if(cropimg) cropimg->destroy(cropimg);
    return NULL;
ERR_END
}
