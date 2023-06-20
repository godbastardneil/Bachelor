#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb = new picturebox(ui->frame);
    pb->resize(ui->frame->size());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_rep_clicked()
{
    pb->reset();
}

void MainWindow::on_zalit_clicked()
{
    pb->postroch_zal();
    pb->repaint();
}

void MainWindow::on_zatravka_clicked()
{
    pb->zatravca();
    pb->repaint();
}

void MainWindow::on_skan_clicked()
{
    pb->postroch_ckan();
    pb->repaint();
}

