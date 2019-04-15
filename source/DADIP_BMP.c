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
 * This file implements method for BMP file format processing       *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Is_Bmp                                             *
 *         DaDip_Write_Bmp                                          *
 *        And some internal functions:                              *
 *         Flip_Vertical                                            *
 *         Read_Bitmap_Info_Header                                  *
 *         Read_Color_Table                                         *
 *         Read_Pixel_Array_8bits                                   *
 *         Read_Pixel_Array_24bits                                  *
 *         Parse_Bmp                                                *
 *         Destroy_Bmp                                              *
 *         Write_BmpFileheader                                      *
 *         Write_Bitmapinfoheader                                   *
 *         Write_Pixel_Array_8bits                                  *
 *         Write_Pixel_Array_24bits                                 *
 *******************************************************************/

#include "DADIP_BMP.h"

/* Calculate the number of PAD */
#define GETPAD(width)  ((width % 4) == 0) ? 0 : (4 - (width % 4))

/* Internal function to flip image in vertical */
dadip_errinfo Flip_Vertical(DADIP_PTRIMAGE inputimg)
{
    dadip_int i, j, k, rd2;
    DADIP_ARRAY outimage;
    dadip_errinfo err = DADIP_OK;
    dadip_int bytesperpixel;

    /* Create the blank pixel array */
    outimage = DaDip_Allocate_Pixel_Array(WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg));
    CHECK_MEM_UPDATE_ERROR(err, outimage)

    /* Calculate numer of bytes per pixel */
    bytesperpixel = DaDip_Get_Bytes_From_Depth(DEPTH(inputimg));

    /* Perform top half vertical */
    rd2 = HEIGHT(inputimg) / 2;
    for (i = 0; i < rd2; i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATARRAY(outimage, HEIGHT(inputimg) - 1 - i, j * bytesperpixel + k, WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg)) = PIXELATIMAGE(inputimg, i, j * bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Perform bottom half vertical */
    for (i = rd2; i < HEIGHT(inputimg); i++)
    {
        for (j = 0; j < WIDTH(inputimg); j++)
        {
            k = 0;
            do
            {
                PIXELATARRAY(outimage, HEIGHT(inputimg) - 1 - i, j * bytesperpixel + k, WIDTH(inputimg), HEIGHT(inputimg), DEPTH(inputimg)) = PIXELATIMAGE(inputimg, i, j * bytesperpixel + k);
                k++;
            } while (k < bytesperpixel);
        }
    }

    /* Free the old pixel array and assign to new vertically pixel array */
    DaDip_Free_Pixel_Array(inputimg->pixelarray);
    inputimg->pixelarray = outimage;

    return DADIP_OK;
ERR_BEG
    return err;
ERR_END
}

/* Internal function to read bitmap info header */
dadip_errinfo Read_Bitmap_Info_Header(DADIP_PTRIMAGE img)
{
    DADIP_PTRIMAGE_BMP bmpimg;
    DADIP_PTRBITMAPINFOHEADER bitmapheader;
    dadip_char*  buffer;
    dadip_errinfo err = DADIP_OK;

    bmpimg = (DADIP_PTRIMAGE_BMP)img;
    ALLOC_MEM_UPDATE_ERROR(err, bitmapheader, DADIP_BITMAPINFOHEADER, sizeof(DADIP_BITMAPINFOHEADER))

    /* the size of this header (40 bytes) */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->size = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* the bitmap width in pixels (signed integer) */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->width = DaDip_Extract_Long_From_Buffer(buffer, 1, 0);

    /* the bitmap height in pixels (signed integer) */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->height = DaDip_Extract_Long_From_Buffer(buffer, 1, 0);

    /* the number of color planes (must be 1) */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 2))
    bitmapheader->planes = DaDip_Extract_Ushort_From_Buffer(buffer, 1, 0);

    /* the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32. */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 2))
    bitmapheader->bitsperpixel = DaDip_Extract_Ushort_From_Buffer(buffer, 1, 0);

    /* the compression method being used. See the next table for a list of possible values */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->compression = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps. */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->sizeofbitmap = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* the horizontal resolution of the image. (pixel per metre, signed integer) */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->horizontalresolution = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* the vertical resolution of the image. (pixel per metre, signed integer) */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->verticalresolution = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* the number of colors in the color palette, or 0 to default to 2n */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->colorpalette = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* the number of important colors used, or 0 when every color is important; generally ignored */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bitmapheader->colorsused = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* Assign bitmap information header to the BMP instance */
    bmpimg->dibheader.bitmapheader = (DADIP_PTRBITMAPINFOHEADER)bitmapheader;

    /* Assign Global elements of image */
    bmpimg->width = bitmapheader->width;
    bmpimg->height = bitmapheader->height;

    return DADIP_OK;
