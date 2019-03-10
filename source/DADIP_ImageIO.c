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
 * This file implements for method are declared in DADIP_ImageIO.h  *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Extract_Ushort_From_Buffer                         *
 *         DaDip_Extract_Ulong_From_Buffer                          *
 *         DaDip_Extract_Short_From_Buffer                          *
 *         DaDip_Extract_Long_From_Buffer                           *
 *         DaDip_Insert_Short_Into_Buffer                           *
 *         DaDip_Insert_Ushort_Into_Buffer                          *
 *         DaDip_Insert_Long_Into_Buffer                            *
 *         DaDip_Insert_Ulong_Into_Buffer                           *
 *         DaDip_Allocate_Pixel_Array                               *
 *         DaDip_Free_Pixel_Array                                   *
 *         DaDip_Create_Image_Empty                                 *
 *         DaDip_Create_Image_Copy                                  *
 *         DaDip_Check_Image_Type                                   *
 *         DaDip_Get_Bytes_From_Depth                               *
 *******************************************************************/
#include "DADIP_ImageIO.h"

/* Implementation of API extracts ushort from buffer of 2 bytes */
dadip_ushort DaDip_Extract_Ushort_From_Buffer(dadip_char buffer[], dadip_int lsb, dadip_int start)
{
    union ushort_char_union lcu;

    if (lsb == 1)
    {
        lcu.s_alpha[0] = buffer[start + 0];
        lcu.s_alpha[1] = buffer[start + 1];
    }

    if (lsb == 0)
    {
        lcu.s_alpha[0] = buffer[start + 1];
        lcu.s_alpha[1] = buffer[start + 0];
    }

    return lcu.s_num;
}

/* Implementation of API extracts ulong from buffer of 4 bytes */
dadip_uint DaDip_Extract_Ulong_From_Buffer(dadip_char buffer[], dadip_int lsb, dadip_int start)
{
    union ulong_char_union lcu;

    if (lsb == 1)
    {
        lcu.l_alpha[0] = buffer[start + 0];
        lcu.l_alpha[1] = buffer[start + 1];
        lcu.l_alpha[2] = buffer[start + 2];
        lcu.l_alpha[3] = buffer[start + 3];
    }

    if (lsb == 0) {
        lcu.l_alpha[0] = buffer[start + 3];
        lcu.l_alpha[1] = buffer[start + 2];
        lcu.l_alpha[2] = buffer[start + 1];
        lcu.l_alpha[3] = buffer[start + 0];
    }

    return lcu.l_num;
}

/* Implementation of API extracts short from buffer of 2 bytes */
dadip_short DaDip_Extract_Short_From_Buffer(dadip_char buffer[], dadip_int lsb, dadip_int start)
{
    union short_char_union lcu;

    if (lsb == 1)
    {
        lcu.s_alpha[0] = buffer[start + 0];
        lcu.s_alpha[1] = buffer[start + 1];
    }

    if (lsb == 0)
    {
        lcu.s_alpha[0] = buffer[start + 1];
        lcu.s_alpha[1] = buffer[start + 0];
    }

    return lcu.s_num;
}

/* Implementation of API extracts long from buffer of 4 bytes */
dadip_long DaDip_Extract_Long_From_Buffer(dadip_char buffer[], dadip_int lsb, dadip_int start)
{
    union long_char_union lcu;

    if (lsb == 1)
    {
        lcu.l_alpha[0] = buffer[start + 0];
        lcu.l_alpha[1] = buffer[start + 1];
        lcu.l_alpha[2] = buffer[start + 2];
        lcu.l_alpha[3] = buffer[start + 3];
    }

    if (lsb == 0)
    {
        lcu.l_alpha[0] = buffer[start + 3];
        lcu.l_alpha[1] = buffer[start + 2];
        lcu.l_alpha[2] = buffer[start + 1];
        lcu.l_alpha[3] = buffer[start + 0];
    }

    return lcu.l_num;
}

/* Implementation of API converts short to buffer of 2 bytes */
dadip_void DaDip_Insert_Short_Into_Buffer(dadip_char buffer[], dadip_int start, dadip_short number)
{
    union short_char_union lsu;

    lsu.s_num = number;
    buffer[start + 0] = lsu.s_alpha[0];
    buffer[start + 1] = lsu.s_alpha[1];
}

/* Implementation of API converts ushort to buffer of 2 bytes */
dadip_void DaDip_Insert_Ushort_Into_Buffer(dadip_char buffer[], dadip_int start, dadip_ushort number)
{
    union ushort_char_union lsu;

    lsu.s_num = number;
    buffer[start + 0] = lsu.s_alpha[0];
    buffer[start + 1] = lsu.s_alpha[1];
}

/* Implementation of API converts long to buffer of 4 bytes */
dadip_void DaDip_Insert_Long_Into_Buffer(dadip_char buffer[], dadip_int start, dadip_long number)
{
    union long_char_union lsu;

    lsu.l_num = number;
    buffer[start + 0] = lsu.l_alpha[0];
    buffer[start + 1] = lsu.l_alpha[1];
    buffer[start + 2] = lsu.l_alpha[2];
    buffer[start + 3] = lsu.l_alpha[3];
}

