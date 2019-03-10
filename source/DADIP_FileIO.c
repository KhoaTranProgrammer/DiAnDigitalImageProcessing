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
 * This file implements for method that reading from file or writing*
 * to file                                                          *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Mar-07-2019                                               *
 *        Initial version implements for APIs:                      *
 *         DaDip_Create_File_Reader                                 *
 *         DaDip_Create_File_Writer                                 *
 *        And some internal functions:                              *
 *         Read_Data_From_File                                      *
 *         Destroy_File_Reader                                      *
 *         Seek_From_Current                                        *
 *         Write_Data_To_File                                       *
 *         Destroy_File_Writer                                      *
 *******************************************************************/

#include "DADIP_FileIO.h"

/* The implementation of method to read amount of data from file */
static dadip_errinfo Read_Data_From_File(DADIP_PTRFILEREADER fileReader, dadip_char **outData, dadip_int bytes)
{
    dadip_errinfo err;
    dadip_char* data;

    err = DADIP_MEMERROR;
    data = NULL;

    CHECK_MEM(fileReader)

    /* In case reaching the end of file */
    if (feof(fileReader->f)) return DADIP_FILEEOF;

    /* Allocate memory to store reading data */
    ALLOC_MEM(data, dadip_char, bytes)

    /* Read data and increase bytesread */
    fread(data, bytes, 1, fileReader->f);
    fileReader->bytesread += bytes;

    *outData = data;

    return DADIP_OK;
ERR_BEG
    FREE_MEM(data)
    return err;
ERR_END
}

/* The implementation of method to destroy file reader instance */
static dadip_void Destroy_File_Reader(DADIP_PTRFILEREADER fileReader)
{
    CHECK_MEM(fileReader)
    if (fileReader->f != NULL) fclose(fileReader->f);
    FREE_MEM(fileReader)
ERR_BEG
    return;
ERR_END
}

/* The implementation of method to move to the new position */
static dadip_void Seek_From_Current(DADIP_PTRFILEREADER fileReader, dadip_int bytes)
{
    CHECK_MEM(fileReader)
    CHECK_ERROR(fseek(fileReader->f, bytes, SEEK_CUR))
ERR_BEG
    return;
ERR_END
}

/* The implementation of method to create the instance of file reader */
dadip_errinfo DaDip_Create_File_Reader(DADIP_2DPTRFILEREADER fileReader, dadip_char* filename)
{
    dadip_errinfo err;

    err = DADIP_MEMERROR;

    /* Allocate DADIP_FILEREADER structure */
    ALLOC_MEM(*fileReader, DADIP_FILEREADER, sizeof(DADIP_FILEREADER))

    /* Open file */
    (*fileReader)->f = fopen(filename, "rb");
    CHECK_MEM((*fileReader)->f);

    /* Assign elements of DADIP_FILEREADER */
    (*fileReader)->bytesread = 0;
    (*fileReader)->destroy = Destroy_File_Reader;
    (*fileReader)->readDataFromFile = Read_Data_From_File;
    (*fileReader)->seekFromCurrent = Seek_From_Current;

    return DADIP_OK;
ERR_BEG
    Destroy_File_Reader(*fileReader);
    return err;
ERR_END
}

/* The implementation of method to write amount of data to file */
static dadip_errinfo Write_Data_To_File(DADIP_PTRFILEWRITER fileWriter, dadip_char *inData, dadip_int bytes)
{
    dadip_errinfo err;

    err = DADIP_MEMERROR;

    CHECK_MEM(fileWriter)

    /* Write data and increase byteswrite */
    fwrite(inData, 1, bytes, fileWriter->f);
    fileWriter->byteswrite += bytes;
    
    return DADIP_OK;
ERR_BEG
    return err;
ERR_END
}

/* The implementation of method to destroy file writer instance */
static dadip_void Destroy_File_Writer(DADIP_PTRFILEWRITER fileWriter)
{
    CHECK_MEM(fileWriter)
    if (fileWriter->f != NULL) fclose(fileWriter->f);
    FREE_MEM(fileWriter)

ERR_BEG
    return;
ERR_END
}

/* The implementation of method to create the instance of file writer */
dadip_errinfo DaDip_Create_File_Writer(DADIP_2DPTRFILEWRITER fileWriter, dadip_char* filename)
{
    dadip_errinfo err;

    err = DADIP_MEMERROR;

    /* Allocate DADIP_FILEWRITER structure */
    ALLOC_MEM(*fileWriter, DADIP_FILEWRITER, sizeof(DADIP_FILEWRITER))

    /* Open file */
    (*fileWriter)->f = fopen(filename, "wb");
    CHECK_MEM((*fileWriter)->f);

    /* Assign elements of DADIP_FILEWRITER */
    (*fileWriter)->byteswrite = 0;
    (*fileWriter)->destroy = Destroy_File_Writer;
    (*fileWriter)->writeDataToFile = Write_Data_To_File;

    return DADIP_OK;
ERR_BEG
    Destroy_File_Writer(*fileWriter);
    return err;
ERR_END
}
