#include "picturebox.h"

using namespace std;

picturebox::picturebox(QWidget *parent) : QGraphicsView(parent)
{
    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    scene = new QGraphicsScene(0, 0, parent->width()-60, parent->height()-60, parent);   // Инициализируем сцену для отрисовки
    this->setScene(scene);       // Устанавливаем сцену в виджет


    magnit = new QGraphicsPixmapItem(fname + "magnit.png");
    magnit->setOffset((3*scene->width()/4)-(magnit->pixmap().width()/2)-58, 0);

    main_im1 = new QGraphicsPixmapItem(fname + "main_im.png");
    main_im1->setOffset(scene->width()/4, 150);
    cat1 = scene->height()/2 - main_im1->pixmap().height()/6;
    cat2 = cat1 + main_im1->pixmap().height()/3;

    main_im2 = new QGraphicsPixmapItem(fname + "gal_only.png");
    main_im2->setOffset(scene->width()/4, 150);

    ram = new QGraphicsPixmapItem(fname + "rama.png");
    ram->setOffset((3*scene->width()/4)-(ram->pixmap().width()/2)-100, (scene->height()/2)-(ram->pixmap().height()/2)+55);
    ram->setTransformOriginPoint(((3*scene->width()/4)-100), ((scene->height()/2)+55));

    pole = new QGraphicsPixmapItem(fname + "magpole.png");
    pole->setOffset((3*scene->width()/4)-(pole->pixmap().width()/2)-100, (scene->height()/2)-(pole->pixmap().height()/2)+55);


    strelca = new QGraphicsPixmapItem(fname + "strelca.png");
    strelca->setOffset(50+scene->width()/4, 175);
    strelca->setTransformOriginPoint(58+scene->width()/4, 235);


    rule1 = new QGraphicsPixmapItem(fname + "rule1.png");
    rule1->setOffset(scene->width()-rule1->pixmap().width(), (scene->height()-rule1->pixmap().height())/2);
    rule2 = new QGraphicsPixmapItem(fname + "rule2.png");
    rule2->setOffset(scene->width()-rule1->pixmap().width()-rule2->pixmap().width(), (scene->height()-rule2->pixmap().height())/2);

    scene->addItem(magnit);     // Добавляем движущийся объект в сцену
    scene->addItem(main_im1);   // Добавляем гальвонометр в сцену

    scene->addItem(main_im2);   // Добавляем гальвонометр в сцену
    scene->addItem(ram);        // Добавляем движущийся объект в сцену
    scene->addItem(pole);       // Добавляем поле в сцену

    scene->addItem(strelca);    // Добавляем стрелка в сцену

    scene->addItem(rule1);      // Добавляем стрелка в сцену
    scene->addItem(rule2);      // Добавляем стрелка в сцену

    set_scene(0);

    qt = new QTimer(this);
    qt->setInterval(500);
    connect(qt, SIGNAL(timeout()), this, SLOT(reset()));
    qt->start();
}

void picturebox::set_scene(const int &s)
{
    sc = s;
    if (s == 0)
    {
        ram->hide();
        main_im2->hide();
        pole->hide();
        rule2->hide();

        magnit->show();
        main_im1->show();
    } else if (s == 1)
    {
        magnit->hide();
        main_im1->hide();

        ram->show();
        main_im2->show();
        pole->show();
        rule2->show();
    }
    rule1->show();
}

void picturebox::galvonometr()
{
    t1 = clock();
    if (i > 0)
    {
        I = dB*dy*S*a/((t1 - t0)*R);
        strelca->setRotation(180*std::asin(I/strelca->pixmap().width())/3.14);
    }
    t0 = t1;
    ++i;
}

void picturebox::mousePressEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    mouse_press = event->y();
}
void picturebox::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    rule1->hide();
    rule2->hide();
    Q_UNUSED(event);
}

void picturebox::mouseMoveEvent(QMouseEvent *event)
{
    if (sc == 0)
    {
        old_pos = magnit->y();
        magnit->setY(event->y() + magnit->y() - mouse_press);
        mouse_press = event->y();

        dy = magnit->y() - old_pos;

        obj_h = magnit->y() + magnit->pixmap().height();

        if (magnit->y() > cat1 && magnit->y() < cat2)
        {
            galvonometr();
        } else if (magnit->y() < cat1 && obj_h > cat2)
        {
            galvonometr();
        } else if (obj_h > cat1 && obj_h < cat2)
        {
            galvonometr();
        } else { i = 0; }
    } else
    {
        old_pos = mouse_press;
        mouse_press = event->y();
        dy = old_pos-mouse_press;
        a = (ram->pixmap().width()/2)/std::sqrt(dy*dy + ram->pixmap().width()*ram->pixmap().width()/4);
        if (dy < 0)
        {
            dy = -1;
        } else if (dy > 0) { dy = 1; }
        ram->setRotation(ram->rotation()+180*dy*std::acos(a)/3.14);
        if (ram->rotation() != 0)
        {
            a *= 10;
            galvonometr();
        } else { i = 0; }
    }
}

void picturebox::reset() { strelca->setRotation(0); }
