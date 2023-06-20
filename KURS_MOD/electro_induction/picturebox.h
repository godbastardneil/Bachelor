#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>

#include <ctime>
#include <cmath>

class picturebox : public QGraphicsView
{
    Q_OBJECT

private:
    int wi, h;
    QString fname = "files/images/";

    int sc = 0;

    QGraphicsScene *scene;     // Объявляем сцену для отрисовки


    QGraphicsPixmapItem *magnit;   // Объявляем магнит
    QGraphicsPixmapItem *main_im1;   // Объявляем гальвонометр для задания №1

    QGraphicsPixmapItem *main_im2;   // Объявляем гальвонометр для задания №2
    QGraphicsPixmapItem *ram;   // Объявляем рамка
    QGraphicsPixmapItem *pole;   // Объявляем магнитное поле

    QGraphicsPixmapItem *strelca;   // стрелка
    QGraphicsPixmapItem *rule1;   // правила 1
    QGraphicsPixmapItem *rule2;   // правила 2

    int old_pos; // старая позиция объекта
    int mouse_press; // где было нажатой мышкой

    double dy; // насколько изменилось положение объекта

    int cat1; // начало катушки
    int cat2; // конец катушки
    int obj_h; // размер объекта

    // время движения объекта
    clock_t t0;
    clock_t t1;
    int i = 0;

    double dB = 0.1; // магнитная индукция
    int S = 80;
    double R = 1.68;
    double I;
    double a = 1; // косинус

    QTimer *qt;

    void galvonometr();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private slots:
    void reset();

public:
    explicit picturebox(QWidget *parent = nullptr);

    void set_scene(const int &s);

    void set_B(const double &db) { dB = db; }
    int get_B() { return dB; }

    void set_R(const double &r) { R = r; }
    int get_R() { return R; }

};
#endif // PICTUREBOX_H

