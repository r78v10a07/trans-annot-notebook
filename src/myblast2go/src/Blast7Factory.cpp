/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Blast7Factory.cpp
 * Author: veraalva
 * 
 * Created on March 18, 2016, 9:37 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <dirent.h>

#include <iostream>
#include <exception>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <vector>
#include <map>

#include "berror.h"
#include "bmemory.h"
#include "bstring.h"

#include "Exceptions.h"
#include "UniprotFactory.h"
#include "Blast7Factory.h"

using namespace std;
using namespace exceptions;
using namespace uniprot;
using namespace blast;

using namespace blast;

Blast7Factory::Blast7Factory() {
}

Blast7Factory::Blast7Factory(const Blast7Factory& orig) {
}

Blast7Factory::~Blast7Factory() {
}

void Blast7Factory::ParsingBlastFile(FILE* outStream,FILE* errStream, char* fileName, int giColumn, int scoreColumn, double cutoff, uniprot::UniprotFactory& uFactory) {
    FILE *blastFile = (FILE *) checkPointerError(fopen(fileName, "r"), "Can't open Blast file", __FILE__, __LINE__, -1);

    size_t bufferSize, read, backupLineSize;
    char *buffer, *newLine, *str, *backupLine, *completeLine;
    char **fields = NULL;
    size_t fieldsSize = 0;
    bool useLine = false;
    set<string> goSet;
    vector<string>::iterator goIt;

    backupLineSize = bufferSize = 100000000;
    buffer = (char *) allocate(sizeof (char) * (bufferSize + 1), __FILE__, __LINE__);
    backupLine = (char *) allocate(sizeof (char) * (bufferSize + 1), __FILE__, __LINE__);

    *backupLine = 0;
    while (!feof(blastFile)) {
        read = fread(buffer, sizeof (char), bufferSize, blastFile);
        buffer[read] = 0;
        if (feof(blastFile)) {
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
                useLine = true;
                fieldsSize = splitString(&fields, completeLine, "\t");

                if (giColumn < 0 && giColumn >= fieldsSize) {
                    cerr << "\nERROR!!" << endl;
                    cerr << "giColumn " << giColumn << " used is not correct. The current Blast output has " << fieldsSize << " tab separated fields per line" << endl;
                    exit(-1);
                }

                if (scoreColumn >= fieldsSize) {
                    cerr << "\nERROR!!" << endl;
                    cerr << "scoreColumn " << scoreColumn << " used is not correct. The current Blast output has " << fieldsSize << " tab separated fields per line" << endl;
                    exit(-1);
                }

                if (scoreColumn >= 0 && cutoff > strtod(fields[scoreColumn], NULL)) {
                    useLine = false;
                }

                if (useLine) {
                    try {
                        if (find(gi.begin(), gi.end(), atoi(fields[giColumn])) == gi.end()) {
                            goSet = uFactory.GetGOFromGI(atoi(fields[giColumn]));
                            for (auto it = goSet.begin(); it != goSet.end(); ++it) {
                                fprintf(outStream, "%d\t%s\n", atoi(fields[giColumn]), it->c_str());
                            }
                            gi.push_back(atoi(fields[giColumn]));
                        }
                    } catch (NotFoundException &ex) {
                        fprintf(errStream, "%s\n", fields[giColumn]);
                    }
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

    free(buffer);
    free(backupLine);
    fclose(blastFile);
}

int Blast7Factory::ParsingBlastDirectory(FILE* outStream, FILE* errStream, char* dirName, const char* prefix, const char* sufix, bool recursive, int giColumn, int scoreColumn, double cutoff, UniprotFactory& uFactory) {
    int result = 0;
    struct dirent *dp;
    bool read = false;
    size_t len;
    char *fileName;

    if (!outStream) {
        throw FileFoundException("NULL out stream pointer");
    }

    if (!errStream) {
        throw FileFoundException("NULL out stream pointer");
    }

    DIR *dirp = (DIR *) checkPointerError(opendir(dirName), "Can't open input directory", __FILE__, __LINE__, -1);
    len = strlen(dirName);
    fileName = (char *) allocate(sizeof (char) * (len + 1), __FILE__, __LINE__);

    while ((dp = readdir(dirp)) != NULL) {
        if (dp->d_name[0] != '.') {
            if (dp->d_type == DT_REG) {
                read = false;
                if (!prefix && !sufix) {
                    read = true;
                } else {
                    if (prefix && !sufix) {
                        if (strncmp(dp->d_name, prefix, strlen(prefix)) == 0) read = true;
                    } else if (!prefix && sufix) {
                        if (strbcmp(dp->d_name, sufix) == 0) read = true;
                    } else if (prefix && sufix) {
                        if (strncmp(dp->d_name, prefix, strlen(prefix)) == 0 && strbcmp(dp->d_name, sufix) == 0) read = true;
                    }
                }
                if (read) {
                    if (len < strlen(dirName) + strlen(dp->d_name) + 2) {
                        len = strlen(dirName) + strlen(dp->d_name) + 2;
                        fileName = (char *) reallocate(fileName, sizeof (char) * len, __FILE__, __LINE__);
                    }
                    sprintf(fileName, "%s/%s", dirName, dp->d_name);
                    ParsingBlastFile(outStream, errStream, fileName, giColumn, scoreColumn, cutoff, uFactory);
                    cout << "File: " << fileName << " parsed." << endl;
                    result++;
                }
            } else if (dp->d_type == DT_DIR && recursive) {
                if (len < strlen(dirName) + strlen(dp->d_name) + 2) {
                    len = strlen(dirName) + strlen(dp->d_name) + 2;
                    fileName = (char *) reallocate(fileName, sizeof (char) * len, __FILE__, __LINE__);
                }
                sprintf(fileName, "%s/%s", dirName, dp->d_name);
                result += ParsingBlastDirectory(outStream, errStream, fileName, prefix, sufix, recursive, giColumn, scoreColumn, cutoff, uFactory);
            }
        }
    }

    closedir(dirp);
    free(fileName);
    return result;
}
