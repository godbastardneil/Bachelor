#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb_frame = new picturebox(ui->frame);
    pb_frame->resize(ui->frame->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Ok_clicked()
{
    pb_frame->trigger = true;
    pb_frame->repaint();
}
