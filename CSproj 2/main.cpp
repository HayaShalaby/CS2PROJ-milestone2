#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Document.h"
#include "PlagiarismChecker.h"


using namespace std;


int main(){
    
    string userfilename;
    cout<<"Enter name of file"<<endl;
    cin >> userfilename;
    
    

    PlagiarismChecker plag;
    plag=PlagiarismChecker();
    plag=PlagiarismChecker(userfilename);
    plag.compDoc();
    
    
    
  return 0;
}

