#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

extern double v0, a;
double v0, a;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb_frame = new PictureBox(ui->frame);
    pb_frame->resize(ui->frame->size());
}


MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_A0_valueChanged(double arg1) { a = arg1*0.0174; }

void MainWindow::on_V0_valueChanged(double arg1) { v0 = arg1; }

void MainWindow::on_OK_clicked() { pb_frame->update(); }
