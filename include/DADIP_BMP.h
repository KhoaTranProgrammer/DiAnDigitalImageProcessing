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
 * This file defines some data structures and method for BMP file   *
 * format processing                                                *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version supports 8/24 bits per pixel, Windows and *
 *        OS/2 bitmap headers, read and write BMP file              *
 *******************************************************************/

#ifndef DADIP_BMP_H
#define DADIP_BMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

/* The structure to store bitmap file header */
typedef struct _dadip_bmpfileheader
{
    dadip_ushort  filetype;       /* The header field used to identify the BMP and DIB file is 0x42 0x4D in hexadecimal, same as BM in ASCII.The following entries are possible : */
                                  /* BM - Windows 3.1x, 95, NT, ... etc. */
                                  /* BA - OS / 2 struct bitmap array */
                                  /* CI - OS / 2 struct color icon */
                                  /* CP - OS / 2 const color pointer */
                                  /* IC - OS / 2 struct icon */
                                  /* PT - OS / 2 pointer */
    dadip_uint    filesize;       /* The size of the BMP file in bytes */
    dadip_short   reserved1;      /* Reserved; actual value depends on the application that creates the image */
    dadip_short   reserved2;      /* Reserved; actual value depends on the application that creates the image */
    dadip_uint    bitmapoffset;   /* The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found. */
} DADIP_BMPFILEHEADER;

/* The structure to store dib header */
typedef struct _dadip_dibheader
{
    dadip_void* bitmapheader; /* Windows and OS/2 bitmap headers */
} DADIP_DIBHEADER;

/* The structure to store bitmap info header */
typedef struct _dadip_bitmapinfoheader
{
    dadip_uint    size;                   /* the size of this header (40 bytes) */
    dadip_int     width;                  /* the bitmap width in pixels (signed integer) */
    dadip_int     height;                 /* the bitmap height in pixels (signed integer) */
    dadip_ushort  planes;                 /* the number of color planes (must be 1) */
    dadip_ushort  bitsperpixel;           /* the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32. */
    dadip_uint    compression;            /* the compression method being used. See the next table for a list of possible values */
    dadip_uint    sizeofbitmap;           /* the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps. */
    dadip_uint    horizontalresolution;   /* the horizontal resolution of the image. (pixel per metre, signed integer) */
    dadip_uint    verticalresolution;     /* the vertical resolution of the image. (pixel per metre, signed integer) */
    dadip_uint    colorpalette;           /* the number of colors in the color palette, or 0 to default to 2n */
    dadip_uint    colorsused;             /* the number of important colors used, or 0 when every color is important; generally ignored */
} DADIP_BITMAPINFOHEADER, *DADIP_PTRBITMAPINFOHEADER;

/* The structure to store BMP image */
typedef struct _dadip_image_bmp
{
    DADIP_BASEIMAGE                   /* Global elements of image */
    DADIP_BMPFILEHEADER   fileheader; /* Bitmap file header */
    DADIP_DIBHEADER   dibheader;      /* Bitmap information header */
    DADIP_RGB* colortable;            /* Color table */
    dadip_int colors;                 /* The length of color table */
    dadip_int** places;               /* Store the place of color's pixel in color table */
} DADIP_IMAGE_BMP, *DADIP_PTRIMAGE_BMP;

/*
 * Function: DaDip_Is_Bmp
 * --------------------
 * API to check BMP type
 *
 *  inputimg(I): input image
 *
 *  filename(I): input file location
 *
 *  returns: if OK returns DADIP_OK
 *           if can not allocate memory returns DADIP_MEMERROR
 *           if is not BMP file returns DADIP_UNSUPPORTFORMAT
 */
dadip_errinfo DaDip_Is_Bmp(DADIP_2DPTRIMAGE inputimg, dadip_char* filename);

/*
 * Function: DaDip_Write_Bmp
 * --------------------
 * API to write Base image to BMP image
 *
 *  inputimg(I): input image
 *
 *  filename(I): output file location
 *
 *  returns: if OK returns DADIP_OK
 *           if can not allocate memory returns DADIP_MEMERROR
 */
dadip_errinfo DaDip_Write_Bmp(DADIP_PTRIMAGE inputimg, dadip_char* filename);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_BMP_H */
