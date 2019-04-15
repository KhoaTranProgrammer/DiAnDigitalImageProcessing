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
 * This file defines some methods to implement the Warping Technique*
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-03-2019                                               *
 *        Initial version includes methods for Warp and Object Warp *
 *******************************************************************/

#ifndef DADIP_WARPING_H
#define DADIP_WARPING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

/*
 * Function: DaDip_Warp
 * --------------------
 * API to warps a rowsxcols section of an image by using control points(x,y)
 *
 *  inputimg(I): input image
 *
 *  xcontrol(I): the control points inside section in x direction
 *
 *  ycontrol(I): the control points inside section in y direction
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Warp(DADIP_PTRIMAGE inputimg, dadip_int xcontrol, dadip_int ycontrol);

/*
 * Function: DaDip_Object_Warp
 * --------------------
 * API to warps a rowsxcols section of an image by using four corners of a four side figure
 *
 *  inputimg(I): input image
 *
 *  x1(I): The point coordinates are for the four corners of a four side figure
 *
 *  y1(I): The point coordinates are for the four corners of a four side figure
 *
 *  x2(I): The point coordinates are for the four corners of a four side figure
 *
 *  y2(I): The point coordinates are for the four corners of a four side figure
 *
 *  x3(I): The point coordinates are for the four corners of a four side figure
 *
 *  y3(I): The point coordinates are for the four corners of a four side figure
 *
 *  x4(I): The point coordinates are for the four corners of a four side figure
 *
 *  y4(I): The point coordinates are for the four corners of a four side figure
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Object_Warp(DADIP_PTRIMAGE inputimg,
                                dadip_int x1, dadip_int y1, dadip_int x2, dadip_int y2,
                                dadip_int x3, dadip_int y3, dadip_int x4, dadip_int y4);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_WARPING_H */
