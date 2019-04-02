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
 * This file defines some methods to implement several types of     *
 * basic spatial frequency filters                                  *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-31-2019                                               *
 *        Initial version includes filter with single 3x3 mask and  *
 *        median filter                                             *
 *******************************************************************/

#ifndef DADIP_FILTER_H
#define DADIP_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

/* Enum of mask type */
enum
{
    DADIP_FILTER_1 = 1,
    DADIP_FILTER_2 = 2,
    DADIP_FILTER_3 = 3,
    DADIP_FILTER_6 = 6,
    DADIP_FILTER_9 = 9,
    DADIP_FILTER_10 = 10,
    DADIP_FILTER_16 = 16,
    DADIP_FILTER_32 = 32
};

/*
 * Function: DaDip_Filter_Image
 * --------------------
 * API to filters an image by using a single 3x3 mask
 *
 *  inputimg(I): input image
 *
 *  masktype(I): mask type
 *
 *  lowhigh(I): filter type
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Filter_Image(DADIP_PTRIMAGE inputimg, dadip_int masktype, dadip_int lowhigh);

/*
 * Function: DaDip_Median_Filter
 * --------------------
 * API to performs a median filter on an image using a size (3x3, 5x5, ...)
 *
 *  inputimg(I): input image
 *
 *  size(I): filter size
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Median_Filter(DADIP_PTRIMAGE inputimg, dadip_int size);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_FILTER_H */
