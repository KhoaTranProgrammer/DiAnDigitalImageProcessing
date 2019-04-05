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
 * This file implements the methods of the Warping Technique        *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-03-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Warp                                               *
 *         DaDip_Object_Warp                                        *
 *        Internal functions:                                       *
 *         Warp_Loop                                                *
 *         Full_Warp_Loop                                           *
 *******************************************************************/

#include "DADIP_Warping.h"

/* Internal function sets up the coefficients and loops through a quarter of
   the rowsxcols section of the image that is being warped */
void Warp_Loop(DADIP_PTRIMAGE inputimg, DADIP_PTRIMAGE outputimg,
               dadip_int x1, dadip_int x2, dadip_int x3, dadip_int x4,
               dadip_int y1, dadip_int y2, dadip_int y3, dadip_int y4,
               dadip_int extrax, dadip_int extray)
{
    dadip_int colsdiv2, denom, i, j, rowsdiv2,
        xa, xb, xab, xout, ya, yb, yab, yout, k;
    dadip_int bytesperpixel;

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    colsdiv2 = WIDTH(inputimg) / 2;
    rowsdiv2 = HEIGHT(inputimg) / 2;
    denom = colsdiv2 * rowsdiv2;

    /* Set up the terms for the spatial transformation. */
    xa = x2 - x1;
    xb = x4 - x1;
    xab = x1 - x2 + x3 - x4;

    ya = y2 - y1;
    yb = y4 - y1;
    yab = y1 - y2 + y3 - y4;

    /* Loop through a quadrant and perform the spatial transformation. */
    for (i = 0; i < rowsdiv2; i++)
    {
        for (j = 0; j < colsdiv2; j++)
        {
            xout = x1 + (xa * j) / colsdiv2 +
                (xb * i) / rowsdiv2 + (xab * i * j) / (denom);
            yout = y1 + (ya * j) / colsdiv2 +
                (yb * i) / rowsdiv2 + (yab * i * j) / (denom);

            k = 0;
            do
            {
                if (xout < 0 || xout >= WIDTH(inputimg) || yout < 0 || yout >= HEIGHT(inputimg))
                    PIXELATIMAGE(outputimg, i + extray, (j + extrax) * bytesperpixel + k) = GRAY_LEVELS / 2;
                else
                    PIXELATIMAGE(outputimg, i + extray, (j + extrax) * bytesperpixel + k) = PIXELATIMAGE(inputimg, yout, xout * bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }
}

/* Implementation of API to warps a rowsxcols section of an image by using control points(x,y) */
DADIP_PTRIMAGE DaDip_Warp(DADIP_PTRIMAGE inputimg, dadip_int xcontrol, dadip_int ycontrol)
{
    DADIP_PTRIMAGE outputimg;
    dadip_int colsdiv2, extrax, extray, i, j,
              rowsdiv2, x1, x2, x3, x4, y1, y2, y3, y4;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    colsdiv2 = WIDTH(inputimg) / 2;
    rowsdiv2 = HEIGHT(inputimg) / 2;

    /* 1 - upper left quarter */
    x1 = 0;
    x2 = colsdiv2;
    x3 = xcontrol;
    x4 = 0;

    y1 = 0;
    y2 = 0;
    y3 = ycontrol;
    y4 = rowsdiv2;

    extrax = 0;
    extray = 0;

    Warp_Loop(inputimg, outputimg, x1, x2, x3, x4,
            y1, y2, y3, y4, extrax, extray);

    /* 2 - upper right quarter */
    x1 = colsdiv2;
    x2 = WIDTH(inputimg) - 1;
    x3 = WIDTH(inputimg) - 1;
    x4 = xcontrol;

    y1 = 0;
    y2 = 0;
    y3 = rowsdiv2;
    y4 = ycontrol;

    extrax = colsdiv2;
    extray = 0;

    Warp_Loop(inputimg, outputimg, x1, x2, x3, x4,
            y1, y2, y3, y4, extrax, extray);

    /* 3 - lower right quarter */
    x1 = xcontrol;
    x2 = WIDTH(inputimg) - 1;
    x3 = WIDTH(inputimg) - 1;
    x4 = colsdiv2;

    y1 = ycontrol;
    y2 = rowsdiv2;
    y3 = HEIGHT(inputimg) - 1;
    y4 = HEIGHT(inputimg) - 1;

    extrax = colsdiv2;
    extray = rowsdiv2;

    Warp_Loop(inputimg, outputimg, x1, x2, x3, x4,
            y1, y2, y3, y4, extrax, extray);

    /* 4 - lower left quarter */
    x1 = 0;
    x2 = xcontrol;
    x3 = colsdiv2;
    x4 = 0;

    y1 = rowsdiv2;
    y2 = ycontrol;
    y3 = HEIGHT(inputimg) - 1;
    y4 = HEIGHT(inputimg) - 1;

    extrax = 0;
    extray = rowsdiv2;

    Warp_Loop(inputimg, outputimg, x1, x2, x3, x4,
            y1, y2, y3, y4, extrax, extray);

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Internal function sets up the coefficients and loops through an entire
   rowsxcols image that is being warped */
void Full_Warp_Loop(DADIP_PTRIMAGE inputimg, DADIP_PTRIMAGE outputimg,
    dadip_int x1, dadip_int x2, dadip_int x3, dadip_int x4,
    dadip_int y1, dadip_int y2, dadip_int y3, dadip_int y4,
    dadip_int extrax, dadip_int extray)
{
    dadip_int colsdiv2, denom, i, j, rowsdiv2,
        xa, xb, xab, xout, ya, yb, yab, yout, k;
    dadip_int bytesperpixel;

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    denom = WIDTH(inputimg) * HEIGHT(inputimg);

    /* Set up the terms for the spatial transformation */
    xa = x2 - x1;
    xb = x4 - x1;
    xab = x1 - x2 + x3 - x4;

    ya = y2 - y1;
    yb = y4 - y1;
    yab = y1 - y2 + y3 - y4;

    /* Loop through the image and perform the spatial transformation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            xout = x1 + (xa * j) / WIDTH(inputimg) +
                (xb * i) / HEIGHT(inputimg) + (xab * i * j) / (denom);
            yout = y1 + (ya * j) / WIDTH(inputimg) +
                (yb * i) / HEIGHT(inputimg) + (yab * i * j) / (denom);

            k = 0;
            do
            {
                if (xout < 0 || xout >= WIDTH(inputimg) || yout < 0 || yout >= HEIGHT(inputimg))
                    PIXELATIMAGE(outputimg, i + extray, (j + extrax) * bytesperpixel + k) = GRAY_LEVELS / 2;
                else
                    PIXELATIMAGE(outputimg, i + extray, (j + extrax) * bytesperpixel + k) = PIXELATIMAGE(inputimg, yout, xout * bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

}

/* Implementation of API to warps a rowsxcols section of an image by using four corners of a four side figure */
DADIP_PTRIMAGE DaDip_Object_Warp(DADIP_PTRIMAGE inputimg,
                                dadip_int x1, dadip_int y1, dadip_int x2, dadip_int y2,
                                dadip_int x3, dadip_int y3, dadip_int x4, dadip_int y4)
{
    DADIP_PTRIMAGE outputimg;
    dadip_int extrax, extray;

    extrax = 0;
    extray = 0;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Sets up the coefficients and loops through an entire rowsxcols image */
    Full_Warp_Loop(inputimg, outputimg, x1, x2, x3, x4, y1, y2, y3, y4, extrax, extray);

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}