ERR_BEG
    FREE_MEM(bitmapheader)
    return err;
ERR_END
}

/* Internal function to read color table for 8 bits image */
dadip_errinfo Read_Color_Table(DADIP_PTRIMAGE inputimg)
{
    DADIP_PTRIMAGE_BMP bmpimg;
    DADIP_PTRBITMAPINFOHEADER bitmapheader;
    dadip_char*  buffer;
    dadip_int i;
    dadip_errinfo err = DADIP_OK;

    bmpimg = (DADIP_PTRIMAGE_BMP)inputimg;
    bitmapheader = (DADIP_PTRBITMAPINFOHEADER)bmpimg->dibheader.bitmapheader;

    /* Confirm the number of colors */
    if (bitmapheader->colorsused == 0)
    {
        bmpimg->colors = GRAY_LEVELS + 1;
    }
    else
    {
        bmpimg->colors = bitmapheader->colorsused;
    }

    /* Allocate memory for color table */
    ALLOC_MEM_UPDATE_ERROR(err, bmpimg->colortable, DADIP_RGB, sizeof(DADIP_RGB) * bmpimg->colors)

    for (i = 0; i < bmpimg->colors; i++)
    {
        /* Read Red/Green/Blue and 1 reserved byte */
        CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))

        /* blue */
        bmpimg->colortable[i].blue = buffer[0];

        /* green */
        bmpimg->colortable[i].green = buffer[1];

        /* red */
        bmpimg->colortable[i].red = buffer[2];
    }

    return DADIP_OK;
ERR_BEG
    FREE_MEM(bmpimg->colortable)
    return err;
ERR_END
}

/* Internal function to read pixel data for 8 bits image */
dadip_errinfo Read_Pixel_Array_8bits(DADIP_PTRIMAGE img)
{
    DADIP_PTRIMAGE_BMP bmpimg;
    dadip_int width, height, negative, pad, i, j, place;
    dadip_char* buffer;
    dadip_errinfo err = DADIP_OK;

    bmpimg = (DADIP_PTRIMAGE_BMP)img;
    negative = 0;

    width = WIDTH(bmpimg);
    height = HEIGHT(bmpimg);

    if (height < 0)
    {
        height *= -1;
        negative = 1;
    }

    /* Count PAD */
    pad = GETPAD(width);

    /* Assign Global element depth */
    bmpimg->depth = 24;

    /* Create the blank pixel array */
    bmpimg->pixelarray = DaDip_Allocate_Pixel_Array(WIDTH(bmpimg), HEIGHT(bmpimg), DEPTH(bmpimg));
    CHECK_MEM_UPDATE_ERROR(err, bmpimg->pixelarray)

    /* Allocate memory(in total row) for the place of color's pixel in color table */
    ALLOC_MEM_UPDATE_ERROR(err, bmpimg->places, dadip_int*, height * sizeof(dadip_int*))

    /* Perform read data */
    for (i = 0; i < height; i++)
    {
        /* Allocate memory(in total column of each row) for the place of color's pixel in color table */
        ALLOC_MEM_UPDATE_ERROR(err, bmpimg->places[i], dadip_uchar, width * sizeof(dadip_int))

        for (j = 0; j < width; j++)
        {
            CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 1))
            place = (buffer[0] & 0xff);
            /* Red */
            PIXELATIMAGE(bmpimg, i, j * 3 + DADIP_R) = bmpimg->colortable[place].red;
            /* Green */
            PIXELATIMAGE(bmpimg, i, j * 3 + DADIP_G) = bmpimg->colortable[place].green;
            /* Blue */
            PIXELATIMAGE(bmpimg, i, j * 3 + DADIP_B) = bmpimg->colortable[place].blue;

            bmpimg->places[i][j] = place;
        }
        if (pad != 0)
        {
            bmpimg->filereader->seekFromCurrent(bmpimg->filereader, pad);
        }
    }

    /* Perform Flip Vertical */
    if (negative == 0)
    {
        CHECK_UPDATE_ERROR(err, Flip_Vertical(bmpimg))
    }

    return DADIP_OK;
