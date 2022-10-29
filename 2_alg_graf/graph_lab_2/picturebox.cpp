#include "picturebox.h"

using namespace std;

extern QVector<Star> Stars;

PictureBox::PictureBox(QWidget *parent) : QFrame(parent)
{
    m_Pixmap = QPixmap(parent->width(), parent->height());
    m_new = QPixmap(m_Pixmap.size());
}

void PictureBox::drowS()
{
    QPaintDevice* pointer = &m_Pixmap;

    QPainter painter(pointer);

    int N = Stars.size();
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i = 0; i < N; i++)
    {
        painter.setPen(Stars[i].color);
        painter.setBrush(Stars[i].color);
        painter.drawEllipse(static_cast<int>(Stars[i].x), static_cast<int>(Stars[i].y), Stars[i].size, Stars[i].size);
    }
}

void PictureBox::reset()
{
    m_Pixmap = m_new;
}

void PictureBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
    if (!trail) {
        reset();
    }
}
