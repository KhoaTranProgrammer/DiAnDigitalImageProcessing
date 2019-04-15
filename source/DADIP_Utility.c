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
 * This file implements some common functions                       *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-31-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Fill_Boundary                                      *
 *         DaDip_Sort_Elements                                      *
 *        Internal functions:                                       *
 *         swap                                                     *
 *******************************************************************/

#include "DADIP_Utility.h"

/* Implementation of API to add the pixel data for the boundary of image */
dadip_void DaDip_Fill_Boundary(DADIP_PTRIMAGE inputimg, dadip_int length)
{
    dadip_int i, j, k;
    dadip_float bytesperpixel;

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Fill up four corners */
    for (i = length; i > 0; i--)
    {
        k = 0;
        do
        {
            PIXELATIMAGE(inputimg, i - 1, (i - 1) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, i * (int)bytesperpixel + k);
            PIXELATIMAGE(inputimg, i - 1, ((WIDTH(inputimg) - 1) - (i - 1)) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, ((WIDTH(inputimg) - 1) - 1 - (i - 1)) * (int)bytesperpixel + k);
            PIXELATIMAGE(inputimg, (HEIGHT(inputimg) - 1) - (i - 1), (i - 1) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, (HEIGHT(inputimg) - 1) - 1 - (i - 1), i * (int)bytesperpixel + k);
            PIXELATIMAGE(inputimg, (HEIGHT(inputimg) - 1) - (i - 1), ((WIDTH(inputimg) - 1) - (i - 1)) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, (HEIGHT(inputimg) - 1) - 1 - (i - 1), ((WIDTH(inputimg) - 1) - 1 - (i - 1)) * (int)bytesperpixel + k);
            k++;
        } while (k < bytesperpixel);
    }

    /* Fill up left & right */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = length; j > 0; j--)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(inputimg, i, (j - 1) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                PIXELATIMAGE(inputimg, i, (WIDTH(inputimg) - j) * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, (WIDTH(inputimg) - j - 1) * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Fill up top & down */
    for (j = 0; j < WIDTH(inputimg); j++)
    {
        for (i = length; i > 0; i--)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(inputimg, i - 1, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                PIXELATIMAGE(inputimg, HEIGHT(inputimg) - i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, HEIGHT(inputimg) - i - 1, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }
}

/* Internal function to swap between 2 numbers */
static dadip_void swap(dadip_short* a, dadip_short* b)
{
    dadip_short temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/* Implementation of API to performs a simple bubble sort on the list of elements */
dadip_void DaDip_Sort_Elements(dadip_short* elements, dadip_int count)
{
    dadip_int i, j;
    j = count;
    while (j-- > 1)
    {
        for (i = 0; i < j; i++)
        {
            if (elements[i] > elements[i + 1])
                swap(&elements[i], &elements[i + 1]);
        }
    }
}
