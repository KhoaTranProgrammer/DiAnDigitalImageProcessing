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
 * This file defines some data structures and method for some basic *
 * operations to image such as Basic image structure, extract/insert*
 * data from/to buffer, create empty image, copy image, pixel array *
 * manipulation, image type checking, count bytes used for 1 pixel  *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version includes Basic image structure, buffer    *
 *        conversion, create/copy image, pixel array manipulation,  *
 *        image type checking, count bytes used for 1 pixel         *
 *******************************************************************/

#ifndef DADIP_IMAGEIO_H
#define DADIP_IMAGEIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_Type.h"
#include "DADIP_FileIO.h"

/* Types of image */
enum
{
    DADIP_GRAY,
    DADIP_BMP
};

/* RGB index */
enum
{
    DADIP_R = 0,
    DADIP_G = 1,
    DADIP_B = 2,
};

/* RGB structure */
typedef struct _dadip_rgb
{
    dadip_uchar red;
    dadip_uchar green;
    dadip_uchar blue;
} DADIP_RGB;

#define DADIP_ARRAY     dadip_uchar* /* Data type of pixel array */
#define GRAY_LEVELS     255          /* Gray levels */
#define HEIGHT(img)     img->height  /* Get height from image */
#define WIDTH(img)      img->width   /* Get width from image */
#define DEPTH(img)      img->depth   /* Get depth from image */

/* Access data at specific location(row, column) in pixel array */
#define PIXELATARRAY(pixelarray, row, col, w, h, d)      pixelarray[(row) * (w) * (int)DaDip_Get_Bytes_From_Depth(d) + (col)]

/* Access data at specific location(row, column) in image */
#define PIXELATIMAGE(img, row, col)     img->pixelarray[(row) * WIDTH(img) * (int)DaDip_Get_Bytes_From_Depth(DEPTH(img)) + (col)]

/* Base image with some global elements */
#define DADIP_BASEIMAGE                                                             \
    dadip_uint    imagetype;        /* Type of image */                             \
    dadip_int     width;            /* Image width */                               \
    dadip_int     height;           /* Image height */                              \
    dadip_ushort depth;             /* Total bits for 1 pixel. Support: 8, 24 */    \
    DADIP_ARRAY pixelarray;         /* Image pixels in 1 dimension array */         \
    DADIP_PTRFILEREADER filereader;   /* File reader handle */                      \
    DADIP_PTRFILEWRITER filewriter;   /* File writer handle */                      \
    dadip_errinfo (*parseImage)(struct _dadip_image* me); /* Extract image  */      \
    dadip_void (*destroy)(struct _dadip_image* me); /* Destroy image data */        \

/* Basic image structure */
typedef struct _dadip_image
{
    DADIP_BASEIMAGE /* Global elements */
} DADIP_IMAGE, *DADIP_PTRIMAGE, **DADIP_2DPTRIMAGE;

/* Union to convert between short & char */
union short_char_union
{
    dadip_short s_num;
    dadip_char  s_alpha[2];
};

/* Union to convert between int & char */
union int_char_union
{
    dadip_int  i_num;
    dadip_char i_alpha[2];
};

/* Union to convert between long & char */
union long_char_union
{
    dadip_long  l_num;
    dadip_char  l_alpha[4];
};

/* Union to convert between float & char */
union float_char_union
{
    dadip_float f_num;
    dadip_char  f_alpha[4];
};

/* Union to convert between ushort & char */
union ushort_char_union
{
    dadip_short s_num;
    dadip_char  s_alpha[2];
};

/* Union to convert between unit & char */
union uint_char_union
{
    dadip_int  i_num;
    dadip_char i_alpha[2];
};

/* Union to convert between ulong & char */
union ulong_char_union
{
    dadip_long  l_num;
    dadip_char  l_alpha[4];
};

/*
 * Function: DaDip_Extract_Ushort_From_Buffer
 * --------------------
 * API extracts ushort from buffer of 2 bytes. Supports MSB/LSB
 *
 *  buffer(I): input buffer
 *
 *  lsb(I): 0 is MSB, 1 is LSB
 *
 *  start(I): starting point in buffer
 *
 *  returns: unsigned short number
 */
dadip_ushort DaDip_Extract_Ushort_From_Buffer(dadip_char buffer[], dadip_int lsb, dadip_int start);

/*
 * Function: DaDip_Extract_Ulong_From_Buffer
 * --------------------
 * API extracts ulong from buffer of 4 bytes. Supports MSB/LSB
 *
 *  buffer(I): input buffer
 *
 *  lsb(I): 0 is MSB, 1 is LSB
 *
 *  start(I): starting point in buffer
 *
 *  returns: unsigned integer number
 */
dadip_uint DaDip_Extract_Ulong_From_Buffer(dadip_char buffer[], dadip_int lsb, dadip_int start);