ERR_BEG
    /* Free pixel array */
    DaDip_Free_Pixel_Array(bmpimg->pixelarray);
    for (i = 0; i < height; i++)
    {
        FREE_MEM(bmpimg->places[i])
    }
    FREE_MEM(bmpimg->places)
    return err;
ERR_END
}

/* Internal function to read pixel data for 24 bits image */
dadip_errinfo Read_Pixel_Array_24bits(DADIP_PTRIMAGE inputimg)
{
    DADIP_PTRIMAGE_BMP bmpimg;
    dadip_int width, height, negative, pad, i, j, place;
    dadip_char* buffer;
    dadip_errinfo err = DADIP_OK;

    bmpimg = (DADIP_PTRIMAGE_BMP)inputimg;
    negative = 0;

    width = WIDTH(bmpimg);
    height = HEIGHT(bmpimg);

    if (height < 0)
    {
        height *= -1;
        negative = 1;
    }

    /* Count PAD */
    pad = GETPAD(width);

    /* Assign Global element depth */
    bmpimg->depth = 24;

    /* Create the blank pixel array */
    bmpimg->pixelarray = DaDip_Allocate_Pixel_Array(WIDTH(bmpimg), HEIGHT(bmpimg), DEPTH(bmpimg));
    CHECK_MEM_UPDATE_ERROR(err, bmpimg->pixelarray)

    /* Perform read data */
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            /* Blue */
            CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 1))
            PIXELATIMAGE(bmpimg, i, j * 3 + DADIP_B) = buffer[0];

            /* Green */
            CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 1))
            PIXELATIMAGE(bmpimg, i, j * 3 + DADIP_G) = buffer[0];

            /* Red */
            CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 1))
            PIXELATIMAGE(bmpimg, i, j * 3 + DADIP_R) = buffer[0];
        }
        if (pad != 0)
        {
            bmpimg->filereader->seekFromCurrent(bmpimg->filereader, pad);
        }
    }

    /* Perform Flip Vertical */
    if (negative == 0)
    {
        CHECK_UPDATE_ERROR(err, Flip_Vertical(bmpimg));
    }

    return DADIP_OK;
ERR_BEG
    /* Free pixel array */
    DaDip_Free_Pixel_Array(bmpimg->pixelarray);
    return err;
ERR_END
}

/* Internal function to fully parse BMP file */
static dadip_errinfo Parse_Bmp(DADIP_PTRIMAGE img)
{
    DADIP_PTRIMAGE_BMP bmpimg;
    DADIP_PTRBITMAPINFOHEADER bitmapheader;
    dadip_errinfo err = DADIP_OK;
     
    /* Assign input DIP_IMAGE to the instance of DIP_IMAGE_BMP */
    bmpimg = (DADIP_PTRIMAGE_BMP)img;

    /* In case of Windows BITMAPINFOHEADER */
    if (bmpimg->fileheader.filetype == 0x4d42)
    {
        /* Read Bitmap Info Header */
        CHECK_UPDATE_ERROR(err, Read_Bitmap_Info_Header(img))
        bitmapheader = (DADIP_PTRBITMAPINFOHEADER)bmpimg->dibheader.bitmapheader;

        if(bitmapheader->bitsperpixel == 8)
        {
            /* Read Color Table */
            CHECK_UPDATE_ERROR(err, Read_Color_Table(img))

            /* Read Pixel Array */
            CHECK_UPDATE_ERROR(err, Read_Pixel_Array_8bits(img))
        }
        else if (bitmapheader->bitsperpixel == 24)
        {
            /* Read Pixel Array */
            CHECK_UPDATE_ERROR(err, Read_Pixel_Array_24bits(img))
        }
    }
    else /* In case of UnSupport Format */
    {
        return DADIP_UNSUPPORTFORMAT;
    }

    return DADIP_OK;
ERR_BEG
    return err;
ERR_END
}

