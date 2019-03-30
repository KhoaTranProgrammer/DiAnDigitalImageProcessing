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
 * This file implements method for image Geometrical Operations     *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-26-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Invert                                             *
 *         DaDip_Geometry                                           *
 *         DaDip_Stretch                                            *
 *         DaDip_Crop                                               *
 *         DaDip_Paste                                              *
 *******************************************************************/

#include "DADIP_Geometry.h"

/* Implementation of API to invert the pixels in an image */
DADIP_PTRIMAGE DaDip_Invert(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Perform Image invert */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * bytesperpixel + k) = GRAY_LEVELS - PIXELATIMAGE(inputimg, i, j * bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to perform three Basic Geometric Operations */
DADIP_PTRIMAGE DaDip_Geometry(DADIP_PTRIMAGE inputimg, dadip_float angle,
                               dadip_float xstretch, dadip_float ystretch,
                               dadip_short xdisplace, dadip_short ydisplace,
                               dadip_float xcross, dadip_float ycross)
{
    dadip_double cosa, sina, radian_angle, tmpx, tmpy;
    dadip_float fi, fj, xdiv, ydiv, xnum, ynum;
    dadip_int i, j, k, newi, newj;
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* the following magic number is from 180 degrees divided by pi */
    radian_angle = angle / 57.29577951;
    cosa = cos(radian_angle);
    sina = sin(radian_angle);

    /* Calculate stretch divide factors for horizontal */
    if (xstretch < 0.00001)
    {
        xdiv = 1.0;
        xnum = 0.0;
    }
    else
    {
        xdiv = xstretch;
        xnum = 1.0;
    }

    /* Calculate stretch divide factors for vertical */
    if (ystretch < 0.00001)
    {
        ydiv = 1.0;
        ynum = 0.0;
    }
    else
    {
        ydiv = ystretch;
        ynum = 1.0;
    }

    /* Perform Geometric Operations */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            fi = i;
            fj = j;

            /* newx = x.cos(a) + y.sin(a) + xdisplace + x.xstretch + x.y.xcross */
            tmpx = (dadip_double)(j) * cosa +
                   (dadip_double)(i) * sina +
                   (dadip_double)(xdisplace) +
                   (dadip_double)(xnum * fj / xdiv) +
                   (dadip_double)(xcross * i * j);

            /* newy = y.cos(a) - x.sin(a) + ydisplace + y.ystretch + x.y.ycross */
            tmpy = (dadip_double)(i) * cosa -
                   (dadip_double)(j) * sina +
                   (dadip_double)(ydisplace) +
                   (dadip_double)(ynum * fi / ydiv) +
                   (dadip_double)(ycross * i * j);

            if (xstretch != 0.0) tmpx = tmpx - (dadip_double)(fj * cosa + fi * sina);
            if (ystretch != 0.0) tmpy = tmpy - (dadip_double)(fi * cosa - fj * sina);

            newj = tmpx;
            newi = tmpy;

            k = 0;
            do
            {
                if (newj < 0 || newj >= WIDTH(inputimg) || newi < 0 || newi >= HEIGHT(inputimg))
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = 0;
                else
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, newi, newj * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to perform the processing to enlarge and shrink an entire image */
DADIP_PTRIMAGE DaDip_Stretch(DADIP_PTRIMAGE inputimg, dadip_float xstretch, dadip_float ystretch)
{
    DADIP_PTRIMAGE outputimg;
    dadip_double tmpx, tmpy;
    dadip_float fi, fj;
    dadip_int i, j, k, new_i, new_j;
    dadip_float bytesperpixel;
    dadip_int newwidth, newheight;

    /* Calculate new resolution */
    newwidth = WIDTH(inputimg) * xstretch;
    newheight = HEIGHT(inputimg) * ystretch;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(newwidth, newheight, DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Perform Stretch Operations */
    for (i = 0; i < newheight; i++)
    {
        for (j = 0; j < newwidth; j++)
        {
            new_i = i / ystretch;
            new_j = j / xstretch;

            k = 0;
            do
            {
                if (new_j < 0 || new_j >= WIDTH(inputimg) || new_i < 0 || new_i >= HEIGHT(inputimg))
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = 0;
                else
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, new_i, new_j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to select the specific area of image */
DADIP_PTRIMAGE DaDip_Crop(DADIP_PTRIMAGE inputimg, dadip_int startrow, dadip_int startcol, dadip_int newheight, dadip_int newwidth)
{
    DADIP_PTRIMAGE outputimg;
    dadip_int i, j, k;
    dadip_float bytesperpixel;

    /* Check the parameters are in range or not */
    if ((startrow < 0 || startrow >= HEIGHT(inputimg)) ||
        (startcol < 0 || startcol >= WIDTH(inputimg)) ||
        (newheight < 0 || newwidth < 0) ||
        ((startrow + newheight) >= HEIGHT(inputimg)) ||
        ((startcol + newwidth) >= WIDTH(inputimg))
        )
    {
        outputimg = NULL;
    }
    else
    {
        /* Create output empty image */
        outputimg = DaDip_Create_Image_Empty(newwidth, newheight, DEPTH(inputimg));
    }
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Copy input image 1 to output image */
    for (i = startrow; i < (newheight + startrow); i++)
    {
        for (j = startcol; j < (newwidth + startcol); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i - startrow, (j - startcol) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to combine 2 input images inside 1 output image */
DADIP_PTRIMAGE DaDip_Paste(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
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
