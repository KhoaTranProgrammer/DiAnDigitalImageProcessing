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
 * This file defines some methods to implement mathematic operation *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-30-2019                                               *
 *        Initial version includes methods for overlay such as: AND,*
 *        OR, XOR, NOT, NAND, NOR, ADD, SUBTRACT                    *
 *******************************************************************/

#ifndef DADIP_MATH_H
#define DADIP_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

/*
 * Function: DaDip_Math_Add
 * --------------------
 * API to implement the basic algebra function Add
 *
 *  inputimg(I): input image
 *
 *  value(I): value to be added
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Math_Add(DADIP_PTRIMAGE inputimg, dadip_ushort value);

/*
 * Function: DaDip_Math_Subtract
 * --------------------
 * API to implement the basic algebra function Subtract
 *
 *  inputimg(I): input image
 *
 *  value(I): value to be added
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Math_Subtract(DADIP_PTRIMAGE inputimg, dadip_ushort value);

/*
 * Function: DaDip_Math_And
 * --------------------
 * API to implement the basic algebra function And
 *
 *  inputimg(I): input image
 *
 *  value(I): value to be added
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Math_And(DADIP_PTRIMAGE inputimg, dadip_ushort value);

/*
 * Function: DaDip_Math_Or
 * --------------------
 * API to implement the basic algebra function Or
 *
 *  inputimg(I): input image
 *
 *  value(I): value to be added
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Math_Or(DADIP_PTRIMAGE inputimg, dadip_ushort value);

/*
 * Function: DaDip_Math_Xor
 * --------------------
 * API to implement the basic algebra function Xor
 *
 *  inputimg(I): input image
 *
 *  value(I): value to be added
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Math_Xor(DADIP_PTRIMAGE inputimg, dadip_ushort value);

/*
 * Function: DaDip_Math_Not
 * --------------------
 * API to implement the basic algebra function Not
 *
 *  inputimg(I): input image
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Math_Not(DADIP_PTRIMAGE inputimg);

/*
 * Function: DaDip_Math_Nand
 * --------------------
 * API to implement the basic algebra function Nand
 *
 *  inputimg(I): input image
 *
 *  value(I): value to be added
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Math_Nand(DADIP_PTRIMAGE inputimg, dadip_ushort value);

/*
 * Function: DaDip_Math_Nor
 * --------------------
 * API to implement the basic algebra function Nor
 *
 *  inputimg(I): input image
 *
 *  value(I): value to be added
 *
 *  return: output image
 */
DADIP_PTRIMAGE DaDip_Math_Nor(DADIP_PTRIMAGE inputimg, dadip_ushort value);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_MATH_H */
