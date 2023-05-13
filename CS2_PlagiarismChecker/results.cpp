#include "results.h"
#include "ui_results.h"

Results::Results(QWidget *parent, QString uFile, QString cFiles, QChar aType) :
    QDialog(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);
    PlagiarismChecker p(uFile,cFiles,aType);
    p.compDoc();
    ui->textEdit_plag->setText(QString::number(p.getTotalPlag()));
    ui->textEdit_sim->setText(QString::number(p.getTotalSim()));
    ui->textEdit_ref->setText(QString::number(p.getTotalRef()));
    ui->textEdit_quote->setText(QString::number(p.getTotalQuotes()));
    QFile file("userInput.txt");
    QTextStream stream(&file);

    if (file.open(QIODevice::ReadWrite)) {
        file.resize(0);
        stream.flush();
    }
    file.close();

}

Results::~Results()
{
    delete ui;
}
