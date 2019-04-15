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
 * This file implement several types of basic spatial frequency     *
 * filters                                                          *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-31-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Filter_Image                                       *
 *         DaDip_Median_Filter                                      *
 *        Internal functions:                                       *
 *         Setup_Filters                                            *
 *         Median_Of                                                *
 *******************************************************************/

#include "DADIP_Filter.h"
#include "DADIP_Utility.h"

/*
 * Define the filter masks.
 */
dadip_short lpf_filter_6[3][3] =
{
    { 0, 1, 0 },
    { 1, 2, 1 },
    { 0, 1, 0 }
};

dadip_short lpf_filter_9[3][3] =
{
    { 1, 1, 1 },
    { 1, 1, 1 },
    { 1, 1, 1 }
};

dadip_short lpf_filter_10[3][3] =
{
    { 1, 1, 1 },
    { 1, 2, 1 },
    { 1, 1, 1 }
};

dadip_short lpf_filter_16[3][3] =
{
    { 1, 2, 1 },
    { 2, 4, 2 },
    { 1, 2, 1 }
};

dadip_short lpf_filter_32[3][3] =
{
    { 1,  4,  1 },
    { 4,  12, 4 },
    { 1,  4,  1 }
};

dadip_short hpf_filter_1[3][3] =
{
    { 0,  -1,  0 },
    { -1,  5, -1 },
    { 0,  -1,  0 }
};

dadip_short hpf_filter_2[3][3] =
{
    { -1, -1, -1 },
    { -1,  9, -1 },
    { -1, -1, -1 }
};

dadip_short hpf_filter_3[3][3] =
{
    { 1,  -2,  1 },
    { -2,  5, -2 },
    { 1,  -2,  1 }
};

/* Internal function copies the filter mask into the filter array */
dadip_void Setup_Filters(dadip_int masktype, dadip_int lowhigh, dadip_short filter[3][3])
{
    dadip_int i, j;

    if (lowhigh == 0)
    {
        if (masktype == DADIP_FILTER_6)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    filter[i][j] = lpf_filter_6[i][j];
                }
            }
        }

        if (masktype == DADIP_FILTER_9)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    filter[i][j] = lpf_filter_9[i][j];
                }
            }
        }

        if (masktype == DADIP_FILTER_10)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    filter[i][j] = lpf_filter_10[i][j];
                }
            }
        }

        if (masktype == DADIP_FILTER_16)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    filter[i][j] = lpf_filter_16[i][j];
                }
            }
        }

        if (masktype == DADIP_FILTER_32)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    filter[i][j] = lpf_filter_32[i][j];
                }
            }
        }
    }

    if (lowhigh == 1)
    {
        if (masktype == DADIP_FILTER_1)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    filter[i][j] = hpf_filter_1[i][j];
                }
            }
        }

        if (masktype == DADIP_FILTER_2)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    filter[i][j] = hpf_filter_2[i][j];
                }
            }
        }

        if (masktype == DADIP_FILTER_3)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    filter[i][j] = hpf_filter_3[i][j];
                }
            }
        }
    }
}

/* Implementation of API to filters an image by using a single 3x3 mask */
DADIP_PTRIMAGE DaDip_Filter_Image(DADIP_PTRIMAGE inputimg, dadip_int masktype, dadip_int lowhigh)
{
    DADIP_PTRIMAGE outputimg;
    dadip_int a, b, d, i, j, max, sum, k;
    dadip_short filter[3][3];
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Copy the filter mask */
    Setup_Filters(masktype, lowhigh, filter);

    d = masktype;
    if (masktype == DADIP_FILTER_2 || masktype == DADIP_FILTER_3) d = 1;

    max = GRAY_LEVELS;

    /* Do convolution over image array */
    for (i = 1; i < HEIGHT(inputimg) - 1; i++)
    {
        for (j = 1; j < WIDTH(inputimg) - 1; j++)
        {
            k = 0;
            do
            {
                sum = 0;
                for (a = -1; a < 2 ; a++)
                {
                    for (b = -1; b < 2 ; b++)
                    {
                        sum = sum +
                            PIXELATIMAGE(inputimg, i + a, (j + b) * bytesperpixel + k) *
                            filter[a + 1][b + 1];
                    }
                }
                sum = sum / d;
                if (sum < 0)   sum = 0;
                if (sum > max) sum = max;
                PIXELATIMAGE(outputimg, i, j * bytesperpixel + k) = sum;
            
                k++;
            } while (k < bytesperpixel);
        }
    }

    DaDip_Fill_Boundary(outputimg, 1);

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* Internal function to sorts the elements array and find and return the median value of the elements array */
dadip_short Median_Of(dadip_short* elements, dadip_int count)
{
    dadip_short median;
    DaDip_Sort_Elements(elements, count);
    median = elements[count / 2];
    return median;
}

/* Implementation of API to performs a median filter on an image using a size (3x3, 5x5, ...) */
DADIP_PTRIMAGE DaDip_Median_Filter(DADIP_PTRIMAGE inputimg, dadip_int size)
{
    DADIP_PTRIMAGE outputimg;
    dadip_int a, b, count, i, j, k, sd2, sd2p1, ss;
    dadip_short  elements[128];
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    sd2 = size / 2;
    sd2p1 = sd2 + 1;
    ss = size * size;

    /* Find median over image array */
    for (i = sd2; i < HEIGHT(inputimg) - sd2; i++)
    {
        for (j = sd2; j < WIDTH(inputimg) - sd2; j++)
        {
            k = 0;
            do
            {
                count = 0;
                for (a = -sd2; a < sd2p1; a++)
                {
                    for (b = -sd2; b < sd2p1; b++)
                    {
                        elements[count] = PIXELATIMAGE(inputimg, i + a, (j + b) * bytesperpixel + k);
                        count++;
                    }
                }
                PIXELATIMAGE(outputimg, i, j * bytesperpixel + k) = Median_Of(elements, ss);
                k++;
            } while (k < bytesperpixel);
        }
    }

    DaDip_Fill_Boundary(outputimg, sd2);

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}
