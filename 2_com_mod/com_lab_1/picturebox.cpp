#include "picturebox.h"
#include "mainwindow.h"

using namespace std;

extern double v0, a;
static QString M;

PictureBox::PictureBox(QWidget *parent) : QFrame(parent)
{

}

void findMax (const QVector<double> &Y) {
    int n = Y.size();
    double maxy = 0;
    int x = 0;
    for (int i=0; i<n; i++) {
        if (Y[i] > maxy) {
            maxy = Y[x];
            x = i;
        }
    }
    if (maxy > 0) { M += " Максимальная высота - x: " + QString::number(x+1) + ", y: " + QString::number(maxy) + "\n Максимальное растояние - x: " + QString::number(n); }
}

void PictureBox::paintEvent(QPaintEvent *)
{
    QVector<double> Y;
    int x = 0;
    double g = 9.806;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::SolidLine);
    painter.setPen(QPen(Qt::green, 3));

    double h = height();
    if ((v0>0) && (a>0)) {
        do {
            x += 1;

            Y.push_back(h-(x*tan(a)-(g*x*x)/(2*v0*v0*cos(a)*cos(a))));

            painter.drawEllipse(x, static_cast<int>(Y[x-1]), 2, 2);
            Y[x-1] = h - Y[x-1];
        } while (Y[x-1]>0);
    }
    painter.end();
    findMax(Y);
    Y.erase(Y.begin(), Y.end());
    if (!M.isEmpty()) { QMessageBox::warning(this, "Coord", M); }
    M = "";
}
