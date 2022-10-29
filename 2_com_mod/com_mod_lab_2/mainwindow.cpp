#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_doubleSpinBox_0_valueChanged(double arg1) { T[0] = arg1; }

void MainWindow::on_doubleSpinBox_5_valueChanged(double arg1) { T[5] = arg1; }

void MainWindow::on_unit_tem_valueChanged(double arg1)
{
    ui->doubleSpinBox_1->setValue(arg1);
    ui->doubleSpinBox_2->setValue(arg1);
    ui->doubleSpinBox_3->setValue(arg1);
    ui->doubleSpinBox_4->setValue(arg1);
    for (int i=1; i<5; i++) {  T[i] = arg1; }
}

void MainWindow::on_time_valueChanged(int arg1) { Time = arg1; }

void MainWindow::start()
{
    ui->doubleSpinBox_0->setValue(T[0]);
    ui->doubleSpinBox_1->setValue(T[1]);
    ui->doubleSpinBox_2->setValue(T[2]);
    ui->doubleSpinBox_3->setValue(T[3]);
    ui->doubleSpinBox_4->setValue(T[4]);
    ui->doubleSpinBox_5->setValue(T[5]);
    double t_0 = T[0];
    for (int j=1; j<5; j++) {
        double t_i = T[j];
        T[j] = (t_0 + T[j + 1]) / 2;
        t_0 = t_i;
    }
    if(Time != 0) { Time--; QTimer::singleShot(1000, this, SLOT(start())); } // повторный вызов перещет
}

void MainWindow::on_Ok_clicked() { start(); } // начало процесса