/* Implementation of API converts ulong to buffer of 4 bytes */
dadip_void DaDip_Insert_Ulong_Into_Buffer(dadip_char buffer[], dadip_int start, dadip_ulong number)
{
    union ulong_char_union lsu;

    lsu.l_num = number;
    buffer[start + 0] = lsu.l_alpha[0];
    buffer[start + 1] = lsu.l_alpha[1];
    buffer[start + 2] = lsu.l_alpha[2];
    buffer[start + 3] = lsu.l_alpha[3];
}

/* Implementation of API to create the blank pixel array */
DADIP_ARRAY DaDip_Allocate_Pixel_Array(dadip_int width, dadip_int height, dadip_short depth)
{
    DADIP_ARRAY pixelarray;
    dadip_float bytesperpixel;
    dadip_int i, j, k;
    
    pixelarray = NULL;

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(depth);

    /* Allocate memory for pixel array */
    ALLOC_MEM(pixelarray, dadip_uchar, height * width * sizeof(dadip_uchar) * bytesperpixel)

    /* Clear pixel array */
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            k = 0;
            do
            {
                PIXELATARRAY(pixelarray, i, j * (int)bytesperpixel + k, width, height, depth) = 0;
                k++;
            } while (k < bytesperpixel);
        }
    }

    return pixelarray;
ERR_BEG
    DaDip_Free_Pixel_Array(pixelarray);
    return NULL;
ERR_END
}

/* Implementation of API to free the pixel array */
dadip_void DaDip_Free_Pixel_Array(DADIP_ARRAY pixelarray)
{
    FREE_MEM(pixelarray)
}

/* Default Destroy method of base image */
static dadip_void Destroy_Image(DADIP_PTRIMAGE img)
{
    CHECK_MEM(img)
    DaDip_Free_Pixel_Array(img->pixelarray);
    FREE_MEM(img)
    img = NULL;

ERR_BEG
    return;
ERR_END
}

/* Implementation of API to create the blank base image */
DADIP_PTRIMAGE DaDip_Create_Image_Empty(dadip_int width, dadip_int height, dadip_short depth)
{
    DADIP_PTRIMAGE outputimg;

    outputimg = NULL;

    /* Allocate image structure */
    ALLOC_MEM(outputimg, DADIP_IMAGE, sizeof(DADIP_IMAGE))

    /* Assign Global elements of image */
    outputimg->width = width;
    outputimg->height = height;
    outputimg->depth = depth;
    outputimg->destroy = Destroy_Image;

    /* Create the blank pixel array */
    outputimg->pixelarray = DaDip_Allocate_Pixel_Array(width, height, depth);
    CHECK_MEM(outputimg->pixelarray)

    return outputimg;
ERR_BEG
    Destroy_Image(outputimg);
    return NULL;
ERR_END
}

/* Implementation of API to create the image with base image data is copied from input image */
DADIP_PTRIMAGE DaDip_Create_Image_Copy(DADIP_PTRIMAGE inputimg)
{
    DADIP_PTRIMAGE outputimg;
    dadip_float bytesperpixel;
    dadip_int i, j, k;
    
    outputimg = NULL;

    /* Allocate image structure */
    ALLOC_MEM(outputimg, DADIP_IMAGE, sizeof(DADIP_IMAGE))

    /* Assign Global elements of image */
    outputimg->width = WIDTH(inputimg);
    outputimg->height = HEIGHT(inputimg);
    outputimg->depth = DEPTH(inputimg);
    outputimg->destroy = Destroy_Image;

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Allocate memory for pixel array */
    ALLOC_MEM(outputimg->pixelarray, dadip_uchar, HEIGHT(inputimg) * WIDTH(inputimg) * sizeof(dadip_uchar) * bytesperpixel)

    /* Copy input image to output image */
    for (i = 0; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATIMAGE(outputimg, i, j * (int)bytesperpixel + k) = PIXELATIMAGE(inputimg, i, j * (int)bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    return outputimg;
ERR_BEG
    Destroy_Image(outputimg);
    return NULL;
ERR_END
}

/* Implementation of API to find the type of image */
dadip_errinfo DaDip_Check_Image_Type(DADIP_2DPTRIMAGE inputimg, dadip_char* input)
{
    if (DaDip_Is_Bmp(inputimg, input) == DADIP_OK) /* In case of BMP image */
    {
        (*inputimg)->imagetype = DADIP_BMP;
        return DADIP_OK;
    }

    return DADIP_UNSUPPORTFORMAT;
}

/* Implementation of API to calculate the number of bytes per pixel */
dadip_float DaDip_Get_Bytes_From_Depth(dadip_short depth)
{
    dadip_float bytesperpixel = 1.0;

    switch (depth)
    {
    case 1:
        bytesperpixel = 0.125;
        break;
    case 4:
        bytesperpixel = 0.5;
        break;
    case 8:
        bytesperpixel = 1.0;
        break;
    case 16:
        bytesperpixel = 2.0;
        break;
    case 24:
        bytesperpixel = 3.0;
        break;
    case 32:
        bytesperpixel = 4.0;
        break;
    default:
        bytesperpixel = 1.0;
        break;
    }

    return bytesperpixel;
}
