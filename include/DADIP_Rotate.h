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
 * This file defines method for image rotation                      *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version with API to rotate 90/180/270/any origin, *
 *        flip vertical, flip horizontal                            *
 *******************************************************************/

#ifndef DADIP_ROTATE_H
#define DADIP_ROTATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

/*
 * Function: DaDip_Flip_Vertical
 * --------------------
 * API to perform Flip image as vertical
 * Input  -> Output
 * 1 2 3     7 8 9
 * 4 5 6     4 5 6
 * 7 8 9     1 2 3
 *
 *  inputimg(I): input image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Flip_Vertical(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Flip_Horizontal
 * --------------------
 * API to perform Flip image as horizontal
 * Input  -> Output
 * 1 2 3     3 2 1
 * 4 5 6     6 5 4
 * 7 8 9     9 8 7
 *
 *  inputimg(I): input image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Flip_Horizontal(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Rotation_90_Degree
 * --------------------
 * API to perform 90 degree rotation
 * Input  -> Output
 * 1 2 3     7 4 1
 * 4 5 6     8 5 2
 * 7 8 9     9 6 3
 *
 *  inputimg(I): input image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Rotation_90_Degree(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Rotation_180_Degree
 * --------------------
 * API to perform 180 degree rotation
 * Input  -> Output
 * 1 2 3     9 8 7
 * 4 5 6     6 5 4
 * 7 8 9     3 2 1
 *
 *  inputimg(I): input image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Rotation_180_Degree(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Rotation_270_Degree
 * --------------------
 * API to perform 270 degree rotation
 * Input  -> Output
 * 1 2 3     3 6 9
 * 4 5 6     2 5 8
 * 7 8 9     1 4 7
 *
 *  inputimg(I): input image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Rotation_270_Degree(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Rotation
 * --------------------
 * API to perform rotation in any point of origin
 *
 *  inputimg(I): input image
 *
 *  m(I): x origin  
 *
 *  n(I): y origin
 *
 *  angle(I): degree of rotation
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Rotation(DADIP_PTRIMAGE inputimg, dadip_int m, dadip_int n, dadip_float angle);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_ROTATE_H */
