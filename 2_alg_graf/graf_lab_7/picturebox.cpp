#include "picturebox.h"

using namespace std;

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    m_Pixmap = QPixmap(parent->width(), parent->height());
    m_Pixmap.fill(Qt::white);
    draw_set();
    m_new = m_Pixmap;
    zatrav.push_back(QPoint(-10, -10));
}

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

void picturebox::draw_line(QPoint f, QPoint s, QPainter &painter, const QColor qc, bool w)
{
    int dx = (f.rx()-s.rx());
    int dy = (f.ry()-s.ry());
    int signX;
    int signY;
    if (dx < 0)
    {
        signX = 10;
        dx = -dx;
    } else { signX = -10; }
    if (dy < 0)
    {
        signY = 10;
        dy = -dy;
    } else { signY = -10; }

    QVector<QPoint> qvqp;

    int e = 0;

    int y = f.ry();
    int x = f.rx();
    painter.fillRect(x, y, 10, 10, qc);
    qvqp.push_back(f);
    if (dx < dy)
    {
        for (int i=0; i<dy; i+=10)
        {
            y += signY;
            e += dx;
            if (2*e >= dy)
            {
                x += signX;
                e -= dy;
            }
            painter.fillRect(x, y, 10, 10, qc);
            qvqp.push_back(QPoint(x, y));
        }
    } else {
        for (int i=0; i<dx; i+=10)
        {
            x += signX;
            e += dy;
            if (2*e >= dx)
            {
                y += signY;
                e -= dx;
            }
            painter.fillRect(x, y, 10, 10, qc);
            qvqp.push_back(QPoint(x, y));
        }
    }
    if (w) { all_p.append(qvqp); }
}

bool checker (const QPoint f, const QPoint s)
{
    if (f.y() == s.y())
    {
        return f.x() <= s.x();
    } else { return f.y() < s.y(); }
}

void picturebox::postroch_zal()
{
    sort(all_p.begin(), all_p.end(), checker);

    int n = all_p.size();

    QTimer time;
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i=0; i<n-1; ++i)
    {
        while (i<n-1 && all_p[i].y() == all_p[i+1].y())
        {
            int y = all_p[i].y();
            int x1 = all_p[i].x();
            int x2 = all_p[i+1].x();
            if (abs(x1-x2) > 10)
            {
                draw_line(QPoint(x1+10, y), QPoint(x2-10, y), painter, Qt::green, 0);
            }
            ++i;
        }
        time.start(100);
        while(time.remainingTime() != 0) {}
        repaint();
    }
}
void picturebox::zatravca()
{
    QTimer time;
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    while (!zatrav.empty())
    {
        QPoint qp = zatrav[zatrav.size()-1];
        zatrav.pop_back();
        QColor c_qp = m_Pixmap.toImage().pixel(qp.rx()+5, qp.ry()+5);
        if (c_qp == Qt::white)
        {
            painter.fillRect(qp.rx(), qp.ry(), 10, 10, Qt::green);
            time.start(25);
            while(time.remainingTime() != 0) {}
            repaint();
        }

        QPoint d(qp.rx(), qp.ry()-10);  QColor c_d = m_Pixmap.toImage().pixel(d.rx()+5, d.ry()+5);
        QPoint u(qp.rx(), qp.ry()+10);  QColor c_u = m_Pixmap.toImage().pixel(u.rx()+5, u.ry()+5);
        QPoint l(qp.rx()-10, qp.ry());  QColor c_l = m_Pixmap.toImage().pixel(l.rx()+5, l.ry()+5);
        QPoint r(qp.rx()+10, qp.ry());  QColor c_r = m_Pixmap.toImage().pixel(r.rx()+5, r.ry()+5);

        if (c_d == Qt::white) { zatrav.push_back(d); }
        if (c_u == Qt::white) { zatrav.push_back(u); }
        if (c_l == Qt::white) {zatrav.push_back(l); }
        if (c_r == Qt::white) { zatrav.push_back(r); }
    }
}

