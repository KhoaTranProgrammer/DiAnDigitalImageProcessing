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
 * This file implements method for mathematic operation             *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-30-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Math_Add                                           *
 *         DaDip_Math_Subtract                                      *
 *         DaDip_Math_And                                           *
 *         DaDip_Math_Or                                            *
 *         DaDip_Math_Xor                                           *
 *         DaDip_Math_Not                                           *
 *         DaDip_Math_Nand                                          *
 *         DaDip_Math_Nor                                           *
 *******************************************************************/
#include "DADIP_Math.h"

/* API to implement the basic algebra function Add */
DADIP_PTRIMAGE DaDip_Math_Add(DADIP_PTRIMAGE inputimg, dadip_ushort value)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
    
    /* Perform Add operation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                int result = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k) + value;
                if(result > GRAY_LEVELS)
                {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = GRAY_LEVELS;
                }
                else
                {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = result;
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

/* API to implement the basic algebra function Subtract */
DADIP_PTRIMAGE DaDip_Math_Subtract(DADIP_PTRIMAGE inputimg, dadip_ushort value)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
    
    /* Perform Subtract operation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                int result = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k) - value;
                if(result < 0)
                {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = 0;
                }
                else
                {
                    PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = result;
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

/* API to implement the basic algebra function And */
DADIP_PTRIMAGE DaDip_Math_And(DADIP_PTRIMAGE inputimg, dadip_ushort value)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
    
    /* Perform And operation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k) & value;
                k++;
            } while (k < bytesperpixel);
        }
    }
    
    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* API to implement the basic algebra function Or */
DADIP_PTRIMAGE DaDip_Math_Or(DADIP_PTRIMAGE inputimg, dadip_ushort value)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
    
    /* Perform Or operation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k) | value;
                k++;
            } while (k < bytesperpixel);
        }
    }
    
    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* API to implement the basic algebra function Xor */
DADIP_PTRIMAGE DaDip_Math_Xor(DADIP_PTRIMAGE inputimg, dadip_ushort value)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
    
    /* Perform Xor operation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k) ^ value;
                k++;
            } while (k < bytesperpixel);
        }
    }
    
    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* API to implement the basic algebra function Not */
DADIP_PTRIMAGE DaDip_Math_Not(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
    
    /* Perform Not operation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = ~PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }
    
    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* API to implement the basic algebra function Nand */
DADIP_PTRIMAGE DaDip_Math_Nand(DADIP_PTRIMAGE inputimg, dadip_ushort value)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
    
    /* Perform Nand operation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = ~(PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k) & value);
                k++;
            } while (k < bytesperpixel);
        }
    }
    
    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}

/* API to implement the basic algebra function Nor */
DADIP_PTRIMAGE DaDip_Math_Nor(DADIP_PTRIMAGE inputimg, dadip_ushort value)
{
    dadip_int i, j, k;
    DADIP_PTRIMAGE outputimg;
    dadip_int bytesperpixel;

    /* Create output empty image */
    outputimg = DaDip_Create_Image_Empty(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM(outputimg)

    /* Calculate number of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));
    
    /* Perform Nor operation */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = ~(PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k) | value);
                k++;
            } while (k < bytesperpixel);
        }
    }
    
    return outputimg;
ERR_BEG
    return NULL;
ERR_END
}
