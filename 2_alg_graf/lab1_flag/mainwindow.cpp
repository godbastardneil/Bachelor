#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::paintEvent(QPaintEvent *) {

    int x (40), y (40);
    int w (280), h (280);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::DashLine);
    for (int i=0; i<=360; i+=20) {
        painter.drawLine(0, i, 360, i);
        painter.drawLine(i, 0, i, 360);
    }
    painter.setPen(Qt::SolidLine);
    painter.setPen(QPen(Qt::black, 5));
    painter.drawEllipse(x, y, w, h);

    painter.setPen(QPen(Qt::red, 5));
    painter.drawRect(x, y, w, h);

    x += 40;
    y += 40;
    w -= 80;
    h -= 80;
    painter.setPen(QPen(Qt::blue, 5));
    painter.drawEllipse(x, y, w, h);

    x += 40;
    y += 40;
    w -= 80;
    h -= 80;
    painter.setPen(QPen(Qt::green, 5));
    painter.drawEllipse(x, y, w, h);

    x += 40;
    y += 40;
    w -= 80;
    h -= 80;
    painter.setPen(QPen(Qt::red, 5));
    painter.drawEllipse(x, y, w, h);
}


MainWindow::~MainWindow()
{
    delete ui;
}

