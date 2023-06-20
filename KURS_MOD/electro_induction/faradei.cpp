#include "faradei.h"
#include "ui_faradei.h"

demo::demo(QWidget *parent) : QWidget(parent), ui(new Ui::faradei)
{
    ui->setupUi(this);

    ui->picture->addItem("Опыт №1. Опыт Фарадея");
    ui->picture->addItem("Опыт №2. Вращение рамки");

    on_picture_activated(0);

    ui->B_change->addItem("0.1 Тл/пиксель");
    ui->B_change->addItem("0.4 Тл/пиксель");
    ui->B_change->addItem("0.7 Тл/пиксель");
    ui->B_change->addItem("1 Тл/пиксель");
    on_B_change_activated(0);

    ui->R_change->addItem("Медь - 1.7");
    ui->R_change->addItem("Алюминий - 2.8");
    ui->R_change->addItem("Серебро - 1.6");
    ui->R_change->addItem("Золото - 2.4");

    ui->B_change_2->addItem("1 Тл");
    ui->B_change_2->addItem("4 Тл");
    ui->B_change_2->addItem("7 Тл");
    ui->B_change_2->addItem("10 Тл");
    on_B_change_2_activated(0);
}

demo::~demo() { delete ui; }

void demo::on_return_to_clicked() { emit return_to_menu(); }

void demo::on_B_change_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->pb->set_B(0.1);
        break;
    case 1:
        ui->pb->set_B(0.4);
        break;
    case 2:
        ui->pb->set_B(0.7);
        break;
    case 3:
        ui->pb->set_B(1);
    }
}
void demo::on_B_change_2_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->pb->set_B(1);
        break;
    case 1:
        ui->pb->set_B(4);
        break;
    case 2:
        ui->pb->set_B(7);
        break;
    case 3:
        ui->pb->set_B(10);
    }
}

void demo::on_R_change_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->pb->set_R(1.7);
        break;
    case 1:
        ui->pb->set_R(2.8);
        break;
    case 2:
        ui->pb->set_R(1.6);
        break;
    case 3:
        ui->pb->set_R(2.4);
    }
}


void demo::on_picture_activated(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    if (index == 0)
    {
        on_B_change_activated(ui->B_change->currentIndex());
    } else
    {
        on_B_change_2_activated(ui->B_change_2->currentIndex());
    }
    ui->pb->set_scene(index);
}

