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
 * This file defines some methods to implement some common functions*
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-31-2019                                               *
 *        Initial version includes methods for Fill boundary, Sort  *
 *        elements                                                  *
 *******************************************************************/

#ifndef DADIP_UTILITY_H
#define DADIP_UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_ImageIO.h"

/*
 * Function: DaDip_Fill_Boundary
 * --------------------
 * API to add the pixel data for the boundary of image. It copies the points near the boundary out to the boundary
 *
 *  inputimg(I): input image
 *
 *  length(I): boundary length
 */
dadip_void DaDip_Fill_Boundary(DADIP_PTRIMAGE inputimg, dadip_int length);

/*
 * Function: DaDip_Sort_Elements
 * --------------------
 * API to performs a simple bubble sort on the list of elements
 *
 *  elements(I/O): the list of elements to be sorted
 *
 *  count(I): the number of elements
 */
dadip_void DaDip_Sort_Elements(dadip_short* elements, dadip_int count);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_UTILITY_H */