/* Internal function to destroy data structure of BMP */
static dadip_void Destroy_Bmp(DADIP_PTRIMAGE img)
{
    DADIP_PTRIMAGE_BMP bmpimg;
    DADIP_PTRBITMAPINFOHEADER bitmapheader;
    dadip_int width, height, i, j, negative;

    CHECK_MEM(img)

    bmpimg = (DADIP_PTRIMAGE_BMP)img;

    width = bmpimg->width;
    height = bmpimg->height;

    if (height < 0)
    {
        height *= -1;
        negative = 1;
    }

    /* Free pixel array */
    DaDip_Free_Pixel_Array(bmpimg->pixelarray);

    /* In case of Windows BITMAPINFOHEADER */
    if (bmpimg->fileheader.filetype == 0x4d42)
    {
        bitmapheader = (DADIP_PTRBITMAPINFOHEADER)bmpimg->dibheader.bitmapheader;
        if (bitmapheader->bitsperpixel == 8)
        {
            FREE_MEM(bmpimg->colortable)
            for (i = 0; i < height; i++)
            {
                FREE_MEM(bmpimg->places[i])
            }
        }
    }

    /* Free bitmap header */
    FREE_MEM(bmpimg->dibheader.bitmapheader)

    /* Free file reader structure */
    if(bmpimg->filereader != NULL)
        bmpimg->filereader->destroy(bmpimg->filereader);

    /* Free bmp image structure */
    FREE_MEM(bmpimg)
    bmpimg = NULL;

ERR_BEG
    return;
ERR_END
}

/* The implementation of API to check BMP type */
dadip_errinfo DaDip_Is_Bmp(DADIP_2DPTRIMAGE img, dadip_char* filename)
{
    DADIP_PTRIMAGE_BMP bmpimg;
    dadip_char*  buffer;
    dadip_errinfo err;

    err = DADIP_MEMERROR;

    /* Create the instance to store BMP data structure */
    ALLOC_MEM(bmpimg, DADIP_IMAGE_BMP, sizeof(DADIP_IMAGE_BMP))

    /* Create the instance of file reader */
    CHECK_UPDATE_ERROR(err, DaDip_Create_File_Reader(&bmpimg->filereader, filename))

    /* The header field used to identify the BMP and DIB file is 0x42 0x4D in hexadecimal, same as BM in ASCII */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 2))
    bmpimg->fileheader.filetype = DaDip_Extract_Ushort_From_Buffer(buffer, 1, 0);

    /* The size of the BMP file in bytes */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bmpimg->fileheader.filesize = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* Reserved; actual value depends on the application that creates the image */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 2))
    bmpimg->fileheader.reserved1 = DaDip_Extract_Short_From_Buffer(buffer, 1, 0);

    /* Reserved; actual value depends on the application that creates the image */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 2))
    bmpimg->fileheader.reserved2 = DaDip_Extract_Short_From_Buffer(buffer, 1, 0);

    /* The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found. */
    CHECK_UPDATE_ERROR(err, bmpimg->filereader->readDataFromFile(bmpimg->filereader, (dadip_uchar**)(&buffer), 4))
    bmpimg->fileheader.bitmapoffset = DaDip_Extract_Ulong_From_Buffer(buffer, 1, 0);

    /* Check the filetype is BMP or not */
    if (bmpimg->fileheader.filetype != 0x4d42)
    {
        err = DADIP_UNSUPPORTFORMAT;
        goto if_err;
    }

    /* Assign Parse & Destroy methods for BMP instance */
    bmpimg->parseImage = Parse_Bmp;
    bmpimg->destroy = Destroy_Bmp;

    /* Assign BMP instance for DIP_IMAGE output argument */
    *img = (DADIP_PTRIMAGE)bmpimg;

    return DADIP_OK;
