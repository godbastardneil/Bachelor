#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

extern QVector<Star> Stars;
QVector<Star> Stars;

static random_device rd;
static mt19937 mt(rd());
static uniform_int_distribution<int> range_coordinates;
static uniform_int_distribution<int> range_RGB(0, 255);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pb_frame = new PictureBox(ui->frame);
    pb_frame->resize(ui->frame->size());
    Rand();
    pb_frame->drowS();
    paintTimer = new QTimer(this);
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::Rand()
{
    Stars.resize(N);
    uniform_int_distribution<int> range_size(min, max);
    for (int i=0; i<N; i++)
    {
        Stars[i].x = range_coordinates(mt) % pb_frame->width();
        Stars[i].y = range_coordinates(mt) % pb_frame->height();
        Stars[i].color.setRgb(range_RGB(mt),range_RGB(mt),range_RGB(mt));
        Stars[i].size = range_size(mt);

        double step = 100 + range_coordinates(mt)%300;
        Stars[i].dx = ((pb_frame->width())/2 - Stars[i].x) / step;
        Stars[i].dy = ((pb_frame->height())/2 - Stars[i].y) / step;
    }
}

double MainWindow::newY_Coord(double x1, double y1, double x)
{
    int height = pb_frame->height();
    int width = pb_frame->width();
    double y = (y1 - height / 2) * (x - width / 2) / (x1 - width / 2) + height / 2;
    return y;
}

void MainWindow::convergence()
{
    int N = Stars.size();
    for (int j=0; j<speed; j++)
    {
        for (int i=0; i<N; i++)
        {
            if (Stars[i].x < (pb_frame->width() / 2))
            {
                double Tx = newY_Coord(Stars[i].x -= 1, Stars[i].y, Stars[i].x += 2);
                if (Tx > 0.005 || Tx < pb_frame->height())
                {
                    Stars[i].y = Tx;
                }
            }
            else
            {
                double Tx = newY_Coord(Stars[i].x += 1, Stars[i].y, Stars[i].x -= 2);
                if (Tx > 0.005 || Tx < pb_frame -> height())
                {
                    Stars[i].y = Tx;
                }
            }
        }
    }
    pb_frame->drowS();
    pb_frame->repaint();
}
void MainWindow::discrepancy()
{
    int N = Stars.size();

    for (int  j=0; j<speed; j++)
    {
        for (int i=0; i<N; i++)
        {
            if (Stars[i].x<pb_frame->width()) {
                Stars[i].x -= Stars[i].dx;
            }
            if (Stars[i].y<pb_frame->height()) {
                Stars[i].y -= Stars[i].dy;
            }
        }
    }
    pb_frame->drowS();
    pb_frame->repaint();
}

void MainWindow::on_Start_clicked()
{
    disconnect(paintTimer, SIGNAL(timeout()), this, nullptr);
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(convergence()));
    paintTimer->start(10);
}

void MainWindow::on_Stop_clicked()
{
    if (paintTimer->isActive()) paintTimer->stop();
    else paintTimer->start(10);
}

void MainWindow::on_Remove_clicked()
{
    disconnect(paintTimer, SIGNAL(timeout()), this, nullptr);
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(discrepancy()));
    paintTimer->start(10);
}

void MainWindow::on_Speed_valueChanged(int value) { speed = value; }


void MainWindow::on_Num_valueChanged(int arg1) { N = arg1; }

void MainWindow::on_Min_valueChanged(int arg1)
{
    min = arg1;
    if (ui->Max->value() < arg1) { ui->Max->setValue(arg1); }
    ui->Max->setMinimum(arg1);
}
void MainWindow::on_Max_valueChanged(int arg1) { max = arg1; }

void MainWindow::on_Line_toggled(bool checked)
{
    if (checked) {
        pb_frame->trail = true;
   } else { pb_frame->trail = false; }
}
void MainWindow::on_Ok_clicked()
{
    disconnect(paintTimer, SIGNAL(timeout()), this, nullptr);
    Rand();
    pb_frame->reset();
    pb_frame->drowS();
    pb_frame->repaint();
}
