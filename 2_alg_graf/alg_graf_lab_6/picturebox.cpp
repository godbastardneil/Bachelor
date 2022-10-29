#include "picturebox.h"

using namespace std;

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    w = parent->width(); h = parent->height();
    pic();
}

void picturebox::pic()
{
    m_Pixmap = QPixmap(name);
    m_Pixmap = m_Pixmap.scaled(w, h);
    m_new = m_Pixmap;
}

void picturebox::draw()
{
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor qc;
    double Dr, Dg, Db;
    double R, G, B;
    for (int i=0; i<height(); ++i)
    {
        for (int j=0; j<width(); ++j)
        {
            qc = m_Pixmap.toImage().pixel(i, j);
            Dr = abs(r - qc.red())/l;
            Dg = abs(g - qc.green())/l;
            Db = abs(b - qc.blue())/l;
            R = qc.red() + Dr;
            G = qc.green() + Dg;
            B = qc.blue() + Db;
            if (R>255) { R = 255; }
            if (G>255) { G = 255; }
            if (B>255) { B = 255; }
            painter.fillRect(i, j, 1, 1, QColor(int(R), int(G), int(B)));
        }
    }
}

void picturebox::reset() { m_Pixmap = m_new; }

void picturebox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
    reset();
}
