#include <string>
#include <vector>
#include <ctype.h>
#include "PlagiarismChecker.h"
#include "Document.h"
using namespace std;
 
// d is the number of characters in the input alphabet //for stringMatching
#define d 256

PlagiarismChecker::PlagiarismChecker()
{
  userDoc=Document();

  totalPlag = 0;
  totalRef = 0;
  totalSim = 0;
  totalQuotes = 0;
    match=false;
}

PlagiarismChecker::PlagiarismChecker(string userFile)
{
  userDoc=Document(userFile);
  createCorpus();

}

void PlagiarismChecker::createCorpus()
{
  int size;
  string filename;
  Document corpus;

  cout<<"Enter the number of files you want to check from "<<endl;
  cin>>size;

  cout<<"Enter names of files"<<endl;
  
  for(int i=0; i<size ; i++)
    {
      cin>>filename;

      corpus=Document(filename+".txt");
      database.push_back(corpus);
    }
}

bool PlagiarismChecker::isQuote(string Line) {
  
    for(int i=0 ; i<Line.length() ; i++)
    {
        if(Line[i] == '"' )
        {
            for(int j=i ; j<Line.length() ; j++)
            {
                if(Line[j]=='"')
                    return true;
            }
          
        }
    }
  
  return false;
}

bool PlagiarismChecker::isRef(string sent)
{
  if(sent.substr(0,10) == "References" || sent.substr(0,11) == "Works Cited" ) //or should it be sent == "References"
  {
     return true;
  }
  return false;
}

void PlagiarismChecker::calcPlag()
{
  totalPlag = totalSim - (totalQuotes + totalRef);
}

void PlagiarismChecker::compDoc() // We will count the words for refrences and quotes here -rana
{
  vector <string> dataLines,userLines;
  userLines=userDoc.getLines();
  for(int i=0 ; i<database.size() ; i++)
  {
    dataLines=database[i].getLines();
    compLines(dataLines,userLines);
  }
    cout<<"The number of lines in a quotation: "<<totalQuotes<<endl;
    cout<<"The number of lines in references: "<<totalRef<<endl;
    calcPlag();
    cout<<"The number of lines that are plagiraised: "<<totalPlag<<endl;
}

vector <string> PlagiarismChecker::createPat(vector <string> patterns)
{
    string temp;
    int count;
    vector <string> fullPats;
    
    for(int s=0 ; s<fullPats.size()+1 ; s++)
    {
        temp="";
        count=0;
        
        while(count<5 && count<patterns.size() )
        {
            temp += ' '+patterns[count];
            count++;
        }
        if(temp!=""){
            fullPats.push_back(temp);}
        else{
            break;
        }
        
        patterns.erase(patterns.begin());
        if(patterns.size()<5)
            break;
    }
    
    return fullPats;
}

void PlagiarismChecker::set_type(char ty)
{
    type=ty;
}

void PlagiarismChecker::compLines(vector <string> data , vector <string> user) // We will count the words for refrences and quotes here
{
  long threshold;
    bool x;
    
    vector <string> patterns;// vector of words
    vector <string> fullPats;// vector of patterns
    
  for(int j=0; j<user.size(); j++)
  {
      
       
          x=isRef(user[j]);
      
          
          if(x==true)
          {
            cout<<"The remaining is refreneces"<<endl;
              for(int in=j ; in<user.size() ; in++)
              {
                  totalRef ++;
                  totalSim ++;
              }
              break;
          }
          else if(isQuote(user[j]))
            {
              cout<<"a quote was found"<<endl;
                totalQuotes++;
                totalSim ++;
            }
          else
          {
              patterns=getPat(user[j]);
                if(patterns.size()<5)
                {
                    continue;
                }
                
                fullPats=createPat(patterns);
              
              bool rabin=false;
        if(type=='r')
        {
            for(int index=0 ; index<fullPats.size() ;index++ ){
                for(int k=0 ; k<data[k].size() ; k++)
                {
                   
                    if(rabinKarpSearch(fullPats[index], data[k] , 97))
                    {
                        rabin=true;
                        totalSim ++;
                        break;
                    }
                }
                
                if(rabin)
                    break;
                }
        }
        else{
            for(int k=0 ; k<data[k].size() ; k++)
            {
               
                if(data[k].length() > user[j].length())
                    threshold=user[j].length()/2;
                else
                    threshold=data[j].length()/2;


                if(bruteforce(user[j],data[k],threshold))
                {
                    totalSim ++;
                    break;
                }
            }
        }
                  
          }
      }
}



bool PlagiarismChecker::bruteforce(string usertxt, string datatxt, long threshold )
{
    int distance=hammingDistance( usertxt, datatxt);
    return (distance <= threshold);
}

 vector <string> PlagiarismChecker::getPat(string sentence)
  {
     vector <string> pattern;
     string temp;
     
     for(int i=0 ; i<sentence.length();)
     {
          temp="";
         if(sentence[i]==' ')
         {
             i++;
             continue;
         }
         for(int j=i ; j<sentence.length() ; j++)
         {
             if (sentence[j] ==' ')
             {
                 break;
             }
             temp += sentence[j];
         }
         
         pattern.push_back(temp);
         i += temp.length();
     }
     
     return pattern;
     
  }

int PlagiarismChecker::hammingDistance(string str1, string str2)
{
    int distance = 0;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            distance++;
        }
    }
    return distance;
}

bool PlagiarismChecker::rabinKarpSearch(string pat, string txt , int q)
{
        long M = pat.length();
        long N = txt.length();
        int i, j;
        int p = 0; // hash value for pattern
        int t = 0; // hash value for txt
        int h = 1;
    
        // The value of h would be "pow(d, M-1)%q"
        for (i = 0; i < M - 1; i++)
            h = (h * d) % q;

        // Calculate the hash value of pattern and first
        // window of text
        for (i = 0; i < M; i++) {
            p = (d * p + pat[i]) % q;
            t = (d * t + txt[i]) % q;
        }

        // Slide the pattern over text one by one
        for (i = 0; i <= N - M; i++) {

            // Check the hash values of current window of text
            // and pattern. If the hash values match then only
            // check for characters one by one
            if (p == t) {
                /* Check for characters one by one */
                for (j = 0; j < M; j++) {
                    if (txt[i + j] != pat[j]) {
                        break;
                    }
                }

                // if p == t and pat[0...M-1] = txt[i, i+1,
                // ...i+M-1]

                if (j == M)
                {
                    cout << "Pattern found at index " << i
                         << endl;
                   return true;
                }
            }

            // Calculate hash value for next window of text:
            // Remove leading digit, add trailing digit
            if (i < N - M) {
                t = (d * (t - txt[i] * h) + txt[i + M]) % q;

                // We might get negative value of t, converting
                // it to positive
                if (t < 0)
                    t = (t + q);
            }
        }
    return false;
}


int PlagiarismChecker::getTotalPlag()
{
  return totalPlag;
}

int PlagiarismChecker::getTotalRef()
{
  return totalRef;
}

int PlagiarismChecker::getTotalSim()
{
  return totalSim;
}

int PlagiarismChecker::getTotalQuotes()
{
  return totalQuotes;
}





