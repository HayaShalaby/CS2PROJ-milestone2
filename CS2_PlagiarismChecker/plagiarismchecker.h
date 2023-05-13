//Haya Shalaby, Rana Taher, Jana Elmidany
#ifndef _PLAGIARISMCHECKER_H
#define _PLAGIARISMCHECKER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include "Document.h"

class PlagiarismChecker {
private:
    int totalPlag;
    int totalRef;
    int totalSim;
    int totalQuotes;
    Document userDoc;
    QVector<Document> database;
    QVector<int> quoteIndex;
    Document highlightDoc;
    bool match;
    QChar type;

public:
    PlagiarismChecker()
    {
        userDoc = Document();

        totalPlag = 0;
        totalRef = 0;
        totalSim = 0;
        totalQuotes = 0;
        match = false;
    }

    PlagiarismChecker(QString userFile, QString corpusFiles, QChar aType)
    {
        userDoc = Document(userFile);
        set_type(aType);
        createCorpus(corpusFiles);
    }

    void createCorpus(QString corpusFiles)
    {
        QString filename;
        Document corpus;
        QFile files(corpusFiles);

        if (files.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&files);
            while (!files.atEnd()) {
                in >> filename;
                corpus = Document(filename);
                database.push_back(corpus);
            }
            files.close();
        }
    }

    bool isQuote(QString line)
    {
        if (line.contains('"'))
        {
            int firstIndex = line.indexOf('"');
            int lastIndex = line.lastIndexOf('"');
            if (firstIndex != lastIndex)
                return true;
        }
        return false;
    }

    bool isRef(QString sent)
    {
        if (sent.startsWith("References") || sent.startsWith("Works Cited"))
        {
            return true;
        }
        return false;
    }

    void calcPlag()
    {
        totalPlag = totalSim - (totalQuotes + totalRef);
    }

    void compDoc()
    {
        QVector<QString> dataLines, userLines;
        userLines = userDoc.getLines();
        for (int i = 0; i < database.size(); i++)
        {
            dataLines = database[i].getLines();
            compLines(dataLines, userLines,type);
        }
        calcPlag();
    }

    QVector<QString> createPat(QVector<QString> patterns)
    {
        QVector<QString> fullPats;

        for (int s = 0; s < fullPats.size() + 1; s++)
        {
            QString temp = "";
            int count = 0;

            while (count < 5 && count < patterns.size())
            {
                temp += ' ' + patterns[count];
                count++;
            }

            if (temp != "")
            {
                fullPats.push_back(temp);
            }
            else
            {
                break;
            }

            patterns.erase(patterns.begin());
            if (patterns.size() < 5)
                break;
        }

        return fullPats;
    }

    void set_type(QChar ty)
    {
        type = ty;
    }

    void compLines(QVector<QString> data , QVector<QString> user, QChar type)
    {
        long threshold;
        bool x;
        QVector<QString> patterns;// vector of words
        QVector<QString> fullPats;// vector of patterns

        for(int j=0; j<user.size(); j++)
        {
            x=isRef(user[j]);
            if(x==true && totalRef==0)
            {
                for(int in=j ; in<user.size() ; in++)
                {
                    totalRef ++;
                    totalSim ++;
                }
                break;
            }
            else if(isQuote(user[j]))
            {
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

    bool bruteforce(QString usertxt, QString datatxt, qint64 threshold )
    {
        int distance=hammingDistance( usertxt, datatxt);
        return (distance <= threshold);
    }

    QVector<QString> getPat(QString sentence)
    {
        QVector<QString> pattern;
        QString temp;

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

    int hammingDistance(QString str1, QString str2)
    {
        int distance = 0;
        for (int i = 0; i < str1.length(); i++) {
            if (str1[i] != str2[i]) {
                distance++;
            }
        }
        return distance;
    }

    bool rabinKarpSearch(QString pat, QString txt , int q)
    {
        int d = 256; // number of characters in the input alphabet
        long M = pat.length();
        long N = txt.length();
        int i, j;
        int p = 0; // hash value for pattern
        int t = 0; // hash value for txt
        int h = 1;

        // The value of h would be "pow(d, M-1)%q"
        for (i = 0; i < M - 1; i++)
            h = (h * d) % q;

        // Calculate the hash value of pattern and first window of text
        for (i = 0; i < M; i++) {
            p = (d * p + pat[i].toLatin1()) % q;
            t = (d * t + txt[i].toLatin1()) % q;
        }

        // Slide the pattern over text one by one
        for (i = 0; i <= N - M; i++) {
            // Check the hash values of current window of text and pattern
            // If the hash values match, then only check for characters one by one
            if (p == t) {
                /* Check for characters one by one */
                for (j = 0; j < M; j++) {
                    if (txt[i + j] != pat[j]) {
                        break;
                    }
                }

                // If p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
                if (j == M) {
                    return true;
                }
            }

            // Calculate hash value for next window of text:
            // Remove leading digit, add trailing digit
            if (i < N - M) {
                t = (d * (t - txt[i].toLatin1() * h) + txt[i + M].toLatin1()) % q;

                // We might get negative value of t, converting it to positive
                if (t < 0)
                    t = (t + q);
            }
        }

        return false;
    }

    int getTotalPlag()
    {
        return totalPlag;
    }

    int getTotalRef()
    {
        return totalRef;
    }

    int getTotalSim()
    {
        return totalSim;
    }

    int getTotalQuotes()
    {
        return totalQuotes;
    }


};


#endif //_PLAGIARISMCHECKER_H
