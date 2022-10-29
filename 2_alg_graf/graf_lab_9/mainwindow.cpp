#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb = new picturebox(ui->frame);
    pb->resize(ui->frame->size());

    ui->comboBox->insertItem(0, "300*cos(x*x+z*z)/(x*x+z*z+1)");
    ui->comboBox->insertItem(1, "300*sin(x*x+z*z)/(x*x+z*z+1)");
    ui->comboBox->insertItem(2, "100*(z-sin(x))");
    ui->comboBox->insertItem(3, "100*z*sin(x)");
}
MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_reset_clicked() { pb->reset(); }

void MainWindow::on_Ok_clicked() { pb->doit(); }

void MainWindow::on_comboBox_activated(int index) { pb->set_i(index); }
