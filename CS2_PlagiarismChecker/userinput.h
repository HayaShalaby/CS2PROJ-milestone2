#ifndef USERINPUT_H
#define USERINPUT_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <results.h>

namespace Ui {
class userInput;
}

class userInput : public QDialog
{
    Q_OBJECT

public:
    explicit userInput(QWidget *parent = nullptr, QChar type='b');
    ~userInput();

private slots:
    void on_pushButton_confirm_clicked();

private:
    Ui::userInput *ui;
    QChar alg_type;

};

#endif // USERINPUT_H
