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
 * This file defines some data structures and method to perform     *
 * image histogram such as calculate histogram, free histogram and  *
 * histogram equalization                                           *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-21-2019                                               *
 *        Initial version includes histogram structure, declaration *
 *        of calculate histogram, free histogram and histogram      *
 *        equalization                                              *
 *******************************************************************/

#ifndef DADIP_HISTOGRAM_H
#define DADIP_HISTOGRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

#define DADIP_GRAY_LEVELS 256

typedef struct _dip_histogram
{
    dadip_int gray_levels;
    dadip_ulong histogramchannel1[DADIP_GRAY_LEVELS];
    dadip_ulong histogramchannel2[DADIP_GRAY_LEVELS];
    dadip_ulong histogramchannel3[DADIP_GRAY_LEVELS];
} DADIP_HISTOGRAM, *DADIP_PTRHISTOGRAM;

/*
 * Function: DaDip_Calculate_Histogram
 * --------------------
 * API to calculate the histogram of input image
 *
 *  inputimg(I): input image
 *
 *  return: histogram structure
 */
DADIP_PTRHISTOGRAM DaDip_Calculate_Histogram(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Free_Histogram
 * --------------------
 * API to free histogram list
 *
 *  histogram(I): histogram structure
 */
dadip_void DaDip_Free_Histogram(DADIP_PTRHISTOGRAM histogram);

/*
 * Function: DaDip_Histogram_Equalization
 * --------------------
 * API to perform histogram equalization of input image
 *
 *  inputimg(I): input image
 *
 *  histogram(I): histogram structure
 *
 *  gray_levels(I): gray level
 *
 *  new_grays(I): new gray level
 */
DADIP_PTRIMAGE DaDip_Histogram_Equalization(DADIP_PTRIMAGE inputimg, DADIP_PTRHISTOGRAM histogram, dadip_int gray_levels, dadip_int new_grays);

#ifdef __cplusplus
}
#endif

#endif /* DADIP_HISTOGRAM_H */
