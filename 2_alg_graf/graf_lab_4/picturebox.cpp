#include "picturebox.h"

using namespace std;

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    m_Pixmap = QPixmap(parent->width(), parent->height());
    m_Pixmap.fill(Qt::white);
    m_new = QPixmap(m_Pixmap.size());
    m_new.fill(Qt::white);
}

bool picturebox::chechtr() { return (b.rx()-a.rx())*(c.ry()-a.ry()) - (b.ry()-a.ry())*(c.rx()-a.rx()); }

void picturebox::paint()
{
    QPainter painter(&m_Pixmap);
    painter.drawLine(0, 0, 800, 800);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::green);
    painter.drawEllipse(t, 2, 2);

    int A_x = int(((a.rx()-t.rx())*cos(a0)-(a.ry()-t.ry())*sin(a0)+t.rx())*k);
    int A_y = int(((a.rx()-t.rx())*sin(a0)+(a.ry()-t.ry())*cos(a0)+t.ry())*k);

    int B_x = int(((b.rx()-t.rx())*cos(a0)-(b.ry()-t.ry())*sin(a0)+t.rx())*k);
    int B_y = int(((b.rx()-t.rx())*sin(a0)+(b.ry()-t.ry())*cos(a0)+t.ry())*k);

    int C_x = int(((c.rx()-t.rx())*cos(a0)-(c.ry()-t.ry())*sin(a0)+t.rx())*k);
    int C_y = int(((c.rx()-t.rx())*sin(a0)+(c.ry()-t.ry())*cos(a0)+t.ry())*k);
    painter.setPen(Qt::red);
    if (!m) {
        painter.drawLine(A_x, A_y, C_x, C_y);
        painter.drawLine(A_x, A_y, B_x, B_y);
        painter.drawLine(C_x, C_y, B_x, B_y);
    } else {
        painter.drawLine(A_y, A_x, B_y, B_x);
        painter.drawLine(A_y, A_x, C_y, C_x);
        painter.drawLine(C_y, C_x, B_y, B_x);
    }
}

void picturebox::reset() { m_Pixmap = m_new; }

void picturebox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
    reset();
}