/*
 * Function: DaDip_Extract_Short_From_Buffer
 * --------------------
 * API extracts short from buffer of 2 bytes. Supports MSB/LSB
 *
 *  buffer(I): input buffer
 *
 *  lsb(I): 0 is MSB, 1 is LSB
 *
 *  start(I): starting point in buffer
 *
 *  returns: short number
 */
dadip_short DaDip_Extract_Short_From_Buffer(dadip_char buffer[], dadip_int lsb, dadip_int start);

/*
 * Function: DaDip_Extract_Long_From_Buffer
 * --------------------
 * API extracts long from buffer of 4 bytes. Supports MSB/LSB
 *
 *  buffer(I): input buffer
 *
 *  lsb(I): 0 is MSB, 1 is LSB
 *
 *  start(I): starting point in buffer
 *
 *  returns: long number
 */
dadip_long DaDip_Extract_Long_From_Buffer(dadip_char buffer[], dadip_int lsb, dadip_int start);

/*
 * Function: DaDip_Insert_Short_Into_Buffer
 * --------------------
 * API converts short to buffer of 2 bytes
 *
 *  buffer(I/O): output buffer
 *
 *  start(I): starting point in buffer
 *
 *  number(I): input number
 */
dadip_void DaDip_Insert_Short_Into_Buffer(dadip_char buffer[], dadip_int start, dadip_short number);

/*
 * Function: DaDip_Insert_Ushort_Into_Buffer
 * --------------------
 * API converts ushort to buffer of 2 bytes
 *
 *  buffer(I/O): output buffer
 *
 *  start(I): starting point in buffer
 *
 *  number(I): input number
 */
dadip_void DaDip_Insert_Ushort_Into_Buffer(dadip_char buffer[], dadip_int start, dadip_ushort number);

/*
 * Function: DaDip_Insert_Long_Into_Buffer
 * --------------------
 * API converts long to buffer of 4 bytes
 *
 *  buffer(I/O): output buffer
 *
 *  start(I): starting point in buffer
 *
 *  number(I): input number
 */
dadip_void DaDip_Insert_Long_Into_Buffer(dadip_char buffer[], dadip_int start, dadip_long number);

/*
 * Function: DaDip_Insert_Ulong_Into_Buffer
 * --------------------
 * API converts ulong to buffer of 4 bytes
 *
 *  buffer(I/O): output buffer
 *
 *  start(I): starting point in buffer
 *
 *  number(I): input number
 */
dadip_void DaDip_Insert_Ulong_Into_Buffer(dadip_char buffer[], dadip_int start, dadip_ulong number);

/*
 * Function: DaDip_Allocate_Pixel_Array
 * --------------------
 * API to create the blank pixel array
 *
 *  width/height(I): image resolution
 *
 *  depth(I): bits per pixel
 *
 *  returns: array with defaul value is 0 for each pixel
 */
DADIP_ARRAY DaDip_Allocate_Pixel_Array(dadip_int width, dadip_int height, dadip_short depth);

/*
 * Function: DaDip_Free_Pixel_Array
 * --------------------
 * API to free the pixel array
 *
 *  pixelarray(I): input pixel array
 */
dadip_void DaDip_Free_Pixel_Array(DADIP_ARRAY pixelarray);

/*
 * Function: DaDip_Create_Image_Empty
 * --------------------
 * API to create the blank base image
 *
 *  width/height(I): image resolution
 *
 *  depth(I): bits per pixel
 *
 *  return: blank base image
 */
DADIP_PTRIMAGE DaDip_Create_Image_Empty(dadip_int width, dadip_int height, dadip_short depth);

/*
 * Function: DaDip_Create_Image_Copy
 * --------------------
 * API to create the image with base image data is copied from input image
 *
 *  inputimg(I): input image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Create_Image_Copy(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Check_Image_Type
 * --------------------
 * API to find the type of image
 *
 *  inputimg(I/O): image with some global elements: imagetype, filesize, filereader, parseImage, destroy
 *  
 *  input(I): input file location
 *
 *  return: if OK returns DADIP_OK
 *          if the format file is not supported, returns DADIP_UNSUPPORTFORMAT
 */
dadip_errinfo DaDip_Check_Image_Type(DADIP_2DPTRIMAGE inputimg, dadip_char* input);

/*
 * Function: DaDip_Get_Bytes_From_Depth
 * --------------------
 * API to calculate the number of bytes per pixel
 *
 *  depth(I): bits per pixel
 *  
 *  return: 
 *         Depth    Bytes
 *          1       0.125
 *          4       0.5
 *          8       1.0
 *          16      2.0
 *          24      3.0
 *          32      4.0
 */
dadip_float DaDip_Get_Bytes_From_Depth(dadip_short depth);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_IMAGEIO_H */
