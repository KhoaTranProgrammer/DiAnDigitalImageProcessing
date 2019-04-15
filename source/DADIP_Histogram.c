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
 * This file implements for methods of image histogram              *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-21-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Calculate_Histogram                                *
 *         DaDip_Free_Histogram                                     *
 *         DaDip_Histogram_Equalization                             *
 *******************************************************************/

#include "DADIP_Histogram.h"

/* Internal function to clear histogram data by zero */
static dadip_void zero_histogram(DADIP_PTRHISTOGRAM histogram)
{
    for (int i = 0; i < histogram->gray_levels; i++)
    {
        histogram->histogramchannel1[i] = 0;
        histogram->histogramchannel2[i] = 0;
        histogram->histogramchannel3[i] = 0;
    }
}

/* Implementation of API to calculate the histogram of input image */
DADIP_PTRHISTOGRAM DaDip_Calculate_Histogram(DADIP_PTRIMAGE inputimg)
{
    dadip_long i, j;
    dadip_short k, pixel;
    DADIP_PTRHISTOGRAM histogram;
    dadip_float bytesperpixel;

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Allocate memory for histogram structure */
    ALLOC_MEM(histogram, DADIP_HISTOGRAM, sizeof(DADIP_HISTOGRAM));
    
    /* Assign gray level */
    histogram->gray_levels = DADIP_GRAY_LEVELS;

    /* Init histogram data by zero */
    zero_histogram(histogram);

    /* Perform calculate histogram */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                pixel = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                if (k == 0) histogram->histogramchannel1[pixel] = histogram->histogramchannel1[pixel] + 1;
                else if(k == 1) histogram->histogramchannel2[pixel] = histogram->histogramchannel2[pixel] + 1;
                else histogram->histogramchannel3[pixel] = histogram->histogramchannel3[pixel] + 1;
                k++;
            } while (k < bytesperpixel);
        }
    }

    return histogram;

ERR_BEG
    FREE_MEM(histogram)
    return NULL;
ERR_END
}

/* Implementation of API to free histogram list */
dadip_void DaDip_Free_Histogram(DADIP_PTRHISTOGRAM histogram)
{
    FREE_MEM(histogram)
    histogram = NULL;
}

/* Implementation of API to perform histogram equalization of input image */
DADIP_PTRIMAGE DaDip_Histogram_Equalization(DADIP_PTRIMAGE inputimg, DADIP_PTRHISTOGRAM histogram, dadip_int gray_levels, dadip_int new_grays)
{
    dadip_int i, j, k, pixel;
    dadip_ulong sum_channel1, sum_channel2, sum_channel3;
    dadip_ulong sum_of_h_channel1[256], sum_of_h_channel2[256], sum_of_h_channel3[256];
    dadip_double constant;
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Calculate histogram summary */
    sum_channel1 = 0;
    sum_channel2 = 0;
    sum_channel3 = 0;
    for (i = 0; i < gray_levels; i++)
    {
        sum_channel1 = sum_channel1 + histogram->histogramchannel1[i];
        sum_of_h_channel1[i] = sum_channel1;

        sum_channel2 = sum_channel2 + histogram->histogramchannel2[i];
        sum_of_h_channel2[i] = sum_channel2;

        sum_channel3 = sum_channel3 + histogram->histogramchannel3[i];
        sum_of_h_channel3[i] = sum_channel3;
    }

    /* constant = new # of gray levels div by area */
    constant = (float)(new_grays) / (float) (HEIGHT(inputimg) * WIDTH(inputimg));
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                pixel = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                if (k == 0) {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = sum_of_h_channel1[pixel] * constant;
                }
                else if (k == 1) {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = sum_of_h_channel2[pixel] * constant;
                }
                else {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = sum_of_h_channel3[pixel] * constant;
                }
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;

ERR_BEG
    if(outputimg != NULL) outputimg->destroy(outputimg);
    return NULL;
ERR_END
}
