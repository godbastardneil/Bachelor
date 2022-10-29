#include "picturebox.h"


picturebox::picturebox(QWidget *parent) : QGraphicsView(parent)
{
    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);             // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);               // Отключим скроллбар по вертикали


    /* Также зададим минимальные размеры виджета */
    this->setMinimumHeight(parent->height());
    this->setMinimumWidth(parent->width());

    m_Pixmap = QPixmap(100, 100);
    m_Pixmap.fill(Qt::green);
    draw_set();

    scene = new QGraphicsScene();   // Инициализируем сцену для отрисовки
    this->setScene(scene);          // Устанавливаем сцену в виджет
    scene->setSceneRect(0, 0, parent->height(), parent->width());


    item = new QGraphicsPixmapItem(m_Pixmap); // Инициализируем вторую группу элементов
    scene->addItem(item);            //
    item->setPos(pix_x, y);

    line1 = new QGraphicsLineItem(p_x, 0, mx1, y); // Инициализируем вторую группу элементов
    line2 = new QGraphicsLineItem(p_x, 0, mx2, y); // Инициализируем вторую группу элементов

    scene->addItem(line1);            //
    scene->addItem(line2);            //
}

void picturebox::draw_set()
{
    window[0] = QRect(w_x1, 0, size, size);
    window[1] = QRect(w_x2, 0, size, size);
         goal = QRect(0, g_y, size, size);


    QPainter painter(&m_Pixmap);

    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(window[0]);
    painter.fillRect(window[0], painter.brush());

    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(window[1]);

    painter.setBrush(QBrush(Qt::yellow));
    painter.drawRect(goal);

    painter.setPen(Qt::red);
    painter.drawLine(tx1, hsize, hsize, ty);
    painter.drawLine(tx2, hsize, hsize, ty);

    painter.end();
}

void picturebox::move_build(const int &_y)
{
    y = _y;
    item->setPos(pix_x, y);
    line1->setLine(p_x, 0, mx1, y); // Инициализируем вторую группу элементов
    line2->setLine(p_x, 0, mx2, y); // Инициализируем вторую группу элементов

}

void picturebox::move_start_point(const int &_x)
{
    p_x = _x;

    line1->setLine(p_x, 0, mx1, y); // Инициализируем вторую группу элементов
    line2->setLine(p_x, 0, mx2, y); // Инициализируем вторую группу элементов
}
