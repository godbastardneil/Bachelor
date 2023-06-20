#include "demo.h"
#include "ui_demo.h"

demo::demo(QWidget *parent) : QWidget(parent), ui(new Ui::demo)
{
    ui->setupUi(this);
    ui->forward->setEnabled(false);
    ui->back->setEnabled(false);
}

demo::~demo() { delete ui; }

void demo::on_str_textEdited(const QString &arg1) { ui->frame->set_str(arg1); }

void demo::on_Ok_clicked()
{
    if (ui->frame->get_str_size() > 0)
    {
        ui->forward->setEnabled(true);
        ui->back->setEnabled(true);
        ui->result->setText(ui->frame->get_result());
        i = 0;
        ui->frame->show_step(i);
    }
}

void demo::on_back_clicked()
{
    --i;
    if (i >= 0)
    {
        ui->frame->show_step(i);
    } else { ++i; }
}
void demo::on_forward_clicked()
{
    ++i;
    if (i < ui->frame->get_str_size())
    {
        ui->frame->show_step(i);
    } else { --i; }
}

void demo::on_return_to_clicked() { emit return_to_menu(); }

