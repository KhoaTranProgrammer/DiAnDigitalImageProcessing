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
 * This file defines some general information that are used by all  *
 * of APIs such as Basic data types, Math operation, Error codes,   *
 * and some macros for MEM/ERROR processing                         *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version includes Basic data types, Math operation,*
 *        Error codes, some macros for MEM/ERROR processing         *
 *******************************************************************/

#ifndef DADIP_TYPE_H
#define DADIP_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "malloc.h"
#include "math.h"

/* Basic data types */
typedef signed long long dadip_int64;
typedef unsigned long long dadip_uint64;
typedef long dadip_long;
typedef unsigned long dadip_ulong;
typedef signed int dadip_int;
typedef unsigned int dadip_uint;
typedef signed char dadip_char;
typedef unsigned char dadip_uchar;
typedef signed short dadip_short;
typedef unsigned short dadip_ushort;
typedef void dadip_void;
typedef int dadip_errinfo;
typedef float dadip_float;
typedef double dadip_double;

/* Math operation */
#define DADIP_COS(radian_angle) cos(radian_angle)
#define DADIP_SIN(radian_angle) sin(radian_angle)

/* Error codes */
enum
{
    DADIP_OK = 0,           /* OK */
    DADIP_NOK,              /* Not OK */
    DADIP_MEMERROR,         /* Memory error */
    DADIP_FILEEOF,          /* End of file */
    DADIP_UNSUPPORTFORMAT   /* None supported format */
};

#define ALLOC_MEM(p, type, size)    \
    p = (type*)malloc(size);        \
    CHECK_MEM(p)                    \

#define ALLOC_MEM_UPDATE_ERROR(err, p, type, size)  \
    p = (type*)malloc(size);                        \
    CHECK_MEM_UPDATE_ERROR(err, p)                  \

#define FREE_MEM(p)	\
	if(p != NULL)	\
		free(p);	\
    p = NULL;       \

#define CHECK_MEM(p)    \
	if(p == NULL){ 	    \
		goto if_err;	\
    }                   \

#define CHECK_MEM_UPDATE_ERROR(err, p)  \
	if(p == NULL){ 		                \
        err = DADIP_MEMERROR;           \
		goto if_err;	                \
    }                                   \

#define CHECK_ERROR(e)  \
	if(e != DADIP_OK) { \
		goto if_err;	\
    }                   \

#define CHECK_UPDATE_ERROR(err, e)  \
	if(e != DADIP_OK) {             \
        err = e;                    \
		goto if_err;	            \
    }                               \

#define ERR_BEG \
if_err:         \

#define ERR_END \

#ifdef __cplusplus
}
#endif
#endif /* DADIP_TYPE_H */
