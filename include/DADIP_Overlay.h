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
 * This file defines some methods to implement the functions that   *
 * overlay one image on top of another image                        *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-30-2019                                               *
 *        Initial version includes methods for overlay such as: non *
 *        zero, zero, greater, less, average                        *
 *******************************************************************/

#ifndef DADIP_OVERLAY_H
#define DADIP_OVERLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

/*
 * Function: DaDip_Overlay_NonZero
 * --------------------
 * API to overlays 2 input images by Non Zero mode. It writes any non-zero pixel from second input image on top of first input image
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
DADIP_PTRIMAGE DaDip_Overlay_NonZero(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth);

/*
 * Function: DaDip_Overlay_Zero
 * --------------------
 * API to overlays 2 input images by Zero mode. It writes any zero pixel from second input image on top of first input image
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
DADIP_PTRIMAGE DaDip_Overlay_Zero(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth);

/*
 * Function: DaDip_Overlay_Greater
 * --------------------
 * API to overlays 2 input images by Greater mode. It writes inputimg2 on top of inputimg1 if the value of second input image is greater than first input image
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
DADIP_PTRIMAGE DaDip_Overlay_Greater(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth);

/*
 * Function: DaDip_Overlay_Less
 * --------------------
 * API to overlays 2 input images by Less mode. It writes inputimg2 on top of inputimg1 if the value of second input image is less than first input image
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
DADIP_PTRIMAGE DaDip_Overlay_Less(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth);

/*
 * Function: DaDip_Overlay_Average
 * --------------------
 * API to overlays 2 input images by Average mode. It writes the average of first input image and second input image to the output image
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
DADIP_PTRIMAGE DaDip_Overlay_Average(DADIP_PTRIMAGE inputimg1, DADIP_PTRIMAGE inputimg2,
                         dadip_int startrowofimg1, dadip_int startrowofimg2, dadip_int newheight,
                         dadip_int startcolofimg1, dadip_int startcolofimg2, dadip_int newwidth);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_OVERLAY_H */
