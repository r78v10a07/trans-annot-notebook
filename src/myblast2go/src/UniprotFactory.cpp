/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UniprotFactory.cpp
 * Author: veraalva
 * 
 * Created on March 17, 2016, 2:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <exception>
#include <cstdlib>
#include <unordered_map>
#include <set>

#include "berror.h"
#include "bmemory.h"
#include "bstring.h"

#include "Exceptions.h"
#include "UniprotFactory.h"

using namespace std;
using namespace exceptions;
using namespace uniprot;

UniprotFactory::UniprotFactory() {
}

UniprotFactory::UniprotFactory(const UniprotFactory& orig) {
}

UniprotFactory::~UniprotFactory() {
}

void UniprotFactory::CreateMapFromTabFile(FILE* fileStream) {
    int lineNumber = 0;
    size_t i, bufferSize, read, backupLineSize;
    char *buffer, *newLine, *str, *backupLine, *completeLine, *id;
    char **fields = NULL;
    size_t fieldsSize = 0;
    char **fields1 = NULL;
    size_t fieldsSize1 = 0;

    if (!fileStream) {
        throw FileFoundException("Can't open map file in CreateMapFromTabFile.");
    }

    backupLineSize = bufferSize = 100000000;
    buffer = (char *) allocate(sizeof (char) * (bufferSize + 1), __FILE__, __LINE__);
    backupLine = (char *) allocate(sizeof (char) * (bufferSize + 1), __FILE__, __LINE__);

    *backupLine = 0;
    while (!feof(fileStream)) {
        read = fread(buffer, sizeof (char), bufferSize, fileStream);
        buffer[read] = 0;
        if (feof(fileStream)) {
            if (buffer[read - 1] != '\n') {
                buffer[read] = '\n';
                buffer[read + 1] = 0;
            }
        }
        str = buffer;
        while ((newLine = strchr(str, '\n')) != NULL) {
            *newLine = 0;
            if (*backupLine != 0) {
                if (strlen(backupLine) + strlen(str) + 1 > backupLineSize) {
                    backupLineSize += backupLineSize;
                    backupLine = (char *) reallocate(backupLine, sizeof (char) * (backupLineSize + 1), __FILE__, __LINE__);
                }
                strcat(backupLine, str);
                completeLine = backupLine;
            } else {
                completeLine = str;
            }

            if (*completeLine != '#') {
                printf("\tparsing line %10d\r", ++lineNumber);
                fieldsSize = splitString(&fields, completeLine, "\t");
                if (fields[4] && fields[6]) {
                    fieldsSize1 = splitString(&fields1, fields[4], ";");
                    for (i = 0; i < fieldsSize1; i++) {
                        id = strdupdel(fields1[i], ' ');
                        gi2UniProt.insert(pair<int, string>(atoi(id), fields[0]));
                        free(id);
                    }
                    freeArrayofPointers((void **) fields1, fieldsSize1);
                    
                    fieldsSize1 = splitString(&fields1, fields[6], ";");
                    set<string> go;
                    for (i = 0; i < fieldsSize1; i++) {
                        id = strdupdel(fields1[i], ' ');
                        go.insert(id);
                        free(id);
                    }
                    uniProt2GO.insert(pair<string, set < string >> (fields[0], go));
                    freeArrayofPointers((void **) fields1, fieldsSize1);
                }
                freeArrayofPointers((void **) fields, fieldsSize);
            }
            *backupLine = 0;
            str = newLine + 1;
        }


        if (strlen(str) > 0) {
            if (strlen(backupLine) + strlen(str) + 1 > backupLineSize) {
                backupLineSize += backupLineSize;
                backupLine = (char *) reallocate(backupLine, sizeof (char) * (backupLineSize + 1), __FILE__, __LINE__);
            }
            strcat(backupLine, str);
        }
    }
    
    printf("\tparsing line %10d\n", lineNumber);

    free(buffer);
    free(backupLine);
}
