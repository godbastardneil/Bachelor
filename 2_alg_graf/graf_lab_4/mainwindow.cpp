#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb_frame = new picturebox(ui->frame);
    pb_frame->resize(ui->frame->size());
    pb_frame->paint();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::draw()
{
    pb_frame->paint();
    pb_frame->repaint();
}

void MainWindow::on_X_A_valueChanged(int arg1)
{
    pb_frame->a.setX(arg1);
    if (pb_frame->chechtr()) { draw(); }
}
void MainWindow::on_Y_A_valueChanged(int arg1)
{
    pb_frame->a.setY(arg1);
    if (pb_frame->chechtr()) { draw(); }
}


void MainWindow::on_X_B_valueChanged(int arg1)
{
    pb_frame->b.setX(arg1);
    if (pb_frame->chechtr()) { draw(); }
}
void MainWindow::on_Y_B_valueChanged(int arg1)
{
    pb_frame->b.setY(arg1);
    if (pb_frame->chechtr()) { draw(); }
}


void MainWindow::on_X_C_valueChanged(int arg1)
{
    pb_frame->c.setX(arg1);
    if (pb_frame->chechtr()) { draw(); }
}
void MainWindow::on_Y_C_valueChanged(int arg1)
{
    pb_frame->c.setY(arg1);
    if (pb_frame->chechtr()) { draw(); }
}

void MainWindow::on_X_T_valueChanged(int arg1)
{
    pb_frame->t.setX(arg1);
    if (pb_frame->chechtr()) { draw(); }
}
void MainWindow::on_Y_T_valueChanged(int arg1)
{
    pb_frame->t.setY(arg1);
    if (pb_frame->chechtr()) { draw(); }
}


void MainWindow::on_Koo_valueChanged(double arg1)
{
    pb_frame->k = arg1;
    if (pb_frame->chechtr()) { draw(); }
}

void MainWindow::on_angle_valueChanged(int arg1)
{
    pb_frame->a0 = (arg1*(atan(1)*4))/180;
    if (pb_frame->chechtr()) { draw(); }
}

void MainWindow::on_mirror_toggled(bool checked)
{
    pb_frame->m = checked;
    draw();
}
