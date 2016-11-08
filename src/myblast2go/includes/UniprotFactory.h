/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UniprotFactory.h
 * Author: veraalva
 *
 * Created on March 17, 2016, 2:14 PM
 */

#ifndef UNIPROTFACTORY_H
#define UNIPROTFACTORY_H

namespace uniprot {

    class UniprotFactory {
    public:
        UniprotFactory();
        UniprotFactory(const UniprotFactory& orig);
        virtual ~UniprotFactory();
        
        unsigned long int size(){
            return uniProt2GO.size();
        }

        std::set<std::string>& GetGOFromUniProt(std::string uniProtID) {
            std::unordered_map<std::string, std::set < std::string>>::iterator it;
            it = uniProt2GO.find(uniProtID);
            if (it != uniProt2GO.end()) {
                return it->second;
            }
            throw exceptions::NotFoundException("Not found GO Terms for the Uniprot entry " + uniProtID);
        }

        std::set<std::string>& GetGOFromGI(int gi) {
            std::unordered_map<int, std::string>::iterator it;
            it = gi2UniProt.find(gi);
            if (it != gi2UniProt.end()) {
                return GetGOFromUniProt(it->second);
            }
            throw exceptions::NotFoundException("Not found GO Terms for the GI " + std::to_string(gi));
        }

        void CreateMapFromTabFile(FILE *fileStream);
    private:
        std::unordered_map<int, std::string> gi2UniProt;
        std::unordered_map<std::string, std::set<std::string>> uniProt2GO;

    };
}

#endif /* UNIPROTFACTORY_H */

