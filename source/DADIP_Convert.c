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
 * This file implements method for image converting                 *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Convert_RGB_To_GrayScale                           *
 *******************************************************************/
#include "DADIP_Convert.h"

/* Implementation of API to convert from RGB to GrayScale image */
DADIP_PTRIMAGE DaDip_Convert_RGB_To_GrayScale(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j;
    DADIP_PTRIMAGE outputimg;
    dadip_char grayvalue;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), 8);
    CHECK_MEM(outputimg)

    /* Perform converting */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            /* Average method */
            grayvalue = (PIXELATIMAGE(inputimg, i, j * 3 + DADIP_R) +
                         PIXELATIMAGE(inputimg, i, j * 3 + DADIP_G) +
                         PIXELATIMAGE(inputimg, i, j * 3 + DADIP_B)) / 3;
            PIXELATIMAGE(outputimg, i, j) = grayvalue;
        }
    }

    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}
