#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb_frame = new picturebox(ui->frame);
    pb_frame->resize(ui->frame->size());

    p = new picturebox(ui->frame_2);
    p->resize(ui->frame->size());
    for (int i=1; i<4; ++i) {
        ui->picture->addItem("№" + QString::number(i));
    }
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_livel_valueChanged(int value) { pb_frame->set_level(value/10.0); }

void MainWindow::on_Ok_clicked()
{
    pb_frame->draw();
    pb_frame->repaint();
}

void MainWindow::on_reset_clicked()
{
    pb_frame->reset();
    pb_frame->repaint();
}

void MainWindow::on_picture_activated(int index)
{
    if (index == 0) {
        pb_frame->set_name(":/windows.jpg");
        p->set_name(":/windows.jpg");
    } else if (index == 1) {
        pb_frame->set_name(":/city.jpg");
        p->set_name(":/city.jpg");
    } else { pb_frame->set_name(":/all.png"); p->set_name(":/all.png"); }
    pb_frame->pic();
    pb_frame->repaint();
    p->pic();
    p->repaint();
}
