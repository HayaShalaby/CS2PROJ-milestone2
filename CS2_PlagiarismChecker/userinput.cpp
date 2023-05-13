#include "userinput.h"
#include "ui_userinput.h"

userInput::userInput(QWidget *parent,QChar type) :
    QDialog(parent),
    ui(new Ui::userInput)
{
    ui->setupUi(this);
    alg_type=type;
}

userInput::~userInput()
{
    delete ui;
}

void userInput::on_pushButton_confirm_clicked()
{
    QFile file("userInput.txt");
    QString input;
    QTextStream stream(&file);

    if (file.open(QIODevice::ReadWrite)) {
        input=ui->textEdit_uInput->toPlainText();
        if(input==""){
            ui->textEdit_uInput->setText("This section cannot be left empty.\nPlease enter data.");
        }
        else{
        stream<<input;
        stream.flush();
        Results *results = new Results(0,"userInput.txt","corpus_names",alg_type);
        this->close();
        results->exec();
        }
    }

    file.close();
}


