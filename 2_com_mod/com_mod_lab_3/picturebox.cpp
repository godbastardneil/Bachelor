#include "picturebox.h"

using namespace std;

static random_device rd;
static mt19937 mt(rd());
static uniform_int_distribution<int> range(1, 4);

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    m_Pixmap = QPixmap(parent->width(), parent->height());
    m_Pixmap.fill(Qt::white);
    m_new = m_Pixmap;
}

QPoint picturebox::work()
{
    QPoint end = {0, 0}; // начало пути -> конечный путь
    int chance  = range(mt);
    for (int i=0; i<steps; ++i)
    {
        chance = (chance + range(mt))%4;

        if (chance == 1) {
            end.rx() -= int(l);
        } else if (chance == 2) {
            end.rx() += int(l);
        } else if (chance  == 3) {
            end.ry() -= int(l);
        } else { end.ry() += int(l); }
    }
    return end;
}

void picturebox::paint()
{
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::lightGray);
    for (int i = 10; i < height(); i += 10)
    {
        painter.drawLine(0,i,width(),i);
        painter.drawLine(i,0,i,height());
    }
    painter.translate(width()/2, height()/2); // новый центр

    painter.setBrush(Qt::red);
    for (int i=0; i<kol; ++i) { painter.drawEllipse(work(),3,3); }

    painter.setBrush(Qt::blue);
    painter.drawEllipse(-3,-3,6,6); // рисусую центр
}

void picturebox::reset() { m_Pixmap = m_new; }

void picturebox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
    reset();
}
