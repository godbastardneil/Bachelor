#include "picturebox.h"

using namespace std;

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    zero.setX(parent->width()/2); zero.setY(parent->height()/2);
    m_Pixmap = QPixmap(parent->width(), parent->height());
    m_Pixmap.fill(Qt::white);
    m_new = QPixmap(m_Pixmap.size());
    m_new.fill(Qt::white);
}


void picturebox::paint_line()
{
    int ry = -b.ry();

    const int dx = abs(b.rx());
    const int dy = abs(ry);
    const int signX = 0 < b.rx() ? 1 : -1;
    const int signY =0 < ry ? 1 : -1;

    int e = 0;
    int x = -10;

    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(zero.rx(), zero.ry());

    for (int y=0; y<ry*10; y+=signY*10) {
        painter.fillRect(x, y, 10, 10, Qt::green);
        e += dx;
        if (2*e >= dy) {
            x += signX*10;
            e -= dy;
        }
    }
    painter.setPen(Qt::black);
    painter.drawLine(0, 0, b.rx()*10, ry*10); // рисование обычной прямой
}

void picturebox::paint_cyrcle()
{
    int x = 0, y = o_R*10;

    int r2 = o_R*o_R;
    int dst= 4*r2;
    double dxt= double(o_R)/1.414213562373;
    long t = 0;
    long s = -4*r2*o_R;
    long e = (-s/2) - 3*r2;
    int ca = -6*r2;
    int cd = -10*r2;
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(zero.rx(), zero.ry());

    for (int indx=1; indx<=dxt; indx++)
    {
        x += 10;
        if(e>=0) {
            e += t+ca;
        } else {
            y -= 10;
            e += t-s+cd;
            s += dst;
        }
        t -= dst;
        painter.fillRect(y, -x, 10, 10, Qt::green);
    }
    painter.setPen(Qt::black);
    painter.drawEllipse(QPointF(0, 0), o_R*10, o_R*10); // рисование обычного круга
}

void picturebox::paint_ellipse()
{
    int x = 0, y = e_r2*10;

    long a2 = e_r1*e_r1;
    long b2 = e_r2*e_r2;
    long dds = 4*a2;
    long ddt = 4*b2;
    int dxt = int(a2/sqrt(a2+b2));
    long t = 0;
    long s = -4*a2*abs(e_r2);
    long e = (-s/2)-2*b2-a2;
    long ca = -6*b2;
    long cd = ca-4*a2;

    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(zero.rx(), zero.ry());

    for (int indx=1; indx<=dxt; indx++)
    {
        x += 10;
        if (e >= 0) {
            e += t+ca;
        } else {
            y -= 10;
            e += t-s+cd;
            s += dds;
        }
        t -= ddt;
        painter.fillRect(-x, -y, 10, 10, Qt::green);
    }
    dxt = abs(y)/10;
    e -= ((t/2)+(s/2)+b2+a2);
    ca = -6*a2;
    cd = ca - 4*b2;
    for (int indx=1; indx<=dxt-1; indx++)
    {
        y -= 10;
        if (e <= 0) {
            e += -s-ca;
        } else {
            x += 10;
            e += t-s+cd;
            t -= ddt;
        }
        s += dds;
        painter.fillRect(-x, -y, 10, 10, Qt::green);
    }
    painter.setPen(Qt::black);
    painter.drawEllipse(QPointF(0, 0), e_r1*10, e_r2*10); // рисование обычного элипса
}

void picturebox::reset() { m_Pixmap = m_new; } // обновление экрана

void picturebox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::lightGray); // рисование сетки
    for (int i=10; i<width(); i+=10) {
        painter.drawLine(i, 0, i, height());
        painter.drawLine(0, i, width(), i);
    }


    // рисование прямых, делящих октангов
    painter.setPen(Qt::red);
    painter.drawLine(zero.rx(), 0, zero.rx(), height());
    painter.drawLine(0, zero.ry(), width(), zero.ry());
    painter.drawLine(0, 0, width(), height());
    painter.drawLine(width(), 0, 0, height());

    reset();
}
