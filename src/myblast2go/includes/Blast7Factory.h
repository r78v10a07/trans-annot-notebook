/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Blast7Factory.h
 * Author: veraalva
 *
 * Created on March 18, 2016, 9:37 AM
 */

#ifndef BLAST7FACTORY_H
#define BLAST7FACTORY_H

namespace blast {

    class Blast7Factory {
    public:
        Blast7Factory();
        Blast7Factory(const Blast7Factory& orig);
        virtual ~Blast7Factory();

        int ParsingBlastDirectory(FILE *outStream, FILE *errStream, char* dirName, const char *prefix, const char *sufix, bool recursive, int giColumn, int scoreColumn, double cutoff, uniprot::UniprotFactory& uFactory);
        void ParsingBlastFile(FILE* outStream, FILE *errStream, char* fileName, int giColumn, int scoreColumn, double cutoff, uniprot::UniprotFactory& uFactory);

    private:
        std::vector<int> gi;

    };
}

#endif /* BLAST7FACTORY_H */

