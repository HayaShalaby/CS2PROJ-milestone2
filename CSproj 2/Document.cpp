#include "Document.h"
#include <vector>
#include <iostream>
using namespace std;

Document::Document() {
  fileName = "";
  numOflines = 0;
}

Document::Document(string FN) {
  setFileName(FN);
  setLines(FN);
}

void Document::setFileName(string FN) { fileName = FN; }

void Document::setLines(string FN) {
  fstream file;
  file.open(FN);
  string temp;
  while (!file.eof()) {
    getline(file, temp, '.');
    lines.push_back(temp);
  }
  //cout << lines.size()-1 << endl;
}

void Document::addLine(string sentence) {
  lines.push_back(sentence);

}

string Document::getFileName() { return fileName; }

vector<string> Document::getLines() { return lines; }

int Document::numOfLines()
{
    double L=lines.size();
    return L;
    
}
