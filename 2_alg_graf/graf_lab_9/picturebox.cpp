#include "picturebox.h"

using namespace std;

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    m_Pixmap = QPixmap(parent->width(), parent->height());
    m_Pixmap.fill(Qt::white);
    m_new = m_Pixmap;

}
void picturebox::reset() {
    m_Pixmap = m_new;
    repaint();
}

int picturebox::f(double x, double z)
{
    if(i == 0)
    {
        return int((300 * cos(x * x + z * z)) / (x * x + z * z + 1));
    } else if (i == 1)
    {
        return int((300 * sin(x * x + z * z)) / (x * x + z * z + 1));
    } else if (i == 2)
    {
        return int(100*(z-sin(x)));
    } else { return int (100*z*sin(x)); }
}
void picturebox::doit()
{
    QPainter painter(&m_Pixmap);

    int h = this->height();
    int w = this->width();

    double DZ = 0.01;
    double RIGHTX = 6.75;
    double LEFTX = -6.75;
    double STEP1 = (h / (RIGHTX - LEFTX));
    double DX = (DZ * STEP1 / (sqrt(2)));
    double DY = (DZ * STEP1 / (sqrt(2)));

    QVector<int> Upper(w, h), Lower(w, 0);
    int k = 0;
    int y;
    int x1;

    QTimer time;
    for (double z = 1; z<2; z+=DZ)
    {
        for (double x = LEFTX; x<RIGHTX; x+=1/STEP1)
        {
            y = int(378 - (f(x, z) +  k * DY * 6.75));
            x1 = int(STEP1 * x + h/2 + k * DX * 6.75);

            if (y > Lower[x1])
            {
                Lower[x1] = y;
                painter.setPen(Qt::darkRed);
                painter.drawEllipse(x1, y, 3, 3);
            }

            if (y < Upper[x1])
            {
                Upper[x1] = y;
                painter.setPen(Qt::red);
                painter.drawEllipse(x1, y, 3, 3);
            }
        }
        ++k;
        time.start(25);
        while(time.remainingTime() != 0) {}
        repaint();
    }
}

void picturebox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
}
