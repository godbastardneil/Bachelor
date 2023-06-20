#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_crypt_Button_clicked()
{
    std::random_shuffle(alfa.begin(), alfa.end());

    qDebug() << alfa;

    crypt();
    decrypt();
}

void MainWindow::crypt()
{
    QString str = ui->orig_Edit->text().toLower().replace(" ", "");
    ui->orig_Edit->setText(str);
    QString out(str.size(), 'a');
    for (int i=0; i<str.size(); ++i)
    {
        int j = alfa.indexOf(str[i])+11;
        if (j > alfa.size()) { j -= alfa.size(); }
        out[i] = alfa[j];
    }
    ui->crypt_Edit->setText(out);
}

void MainWindow::decrypt()
{
    QString str = ui->crypt_Edit->text();
    QString out(str.size(), 'a');
    for (int i=0; i<str.size(); ++i)
    {
        int j = alfa.indexOf(str[i])-11;
        if (j < 0) { j += alfa.size(); }
        out[i] = alfa[j];
    }
    ui->decrypt_Edit->setText(out);
}

// ШИФРРЕШЕТКАЯВЛЯЕТСЯЧАСТНЫМСЛУЧАЕМШИФРАМАРШРУТНОЙПЕРЕСТАНОВКИ
// шифррешеткаявляетсячастнымслучаемшифрамаршрутнойперестановки
