#include "picturebox.h"

picturebox::picturebox(QWidget *parent) : QFrame(parent)
{
    resize(760, 440);
    m_new = QPixmap(this->width(), this->height());
    m_new.fill(Qt::white);
    m_Pixmap = m_new;
}

void picturebox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(1,1,m_Pixmap);
}


void picturebox::do_main_str(const int &i, QPainter &qp)
{
    qp.setBrush(Qt::white);
    qp.drawRect(0, 0, this->width(), 30);
    qp.setBrush(Qt::blue);
    for (uint j=0; j<size-i; ++j)
    {
        if (j < size-i-1) { qp.drawRect(j*word_size, 0, word_size, 30); }
        qp.drawText(word_size*(j+0.5), 20, QString(in_qs[j+i]));
    }
}
void picturebox::do_oper_str(const int &i, QPainter &qp)
{
    int w = (this->width()-word_size)/2;
    int h = (this->height()-30)/2;
    qp.setBrush(Qt::white);
    qp.drawRect(w, h, (this->width()+word_size)/2, 30);
    qp.setBrush(Qt::black);
    for (int j=0; j<oper[i].size(); ++j)
    {
        qp.drawRect(w+j*word_size, h, word_size, 30);
        qp.drawText(w+word_size*(j+0.5), h+20, QString(oper[i][j]));
    }
}
void picturebox::do_res_str(const int &i, QPainter &qp)
{
    int h = this->height()-30;
    qp.setBrush(Qt::white);
    qp.drawRect(0, h, this->width(), 30);
    qp.setBrush(Qt::red);
    for (int j=0; j<result[i].size(); ++j)
    {
        qp.drawRect(j*word_size, h, word_size, 30);
        qp.drawText(word_size*(j+0.5), h+20, QString(result[i][j]));
    }
}


QString picturebox::what_anim(const QString &str1, const QString &str2)
{
    QString anim;
    int i = str1.lastIndexOf(str2[0]);
    if (i != -1)
    {
        anim += str2[0];
        i += 2;
        for (int j=1; i < str1.size() && j < str2.size() && str1[i] == str2[j]; ++i, ++j)
        {
            anim += str2[j];
            ++i;
            if (i < str1.size() && str1[i] != ' ') { --i; }
        }
    }
    return anim;
}
void picturebox::do_anim(const QString &qs, const uint8_t &mod, QPainter &qp)
{
    m_new = m_Pixmap;
    qp.setBrush(Qt::lightGray);
    if (qs.size() > 0)
    {
        switch (mod)
        {
        case mainres: // main -> res
            for (int w = 0, h = 0; h < this->height()-30; w += result[prev_i].size()*word_size/20, h += (this->height()-30)/20)
            {
                    qp.drawRect(w, h, word_size, 30);
                    qp.drawText(w+word_size/2, h+20, qs);
                repaint();
                QThread::msleep(100);
                qp.drawPixmap(0, 0, m_new);
            }
            break;
        case mainoper: // main -> oper
            for (int w = 0, h = 0; w < (this->width()-word_size)/2; w += (this->width()-word_size)/40, h += (this->height()-30)/40)
            {
                    qp.drawRect(w, h, word_size, 30);
                    qp.drawText(w+word_size/2, h+20, qs);
                repaint();
                QThread::msleep(100);
                qp.drawPixmap(0, 0, m_new);
            }
            break;
        case resmain: // res -> main
            for (int w = word_size*(result[prev_i].size()-qs.size()), h = this->height()-30; h > 0; w -= result[prev_i].size()*word_size/20, h -= this->height()/20)
            {
                    qp.drawRect(w, h, word_size, 30);
                    qp.drawText(w+word_size/2, h+20, qs);
                repaint();
                QThread::msleep(100);
                qp.drawPixmap(0, 0, m_new);
            }
            break;
        case resoper: // res -> oper
            for (int w = word_size*(result[prev_i].size()-qs.size()), h = this->height()-30; h  > (this->height()-30)/2; w += (((this->width()-word_size)/2) - result[prev_i].size()*word_size)/20, h -= (this->height()-30)/40)
            {
                for (int j=0; j<qs.size(); ++j)
                {
                    qp.drawRect(w+j*word_size, h, word_size, 30);
                    qp.drawText(w+word_size*(j+0.5), h+20, qs[j]);
                }
                repaint();
                QThread::msleep(100);
                qp.drawPixmap(0, 0, m_new);
            }
            break;
        case opermain: // oper -> main
            for (int w = (this->width()-word_size)/2, h = (this->height()-30)/2; h > 0; w -= (this->width()-word_size)/40, h -= (this->height()-30)/40)
            {
                    qp.drawRect(w, h, word_size, 30);
                    qp.drawText(w+word_size/2, h+20, qs);
                repaint();
                QThread::msleep(100);
                qp.drawPixmap(0, 0, m_new);
            }
            break;
        case operres: // oper -> res
            for (int w = (this->width()-word_size)/2, h = (this->height()-30)/2; h < this->height()-30; w += (result[prev_i].size()*word_size-(this->width()-word_size)/2)/20, h += (this->height()-30)/40)
            {
                for (int j=0; j<qs.size(); ++j)
                {
                    qp.drawRect(w+j*word_size, h, word_size, 30);
                    qp.drawText(w+word_size*(j+0.5), h+20, qs[j]);
                }
                repaint();
                QThread::msleep(100);
                qp.drawPixmap(0, 0, m_new);
            }
            break;
        }
    }
}


void picturebox::forvard(const int &i, QPainter &qp)
{
    do_main_str(i, qp);
    if (result[i].size() > 0 && in_qs[prev_i] == result[i][result[i].size()-1])
    {
        do_anim(QString(in_qs[prev_i]), mainres, qp);

    } else if (oper[i].size() > 0 && in_qs[prev_i] == oper[i][0]) { do_anim(QString(in_qs[prev_i]), mainoper, qp); }
    do_oper_str(i, qp);
    if (oper[prev_i].size() > 0) { do_anim(what_anim(result[i], oper[prev_i]), operres, qp); }
    do_res_str(i, qp);
}
void picturebox::back(const int &i, QPainter &qp)
{
    do_res_str(i, qp);
    if (result[prev_i].size() > 0 && oper[i].size() > 0) { do_anim(what_anim(result[prev_i], oper[i]), resoper, qp); }
    do_oper_str(i, qp);
    if (result[prev_i].size() > 0 && in_qs[i] == result[prev_i][result[prev_i].size()-1])
    {
        do_anim(QString(in_qs[i]), resmain, qp);

    } else if (oper[prev_i].size() > 0 && in_qs[i] == oper[prev_i][0]) { do_anim(QString(in_qs[i]), opermain, qp); }

    do_main_str(i, qp);
}


void picturebox::show_step(const uint8_t &i)
{
    QPainter qp(&m_Pixmap);
    qp.setPen(Qt::white);
    if (i < prev_i)
    {
        back(i, qp);
    } else { forvard(i, qp); }
    repaint();
    prev_i = i;
}
