#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb_frame = new picturebox(ui->frame);
    pb_frame->resize(ui->frame->size());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_X2_valueChanged(int arg1) { pb_frame->set_b_x(arg1); }
void MainWindow::on_Y2_valueChanged(int arg1) { pb_frame->set_b_y(arg1); }

void MainWindow::on_Ok_line_clicked()
{
    pb_frame->paint_line();
    pb_frame->repaint();
}

void MainWindow::on_R0_valueChanged(int arg1) { pb_frame->set_r(arg1); }

void MainWindow::on_Ok_cyrcle_clicked()
{
    pb_frame->paint_cyrcle();
    pb_frame->repaint();
}

void MainWindow::on_R1_valueChanged(int arg1) { pb_frame->set_r1(arg1); }

void MainWindow::on_R2_valueChanged(int arg1) { pb_frame->set_r2(arg1); }

void MainWindow::on_Ok_ellipse_clicked()
{
    pb_frame->paint_ellipse();
    pb_frame->repaint();
}
