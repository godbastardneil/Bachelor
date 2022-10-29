#include "picturebox.h"

using namespace std;

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    m_Pixmap = QPixmap(parent->width(), parent->height());
    m_Pixmap.fill(Qt::white);
    draw_set();
    m_new = m_Pixmap;
}

inline int picturebox::get_x(double t) { return 3*int(24.8*(cos(t)+(cos(6.2*t)/6.2))); }

inline int picturebox::get_y(double t) { return 3*int(24.8*(sin(t)-(sin(6.2*t)/6.2))); }

void picturebox::draw_set()
{
    int w = m_Pixmap.width();
    int h = m_Pixmap.height();
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::lightGray); // рисование сетки
    for (int i=10; i<h; i+=10) { painter.drawLine(0, i, w, i); }

    for (int i=10; i<w; i+=10) { painter.drawLine(i, 0, i, h); }
}

void picturebox::paintit()
{
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);

    painter.translate(this->width()/2, this->height()/2);

    for (double t=0; t<10*pi; t += 0.001)
    {
        painter.drawEllipse(get_x(t), get_y(t), 2, 2);
        repaint();
    }
}

void picturebox::reset()
{
    m_Pixmap = m_new;
    repaint();
}

void picturebox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
}
