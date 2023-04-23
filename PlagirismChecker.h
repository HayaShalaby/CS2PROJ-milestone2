/**
 * Project Untitled
 */


#ifndef _PLAGIRISMCHECKER_H
#define _PLAGIRISMCHECKER_H

class PlagirismChecker {
public: 
    
/**
 * @param userFile
 * @param ogFile
 */
PlagirismChecker PlagirismChecker(string userFile, string ogFile);
    
bool isQuote();
    
bool isRef();
    
void calcPlag();
    
void compDoc();
    
int getTotalPlag();
    
int getTotalRef();
    
int getTotalSim();
    
int getTotalQuotes();
    
Document getHighlightDoc();
private: 
    int totalPlag;
    int totalRef;
    int totalSim;
    int totalQuotes;
    Document userDoc;
    vector<Document> database;
    Document highlightDoc;
};

#endif //_PLAGIRISMCHECKER_H