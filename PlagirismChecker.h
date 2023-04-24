//Haya Shalaby, Rana Taher, Jana Elmidany
#ifndef _PLAGIARISMCHECKER_H
#define _PLAGIARISMCHECKER_H

#include <string>
#include <fstream>
#include <iostream>
#include "Pattern.h"
#include "Document.h"
using namespace std;

class PlagiarismChecker {
    private: 
        int totalPlag;
        int totalRef;
        int totalSim;
        int totalQuotes;
        Document userDoc;
        vector<Document> database;
        Document highlightDoc;
    public: 
        PlagiarismChecker(string userFile, string ogFile); //opens userFile and ogFile 
        bool isQuote(); //checks if similar line is a quotation & increments totalQuotes if true 
        bool isRef();  //looks for reference page & adds count of all words starting there to totalRef
        void calcPlag(); //calculates totalPlag by subtracting totalRef and totalQuotes from totalSim
        void compDoc(); //compares userDoc against database for similarity, produces highlighted document 
        int getTotalPlag(); //getter for totalPlag
        int getTotalRef(); //getter for totalRef 
        int getTotalSim(); //getter for totalSim 
        int getTotalQuotes(); //getter for totalQuotes 
        Document getHighlightDoc(); //getter for highlightDoc  
};

#endif //_PLAGIARISMCHECKER_H
