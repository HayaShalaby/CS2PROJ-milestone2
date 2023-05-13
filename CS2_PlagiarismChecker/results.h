#ifndef RESULTS_H
#define RESULTS_H

#include <QDialog>
#include "PlagiarismChecker.h"

namespace Ui {
class Results;
}

class Results : public QDialog
{
    Q_OBJECT

public:
    explicit Results(QWidget *parent = nullptr, QString uFile="", QString cFiles="", QChar aType='b');
    ~Results();

private:
    Ui::Results *ui;
};

#endif // RESULTS_H
