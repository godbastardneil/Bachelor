#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QFrame>
#include <QPainter>
#include <QString>
#include <QVector>
#include <QPixmap>
#include <QThread>

#include "algor.h"

enum mod
{
    mainres = 1,
    mainoper = 2,
    resmain = 3,
    resoper = 4,
    opermain = 5,
    operres = 6
};


class picturebox : public QFrame
{
    Q_OBJECT

public:
    explicit picturebox(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent*);

    QString get_result()
    {
        prev_i = 0;
        clear();
        in_qs.remove(' ');
        algor::alg(in_qs, result, oper);
        in_qs += "  ";
        size = in_qs.size();
        word_size = this->width()/result[result.size()-1].size();
        return result[result.size()-1];
    }

    void set_str (const QString &qs) { in_qs = qs; size = qs.size(); }
    QString get_str () { return in_qs; }
    int get_str_size () { return size; }

    void show_step(const uint8_t &i);

private:
    QPixmap m_Pixmap;
    QPixmap m_new;

    int word_size;
    uint8_t prev_i;

    QString in_qs; // входная строка для демонстрации
    QVector<QString> result; // выходная строка для демонстрации
    QVector<QString> oper; // выходная строка для демонстрации
    uint size = 0;

    void clear() { result.clear(); oper.clear(); }

    void do_main_str(const int &i, QPainter &qp);
    void do_oper_str(const int &i, QPainter &qp);
    void do_res_str(const int &i, QPainter &qp);

    QString what_anim(const QString &str1, const QString &str2);
    void do_anim(const QString &qs, const uint8_t &mod, QPainter &qp);

    void forvard(const int &i, QPainter &qp);
    void back(const int &i, QPainter &qp);
};

#endif // PICTUREBOX_H
