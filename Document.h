//Jana Elmidany, Haya Shalaby, Rana Taher 
#ifndef _DOCUMENT_H
#define _DOCUMENT_H
#include <string> 
using namespace std;

class Document {
    private: 
        string fileName; 
        vector<string> lines;
    public: 
        Document(string FN); //constructor, opens file FN, stores lines in vector lines
        string getFileName(); //getter for fileName
        vector<string> getLines(); //getter for vector lines
        int numOfWords(); //count & returns no. of words in the document 
};

#endif //_DOCUMENT_H
