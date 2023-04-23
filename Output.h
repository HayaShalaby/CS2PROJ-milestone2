//Rana Taher, Jana Elmidany, Haya Shalaby
#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "PlagirismChecker.h"
#include <string>

class Output: public PlagirismChecker {
    private: 
        float percentPlag;
        float percentRef;
        float percentSim;
        float percentQuotes;
    public: 
        Output(string userFile, string ogFile): PlagirismChecker(userFile, ogFile); //constructor, executes all PlagirismChecker functions 
        void Terminal(); //displays percentages in terminal
        void file(); //displays percentages and highlighted text in file
};

#endif //_OUTPUT_H 
