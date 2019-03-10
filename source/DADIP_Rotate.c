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
 * This file implements method for image rotation                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Flip_Vertical                                      *
 *         DaDip_Flip_Horizontal                                    *
 *         DaDip_Rotation_90_Degree                                 *
 *         DaDip_Rotation_180_Degree                                *
 *         DaDip_Rotation_270_Degree                                *
 *         DaDip_Rotation                                           *
 *******************************************************************/

#include "DADIP_Rotate.h"

/* Implementation of API to perform Flip image as vertical */
DADIP_PTRIMAGE DaDip_Flip_Vertical(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j, k, rd2;
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Perform top half vertical */
    rd2 = HEIGHT(inputimg) / 2;
    for (i = 0; i < rd2; i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, HEIGHT(outputimg) - 1 - i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Perform bottom half vertical */
    for (i = rd2; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, HEIGHT(outputimg) - 1 - i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to perform Flip image as horizontal */
DADIP_PTRIMAGE DaDip_Flip_Horizontal(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j, k, cd2;
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Perform left half vertical */
    cd2 = WIDTH(inputimg) / 2;
    for (j = 0; j < cd2; j++)
    {
        for (i = 0; i < HEIGHT(inputimg); i++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, (WIDTH(inputimg) - 1 - j) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Perform right half vertical */
    for (j = cd2; j < WIDTH(inputimg); j++)
    {
        for (i = 0; i < HEIGHT(inputimg); i++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, (WIDTH(inputimg) - 1 - j) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to perform 90 degree rotation */
DADIP_PTRIMAGE DaDip_Rotation_90_Degree(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(HEIGHT(inputimg), WIDTH(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Perform Rotation 90 Degree */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, j, (HEIGHT(inputimg) - 1 - i) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to perform 180 degree rotation */
DADIP_PTRIMAGE DaDip_Rotation_180_Degree(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
        
    /* Perform Rotation 180 Degree */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, HEIGHT(inputimg) - i, (WIDTH(inputimg) - j) * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to perform 270 degree rotation */
DADIP_PTRIMAGE DaDip_Rotation_270_Degree(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(HEIGHT(inputimg), WIDTH(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Perform Rotation 90 Degree */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, j, (HEIGHT(inputimg) - 1 - i) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, HEIGHT(inputimg) - i, (WIDTH(inputimg) - j) * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Implementation of API to perform rotation in any point of origin */
DADIP_PTRIMAGE DaDip_Rotation(DADIP_PTRIMAGE inputimg, dadip_int m, dadip_int n, dadip_float angle)
{
    dadip_int i, j, k, new_y, new_x;
    dadip_double cosa, sina, radian_angle;
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;
    
    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Convert Degree to Radian */
    radian_angle = angle / 57.2958;

    cosa = DADIP_COS(radian_angle);
    sina = DADIP_SIN(radian_angle);

    /* Perform Rotation By Any Degree */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            /* new x = x.cos(a) - y.sin(a) -m.cos(a) + m + n.sin(a) */
            new_x = (dadip_double)(j)*cosa - (dadip_double)(i)*sina
                  - (dadip_double)(m)*cosa + (dadip_double)(m) + (dadip_double)(n)*sina;

            /*new y = y.cos(a) + x.sin(a) - m.sin(a) - n.cos(a) + n */
            new_y = (dadip_double)(i)*cosa + (dadip_double)(j)*sina
                  - (dadip_double)(m)*sina - (dadip_double)(n)*cosa + (dadip_double)(n);
            
            k = 0;
            do
            {
                if (new_x < 0 || new_x >= WIDTH(inputimg) ||
                    new_y < 0 || new_y >= HEIGHT(inputimg))
                {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = 0;
                }
                else
                {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, new_y, new_x * (int)bytesperpixel + k);
                }
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}
