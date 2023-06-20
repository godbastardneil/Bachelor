#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb = new picturebox(ui->frame);
    pb->resize(ui->frame->size());
    pb->paint();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::draw()
{
    pb->paint();
    pb->repaint();
}

void MainWindow::on_steps_valueChanged(int arg1) { pb->set_steps(arg1); }

void MainWindow::on_L_vol_valueChanged(double arg1) { pb->set_l(arg1); }

void MainWindow::on_kol_valueChanged(int arg1) { pb->set_kol(arg1); }

void MainWindow::on_Ok_clicked() { draw(); }


