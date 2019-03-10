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
 * This file defines some data structures and method for reading    *
 * from file or writing to file                                     *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version includes dadip_fileReader/dadip_fileWriter*
 *        structure, DaDip_Create_File_Reader,                      *
 *        DaDip_Create_File_Writer                                  *
 *******************************************************************/

#ifndef DADIP_FILEIO_H
#define DADIP_FILEIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DADIP_Type.h"

/* File reader structure to manage the reading of file */
typedef struct _dadip_fileReader
{
    /* An object of type file */
    FILE* f;

    /* Total number of bytes that are read */
    dadip_uint bytesread;

    /* Method to destroy file reader instance */
    dadip_void (*destroy)(struct _dadip_fileReader* me);

    /*
     * Method to read amount of data from file
     * outData: stores output data
     * bytes: number of bytes to be read
     */
    dadip_errinfo (*readDataFromFile)(struct _dadip_fileReader* me, dadip_char **outData, dadip_int bytes);

    /*
     * Method to move to the new position
     * bytes: number of bytes to move from current
     */
    dadip_void (*seekFromCurrent)(struct _dadip_fileReader* me, dadip_int bytes);
} DADIP_FILEREADER, *DADIP_PTRFILEREADER, **DADIP_2DPTRFILEREADER;

/* File writer structure to manage the writing of file */
typedef struct _dadip_fileWriter
{
    /* An object of type file */
    FILE* f;

    /* Total number of bytes that are wrote */
    dadip_uint byteswrite;

    /* Method to destroy file writer instance */
    dadip_void (*destroy)(struct _dadip_fileWriter* me);

    /*
     * Method to write amount of data to file
     * inData: stores input data
     * bytes: number of bytes to be wrote
     */
    dadip_errinfo (*writeDataToFile)(struct _dadip_fileWriter* me, dadip_char *inData, dadip_int bytes);
} DADIP_FILEWRITER, *DADIP_PTRFILEWRITER, **DADIP_2DPTRFILEWRITER;

/*
 * Function: DaDip_Create_File_Reader
 * --------------------
 * Method to create the instance of file reader
 *
 *  filereader(I/O): instance of DADIP_FILEREADER
 *
 *  filename(I): input file location
 *
 *  returns: if OK returns DADIP_OK
 *           if can not allocate memory returns DADIP_MEMERROR
 */
dadip_errinfo DaDip_Create_File_Reader(DADIP_2DPTRFILEREADER fileReader, dadip_char* filename);

/*
 * Function: DaDip_Create_File_Writer
 * --------------------
 * Method to create the instance of file writer
 *
 *  filewriter(I/O): instance of DADIP_FILEWRITER
 *
 *  filename(I): output file location
 *
 *  returns: if OK returns DADIP_OK
 *           if can not allocate memory returns DADIP_MEMERROR
 */
dadip_errinfo DaDip_Create_File_Writer(DADIP_2DPTRFILEWRITER fileWriter, dadip_char* filename);

#ifdef __cplusplus
}
#endif
#endif /* DADIP_FILEIO_H */