ERR_BEG
    if(bmpimg != NULL)
    {
        if(bmpimg->filereader != NULL) bmpimg->filereader->destroy(bmpimg->filereader);
        FREE_MEM(bmpimg)
        *img = NULL;
    }
    return err;
ERR_END
}

/* Write the 14-byte of bmp file header */
dadip_void Write_BmpFileheader(DADIP_PTRIMAGE img)
{
    dadip_char buffer[3000];
    dadip_int filesize, bitmapoffset;
    dadip_errinfo err;

    /* Write file type */
    DaDip_Insert_Ushort_Into_Buffer(buffer, 0, 0x4D42);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 2));

    /* Calculate and write file size */
    filesize = 14; /* Size of Bmp file header 14-bytes */
    filesize += 40; /* Size of bitmap info header 40-bytes */
    bitmapoffset = filesize;
    if (DEPTH(img) == 8)
    {
        filesize += 256 * 4; /* Size of color table */
        filesize += HEIGHT(img) * (WIDTH(img) + GETPAD(WIDTH(img)));
        bitmapoffset += 256 * 4;
    }
    else if (DEPTH(img) == 24)
    {
        filesize += HEIGHT(img) * (WIDTH(img) + GETPAD(WIDTH(img))) * 3;
    }
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, filesize);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    /* Write Reserved 1 */
    DaDip_Insert_Short_Into_Buffer(buffer, 0, 0x00);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 2));

    /* Write Reserved 2 */
    DaDip_Insert_Short_Into_Buffer(buffer, 0, 0x00);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 2));

    /* Write bitmap offset */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, bitmapoffset);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));
    
    return DADIP_OK;
ERR_BEG
    return err;
ERR_END
}

/* Write the 40-byte of bitmap info header */
dadip_void Write_Bitmapinfoheader(DADIP_PTRIMAGE img)
{
    dadip_char buffer[3000];
    dadip_int sizeofbitmap, colorpalette, colorsused;
    dadip_errinfo err;

    /* Write the size of this header */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, 40);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    /* Write width in pixels */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, WIDTH(img));
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    /* Write height in pixels */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, HEIGHT(img));
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    /* Write color planes (must be 1) */
    DaDip_Insert_Ushort_Into_Buffer(buffer, 0, 1);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 2));

    /* Write Bits per pixel */
    DaDip_Insert_Ushort_Into_Buffer(buffer, 0, DEPTH(img));
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 2));

    /* Write Compression method (will be zero) */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, 0);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    switch (DEPTH(img))
    {
    case 8: /* 8 bits per pixel */
        sizeofbitmap = HEIGHT(img) * (WIDTH(img) + GETPAD(WIDTH(img)));
        colorpalette = 256;
        colorsused = 256;
        break;
    case 24: /* 24 bits per pixel */
        sizeofbitmap = 0;
        colorpalette = 0;
        colorsused = 0;
        break;
    default: /* default is 24 bits per pixel */
        sizeofbitmap = 0;
        colorpalette = 0;
        colorsused = 0;
    }

    /* Write image size */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, sizeofbitmap);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    /* Write horizontal resolution */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, 300);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    /* Write vertical resolution */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, 300);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    /* Write number of color palette */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, colorpalette);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    /* Write number of colors used */
    DaDip_Insert_Ulong_Into_Buffer(buffer, 0, colorsused);
    CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));

    return DADIP_OK;
ERR_BEG
    return err;
ERR_END
}

