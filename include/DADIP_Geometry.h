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
 * This file defines method for image Geometrical Operations        *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-26-2019                                               *
 *        Initial version with API to Invert, Stretch, Crop, Paste  *
 *        Geometry(Displacement, Stretching, Rotation)              *
 *******************************************************************/

#ifndef DADIP_GEOMETRY_H
#define DADIP_GEOMETRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

/*
 * Function: DaDip_Invert
 * --------------------
 * API to invert the pixels in an image. Output image appear as negative
 *
 *  inputimg(I): input image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Invert(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Geometry
 * --------------------
 * API to perform three Basic Geometric Operations: Displacement, Stretching, and Rotation
 *
 *  inputimg(I): input image
 *
 *  angle(I): degree of rotation
 *
 *  xstretch(I): enlarges or shrinks the image in the horizontal direction
 *
 *  ystretch(I): enlarges or shrinks the image in the vertical direction
 *
 *  xdisplace(I): perform displacement in the horizontal direction
 *
 *  ydisplace(I): perform displacement in the vertical direction
 *
 *  xcross(I): distort image in the horizontal direction
 *
 *  ycross(I): distort image in the vertical direction
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Geometry(DADIP_PTRIMAGE inputimg, dadip_float angle,
                               dadip_float xstretch, dadip_float ystretch,
                               dadip_short xdisplace, dadip_short ydisplace,
                               dadip_float xcross, dadip_float ycross);

/*
 * Function: DaDip_Stretch
 * --------------------
 * API to perform the processing to enlarge and shrink an entire image
 *
 *  inputimg(I): input image
 *
 *  xstretch(I): enlarges or shrinks the image in the horizontal direction
 *
 *  ystretch(I): enlarges or shrinks the image in the vertical direction
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Stretch(DADIP_PTRIMAGE inputimg, dadip_float xstretch, dadip_float ystretch);

/*
 * Function: DaDip_Crop
 * --------------------
 * API to select the specific area of image
 *
 *  inputimg(I): input image
 *
 *  startrow(I): beginning of row in the input image
 *
 *  startcol(I): beginning of column in the input image
 *
 *  newheight(I): new height of output image
 *
 *  newwidth(I): new width of output image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Crop(DADIP_PTRIMAGE inputimg, dadip_int startrow, dadip_int startcol, dadip_int newheight, dadip_int newwidth);

/*
 * Function: DaDip_Paste
 * --------------------
 * API to combine 2 input images inside 1 output image
 *
 *  inputimg1(I): first input image
 *
 *  inputimg2(I): second input image
 *
 *  startrowofimg1(I): beginning of row in the first input image
 *
 *  startrowofimg2(I): beginning of row in the second input image
 *
 *  newheight(I): new height of output image
 *
 *  startcolofimg1(I): beginning of column in the first input image
 *
 *  startcolofimg2(I): beginning of column in the second input image
 *
 *  newwidth(I): new width of output image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Paste(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                           dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                           dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_GEOMETRY_H */