void picturebox::check_ckan(QPoint qp, int x_r)
{
    QColor qc = m_Pixmap.toImage().pixel(qp.x()+5, qp.y()+5);
    while (qp.x() <= x_r)
    {
        bool flag = false;
        while (qp.x() < x_r && qc != Qt::black && qc != Qt::green)
        {
            if(!flag) { flag = true; }
            qp.rx() += 10;
            qc = m_Pixmap.toImage().pixel(qp.x()+5, qp.y()+5);
        }
        if (flag)
        {
            if (qp.x() == x_r && qc != Qt::black && qc != Qt::green)
            {
               zatrav.push_back(qp);
            } else { zatrav.push_back(QPoint(qp.x()-10, qp.y())); }
            flag = false;
        }
        int x_vhod = qp.x();
        while (qp.rx() < x_r && (qc == Qt::black || qc == Qt::green))
        {
            qp.rx() += 10;
            qc = m_Pixmap.toImage().pixel(qp.x()+5, qp.y()+5);
        }
        if (qp.x() == x_vhod) { qp.rx() += 10; }
    }
}

void picturebox::postroch_ckan()
{
    QTimer time;
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor qc;
    while (!zatrav.empty())
    {
        QPoint qp = zatrav[zatrav.size()-1];
        painter.fillRect(qp.x(), qp.y(), 10, 10, Qt::green);
        zatrav.pop_back();

        int tmp_x = qp.x();
        qp.rx() += 10;
        qc = m_Pixmap.toImage().pixel(qp.x()+5, qp.y()+5);
        while (qp.x() < this->width() && qc != Qt::black)
        {
            painter.fillRect(qp.x(), qp.y(), 10, 10, Qt::green);
            qp.rx() += 10;
            qc = m_Pixmap.toImage().pixel(qp.x()+5, qp.y()+5);
        }

        int x_r = qp.x()-10;
        qp.rx() = tmp_x-10;
        qc = m_Pixmap.toImage().pixel(qp.x()+5, qp.y()+5);
        while (qp.x() > 0 && qc != Qt::black)
        {
            painter.fillRect(qp.x(), qp.y(), 10, 10, Qt::green);
            qp.rx() -= 10;
            qc = m_Pixmap.toImage().pixel(qp.x()+5, qp.y()+5);
        }

        int x_l = qp.x()+10;
        qp.rx() = x_l;

        qp.ry() -= 10;
        check_ckan(qp, x_r);
        qp.ry() += 20;
        check_ckan(qp, x_r);

        repaint();
        time.start(100);
        while(time.remainingTime() != 0) {}
    }
}

void picturebox::reset() {
    m_Pixmap = m_new;
    one.clear(); two.clear();
    who = 0;
    all_p.clear();
    zatrav.clear();
    zatrav.push_back(QPoint(-10, -10));
    repaint();
}

void picturebox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
}


void picturebox::mousePressEvent(QMouseEvent *event)
{
    QPoint tmp = event->pos();
    tmp.rx() -= tmp.rx()%10;
    tmp.ry() -= tmp.ry()%10;
    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    if (event->buttons() == Qt::LeftButton)
    {

        if (who == 0)
        {
            if (one.contains(tmp))
            {
                who = 1;
                draw_line(one[one.size()-1], one[0], painter, Qt::black, 1);
            } else { one.push_back(tmp); }

            if (one.size()>1) { draw_line(one[(one.size()-2)], one[one.size()-1], painter, Qt::black, 1); }

        } else if (who == 1)
        {
            if (two.contains(tmp))
            {
                who = 2;
                draw_line(two[two.size()-1], two[0], painter, Qt::black, 1);
            }  else { two.push_back(tmp); }

            if (two.size()>1) { draw_line(two[two.size()-2], two[two.size()-1], painter, Qt::black, 1); }
        }
        repaint();
    } else if (event->buttons() == Qt::RightButton)
    {
        if (!all_p.contains(tmp))
        {
            if (tmp != zatrav[0])
            {
                if (zatrav[0] != QPoint(-10, -10)) { painter.fillRect(zatrav[0].rx()+1, zatrav[0].ry()+1, 8, 8, Qt::white); }
                painter.fillRect(tmp.rx()+1, tmp.ry()+1, 8, 8, Qt::blue);
                zatrav[0] = (tmp);
            } else
            {
                painter.fillRect(zatrav[0].rx()+1, zatrav[0].ry()+1, 8, 8, Qt::white);
                zatrav[0] = QPoint(-10, -10);
            }
            repaint();
        }
    }
}