/* Write Pixel Array 8bits */
dadip_errinfo Write_Pixel_Array_8bits(DADIP_PTRIMAGE img)
{
    dadip_int i, j, pad;
    dadip_char buffer[3000];
    union  short_char_union scu;
    dadip_errinfo err;

    /* Count PAD */
    pad = GETPAD(WIDTH(img));

    /* Write the color table */
    for (i = 0; i < GRAY_LEVELS + 1; i++)
    {
        buffer[0] = i;
        buffer[1] = i;
        buffer[2] = i;
        buffer[3] = 0x00;
        CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, 4));
    }

    /* Write pixel array */
    for (i = 0; i < HEIGHT(img); i++)
    {
        for (j = 0; j < WIDTH(img); j++)
        {
            if (HEIGHT(img) > 0)
            {
                scu.s_num = PIXELATIMAGE(img, HEIGHT(img) - 1 - i, j);
            }
            else
            {
                scu.s_num = PIXELATIMAGE(img, i, j);
            }
            buffer[j] = scu.s_alpha[0];
        }

        CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, WIDTH(img)));

        if (pad != 0)
        {
            for (j = 0; j < pad; j++)
                buffer[j] = 0x00;
            CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, pad));
        }
    }

    return DADIP_OK;
ERR_BEG
    return err;
ERR_END
}

/* Write Pixel Array 24bits */
dadip_errinfo Write_Pixel_Array_24bits(DADIP_PTRIMAGE img)
{
    dadip_int i, j, pad;
    dadip_char buffer[3000];
    union  short_char_union scu;
    dadip_errinfo err;

    /* Count PAD */
    pad = GETPAD(WIDTH(img));

    /* Write pixel array */
    for (i = 0; i < HEIGHT(img); i++)
    {
        for (j = 0; j < WIDTH(img); j++)
        {
            if (HEIGHT(img) > 0)
            {
                /* Blue */
                scu.s_num = PIXELATIMAGE(img, HEIGHT(img) - 1 - i, j * 3 + DADIP_B);
                buffer[j * 3] = scu.s_alpha[0];

                /* Green */
                scu.s_num = PIXELATIMAGE(img, HEIGHT(img) - 1 - i, j * 3 + DADIP_G);
                buffer[j * 3 + 1] = scu.s_alpha[0];

                /* Red */
                scu.s_num = PIXELATIMAGE(img, HEIGHT(img) - 1 - i, j * 3 + DADIP_R);
                buffer[j * 3 + 2] = scu.s_alpha[0];
            }
            else
            {
                /* Blue */
                scu.s_num = PIXELATIMAGE(img, i, j * 3 + DADIP_B);
                buffer[j * 3] = scu.s_alpha[0];

                /* Green */
                scu.s_num = PIXELATIMAGE(img, i, j * 3 + DADIP_G);
                buffer[j * 3 + 1] = scu.s_alpha[0];

                /* Red */
                scu.s_num = PIXELATIMAGE(img, i, j * 3 + DADIP_R);
                buffer[j * 3 + 2] = scu.s_alpha[0];
            }
        }
        CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, WIDTH(img) * 3));

        if (pad != 0)
        {
            for (j = 0; j < pad; j++)
                buffer[j] = 0x00;
            CHECK_UPDATE_ERROR(err, img->filewriter->writeDataToFile(img->filewriter, buffer, pad));
        }
    }

    return DADIP_OK;
ERR_BEG
    return err;
ERR_END
}

/* Implementation of API to write Base image to BMP image */
dadip_errinfo DaDip_Write_Bmp(DADIP_PTRIMAGE img, dadip_char* filename)
{
    dadip_errinfo err;
    
    /* Create the instance of file writer */
    CHECK_UPDATE_ERROR(err, DaDip_Create_File_Writer(&img->filewriter, filename))

    /* Write bmp file header */
    Write_BmpFileheader(img);

    /* Write bitmap info header */
    Write_Bitmapinfoheader(img);

    /* Write pixel array */
    switch (DEPTH(img))
    {
    case 8:
        /* Write pixel array for 8 bits image */
        CHECK_UPDATE_ERROR(err, Write_Pixel_Array_8bits(img));
        break;
    case 24:
        /* Write pixel array for 24 bits image */
        CHECK_UPDATE_ERROR(err, Write_Pixel_Array_24bits(img));
        break;
    default:
        err = DADIP_UNSUPPORTFORMAT;
        goto if_err;
    }

    /* Free file writer */
    img->filewriter->destroy(img->filewriter);

    return DADIP_OK;
ERR_BEG
    return err;
ERR_END
}
