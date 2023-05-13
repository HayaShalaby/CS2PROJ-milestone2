#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <userinput.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_rb_clicked();

    void on_pushButton_bf_clicked();

    void on_pushButton_df_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
