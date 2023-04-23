/**
 * Project Untitled
 */


#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "PlagirismChecker.h"


class Output: public PlagirismChecker {
public: 
    
/**
 * @param userFile
 * @param ogFile
 */
Output Output(string userFile, string ogFile);
    
void Terminal();
    
void file();
private: 
    float percentPlag;
    float percentRef;
    float percentSim;
    float percentQuotes;
};

#endif //_OUTPUT_H