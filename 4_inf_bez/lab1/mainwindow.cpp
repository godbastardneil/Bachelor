#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pb = new picturebox(ui->cc);

    kl1 = k1/pb->get_g_length1();
    kl2 = k2/pb->get_g_length2();

    step = pb->width()/100.0;

    math();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    pb->move_start_point(value);

    m_math();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    pb->move_build(value);

    math();
}


void MainWindow::on_spinBox_1_valueChanged(double arg1)
{
    POK1 = arg1;

    math();
}


void MainWindow::on_spinBox_2_valueChanged(double arg1)
{
    POK2 = arg1;

    math();
}

void MainWindow::m_math()
{
    qDebug() << ((k1/pb->get_w_length1())*POK1*kl1) << ((k2/pb->get_w_length2())*POK2*kl2);
    ui->resultEdit_1->setText(QString::number((k1/pb->get_w_length1())*POK1*kl1));
    ui->resultEdit_2->setText(QString::number((k2/pb->get_w_length2())*POK2*kl2));
}

void MainWindow::math()
{
    ui->textBrowser->clear();
    for (int i=0; i<100; ++i) {
        double length1 = sqrt(pb->get_y()*pb->get_y() + (pb->get_w_x1()-i*step)*(pb->get_w_x1()-i*step));
        double length2 = sqrt(pb->get_y()*pb->get_y() + (pb->get_w_x2()-i*step)*(pb->get_w_x2()-i*step));
        ui->textBrowser->append(QString::number(i*5)+": "
                                + QString::number((k1/length1)*POK1*kl1)+", "
                                + QString::number((k2/length2)*POK2*kl2)+", ");
    }
    m_math();
}

