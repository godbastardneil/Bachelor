#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <random>
#include <cmath>

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_orig_text_textChanged()
{
    tmp_p = 0, M = 0, K = 0, p = 0;
    ui->P_Edit->clear(), ui->M_Edit->clear(), ui->K_Edit->clear();

    ui->lat_table->clear();

    int s = ui->orig_text->toPlainText().size();
    if (s != 0 && s%4 == 0)
    {
        ui->K_Edit->setEnabled(true);
        ui->M_Edit->setEnabled(true);

        ui->crypt_but->setEnabled(false);
        ui->lat_table->setEnabled(false);
    } else
    {
        ui->K_Edit->setEnabled(false);
        ui->M_Edit->setEnabled(false);

        ui->crypt_but->setEnabled(false);
        ui->lat_table->setEnabled(false);
    }
}

void MainWindow::on_M_Edit_valueChanged(int arg1)
{
    M = arg1;
    check_mk();
}
void MainWindow::on_K_Edit_valueChanged(int arg1)
{
    K = arg1;
    check_mk();
}

void MainWindow::on_crypt_but_clicked()
{
    if (check_init_lat())
    {
        crypt();
        decrypt();
    } else { write_lat(); }
}


void MainWindow::write_lat()
{
    ui->lat_table->clear();

    ui->lat_table->setRowCount(M);
    ui->lat_table->setColumnCount(K);


    for (int i=0; i<M; ++i)
    {
        for (int j=0; j<K; ++j)
        {
            ui->lat_table->setItem(i, j, new QTableWidgetItem());
            ui->lat_table->setColumnWidth(j, ui->lat_table->width()/K);
        }
        ui->lat_table->setRowHeight(i, ui->lat_table->height()/M);
    }
}

void MainWindow::check_mk()
{
    ui->P_Edit->clear();
    if (M*K == ui->orig_text->toPlainText().size() && M%2 == 0 && K%2 == 0)
    {
        ui->lat_table->setEnabled(true);
        ui->crypt_but->setEnabled(true);

        p = M*K/4;
        ui->P_Edit->setText(QString::number(p));

        write_lat();

        tmp_p = 0;

    } else
    {
        ui->lat_table->setEnabled(false);
        ui->crypt_but->setEnabled(false);
    }
}

bool MainWindow::check_init_lat()
{
    if (ui->lat_table->rowCount() == M && ui->lat_table->columnCount() == K)
    {
        int tmp = 0;
        for (int i=0; i<M; ++i) {
            for (int j=0; j<K; ++j) {
                if (ui->lat_table->item(i, j)->isSelected())
                {
                    ++tmp;
                    if (ui->lat_table->item(M-1-i, K-1-j)->isSelected() || ui->lat_table->item(M-1-i, j)->isSelected() || ui->lat_table->item(i, K-1-j)->isSelected())
                    { return false; }
                }
            }
        }
        if (tmp != p) { return false; }
    } else { return false; }
    return true;
}


void MainWindow::crypt()
{
    QString str = ui->orig_text->toPlainText();
    QString out(M*K, 'a');

    int tmp = 0;
    for (int i=0; i<M; ++i) {
        for (int j=0; j<K; ++j) {

            if (ui->lat_table->item(i, j)->isSelected())
            {
                out[i*K+j] = str[tmp];
                out[(M-1-i)*K+(K-1-j)] = str[2*p-tmp-1];
                ++tmp;
            }
        }
    }
    tmp = 0;
    for (int i=0; i<M; ++i) {
        for (int j=K-1; j>-1; --j) {

            if (ui->lat_table->item(i, j)->isSelected())
            {
                out[(M-1-i)*K+j] = str[3*p-tmp-1];
                out[i*K+(K-1-j)] = str[3*p+tmp];
                ++tmp;
            }
        }
    }

    ui->crypt_text->setText(out);
}
void MainWindow::decrypt()
{
    QString str = ui->crypt_text->toPlainText();
    QString out(M*K, 'a');

    int tmp = 0;
    for (int i=0; i<M; ++i) {
        for (int j=0; j<K; ++j) {

            if (ui->lat_table->item(i, j)->isSelected())
            {
                out[tmp] = str[i*K+j];
                out[2*p-tmp-1] = str[(M-1-i)*K+(K-1-j)];
                ++tmp;
            }
        }
    }
    tmp = 0;
    for (int i=0; i<M; ++i) {
        for (int j=K-1; j>-1; --j) {

            if (ui->lat_table->item(i, j)->isSelected())
            {
                out[3*p-tmp-1] = str[(M-1-i)*K+j];
                out[3*p+tmp] = str[i*K+(K-1-j)];
                ++tmp;
            }
        }
    }

    ui->decrypt_text->setText(out);
}

/* ШИФРРЕШЕТКАЯВЛЯЕТСЯЧАСТНЫМСЛУЧАЕМШИФРАМАРШРУТНОЙПЕРЕСТАНОВКИ
0100000000
1000101100
0100010001
0001000100
0100000000
0010011001
*/

