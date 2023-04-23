/**
 * Project Untitled
 */


#ifndef _DOCUMENT_H
#define _DOCUMENT_H

class Document {
public: 
    
/**
 * @param FN
 */
Document Document(string FN);
    
string getFileName();
    
vector<string> getLines();
    
int numOfWords();
private: 
    string fileName;
    vector<string> lines;
};

#endif //_DOCUMENT_H