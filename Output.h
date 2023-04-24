//Rana Taher, Jana Elmidany, Haya Shalaby
#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "PlagiarismChecker.h"
#include "Document.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Output: public PlagiarismChecker {
    private: 
        float percentPlag;
        float percentRef;
        float percentSim;
        float percentQuotes;
    public: 
        Output(string userFile, string ogFile): PlagiarismChecker(userFile, ogFile); //constructor, executes all PlagiarismChecker functions 
        void Terminal(); //displays percentages in terminal
        void file(); //displays percentages and highlighted text in file
};

#endif //_OUTPUT_H 
