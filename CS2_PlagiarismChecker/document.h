#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>

class Document {
private:
    QString fileName;
    QVector<QString> lines;
    int numOflines;

public:
    Document() {
        fileName = "";
        numOflines = 0;
    }
    Document(QString FN) {
        setFileName(FN);
        setLines(FN);
    }
    void setFileName(QString FN) {
        fileName = FN;
    }
    void setLines(QString FN) {
        QFile file(FN);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                lines.push_back(line);
            }
            file.close();
        }
    }

    void addLine(QString sentence) {
        lines.push_back(sentence);
    }

    QString setFileName() {
        return fileName;
    }

    QVector<QString> getLines() {
        return lines;
    }

    int numOfLines() {
        return lines.size();
    }
};

#endif //_DOCUMENT_H
