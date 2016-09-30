/* 
 * File:   main.cpp
 * Author: veraalva
 *
 * Created on March 17, 2016, 2:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

#include <iostream>
#include <exception>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>

#include "berror.h"
#include "bmemory.h"
#include "bstring.h"

#include "TimeUtils.h"
#include "Exceptions.h"
#include "UniprotFactory.h"
#include "Blast7Factory.h"

using namespace std;
using namespace exceptions;
using namespace uniprot;
using namespace blast;

char *program_name;
TimeUtils *TimeUtils::s_instance = 0;

void print_usage(FILE *stream, int exit_code) {
    fprintf(stream, "\n********************************************************************************\n");
    fprintf(stream, "\nUsage: %s \n", program_name);
    fprintf(stream, "\n\n%s options:\n\n", program_name);
    fprintf(stream, "-h,   --help                        Display this usage information.\n");
    fprintf(stream, "-d    --db                          Uncompressed Uniprot ID mapping TSV file from:\nftp://ftp.uniprot.org/pub/databases/uniprot/current_release/knowledgebase/idmapping/idmapping_selected.tab.gz\n");
    fprintf(stream, "-g,   --giColumn                    GI column in the Blast output. Column stating in 1.\n");
    fprintf(stream, "-i,   --in                          Directory with all BLast results. Blast output using option:\n");
    fprintf(stream, "                                    -outfmt \"7 qacc sgi slen qstart qend sstart send evalue bitscore score length pident nident mismatch positive gapopen gaps ppos qcovs qcovhsp\"\n");
    fprintf(stream, "-l,   --scoreColumn                 Column in the Blast output with the score to cutoff. Default: not cutoff. Set cutoff with option -c. Column stating in 1.\n");
    fprintf(stream, "-c,   --cutoff                      Minimum cutoff to be used. Required option if -s is used.\n");
    fprintf(stream, "-o,   --out                         Output file name. Format: GI<tab>GOID\n");
    fprintf(stream, "-e,   --err                         Error output file name with GI without GO terms. Format: GI<tab>[uniprot_ID]\n");
    fprintf(stream, "-r,   --recursive                   Explore recursively the in directory. Default: False\n");
    fprintf(stream, "-p,   --prefix                      Prefix for the Blast output file. Not use it for ignoring prefix.\n");
    fprintf(stream, "-s,   --subfix                      Subfix for the Blast output file. Not use it for ignoring subfix.\n");
    fprintf(stream, "********************************************************************************\n\n");
    fprintf(stream, "            Roberto Vera Alvarez (e-mail: veraalva@ncbi.nlm.nih.gov)\n\n");
    fprintf(stream, "********************************************************************************\n");
    exit(0);
}

/*
 * 
 */
int main(int argc, char** argv) {
    clock_t start = clock();
    int next_option;
    const char* const short_options = "hd:i:rp:s:o:e:g:l:c:";
    FILE *dbStream = NULL;
    FILE *outStream = NULL;
    FILE *errStream = NULL;
    double cutoff = 0.0;
    int scoreColumn = -1;
    int giColumn = -1;
    char *inName = NULL;
    bool recursive = false;
    char *prefix = NULL;
    char *subfix = NULL;
    UniprotFactory uFactory;
    Blast7Factory bFactory;
    int result;

    program_name = argv[0];

    const struct option long_options[] = {
        { "help", 0, NULL, 'h'},
        { "db", 1, NULL, 'd'},
        { "in", 1, NULL, 'i'},
        { "out", 1, NULL, 'o'},
        { "err", 1, NULL, 'e'},
        { "recursive", 0, NULL, 'r'},
        { "prefix", 1, NULL, 'p'},
        { "subfix", 1, NULL, 's'},
        { "giColumn", 1, NULL, 'g'},
        { "scoreColumn", 1, NULL, 'l'},
        { "cutoff", 1, NULL, 'c'},
        { NULL, 0, NULL, 0} /* Required at end of array.  */
    };

    do {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);

        switch (next_option) {
            case 'h':
                print_usage(stdout, 0);

            case 'd':
                dbStream = (FILE *) checkPointerError(fopen(optarg, "r"), "Can't open Uniprot ID mapping TSV file", __FILE__, __LINE__, -1);
                break;

            case 'o':
                outStream = (FILE *) checkPointerError(fopen(optarg, "w"), "Can't open output file", __FILE__, __LINE__, -1);
                break;

            case 'e':
                errStream = (FILE *) checkPointerError(fopen(optarg, "w"), "Can't open error output file", __FILE__, __LINE__, -1);
                break;

            case 'i':
                inName = strdup(optarg);
                break;

            case 'g':
                giColumn = atoi(optarg) - 1;
                break;

            case 'l':
                scoreColumn = atoi(optarg) - 1;
                break;

            case 'c':
                cutoff = strtod(optarg, NULL);
                break;

            case 'r':
                recursive = true;
                break;

            case 'p':
                prefix = strdup(optarg);
                break;

            case 's':
                subfix = strdup(optarg);
                break;
        }
    } while (next_option != -1);

    if (!inName) {
        cerr << "\nDirectory with all BLast results is required. See -i option" << endl;
        print_usage(stderr, -1);
    }

    if (giColumn == -1) {
        cerr << "\nGI column in Blast output is required. See -g option" << endl;
        print_usage(stderr, -1);
    }

    cout << "Loading Uniprot DB\n" << endl;
    uFactory.CreateMapFromTabFile(dbStream);
    cout << "Uniprot DB loaded with " << uFactory.size() << " IDs" << endl;

    cout << "Parsing Blast directory" << endl;
    result = bFactory.ParsingBlastDirectory(outStream, errStream, inName, prefix, subfix, recursive, giColumn, scoreColumn, cutoff, uFactory);
    cout << "Analyzed " << result << " Blast outputs" << endl;


    //    for (int i = 0; i < 500; i++) {
    //        try {
    //            go = uFactory.GetGOFromGI(gis[i]);
    //            for (auto it = go.begin(); it != go.end(); ++it) {
    //                cout << gis[i] << "\t" << *it << endl;
    //            }
    //        } catch (NotFoundException& ex) {
    //            cerr << ex.what() << endl;
    //        }
    //    }

    if (inName) free(inName);
    if (prefix) free(prefix);
    if (subfix) free(subfix);
    fclose(dbStream);
    fclose(outStream);
    fclose(errStream);
    cout << "Total elapse time: " << TimeUtils::instance()->GetTimeMinFrom(start) << " minutes" << endl;
    return 0;
}

