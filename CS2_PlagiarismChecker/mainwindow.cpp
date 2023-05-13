#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_rb_clicked()
{
    userInput *userinput = new userInput(0,'r');
    this->close();
    userinput->exec();
}


void MainWindow::on_pushButton_bf_clicked()
{
    userInput *userinput = new userInput(0,'b');
    this->close();
    userinput->exec();

}


void MainWindow::on_pushButton_df_clicked()
{
    userInput *userinput = new userInput();
    this->close();
    userinput->exec();
}

