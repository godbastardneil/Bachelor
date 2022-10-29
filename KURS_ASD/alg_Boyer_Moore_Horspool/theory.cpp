#include "theory.h"
#include "ui_theory.h"

theory::theory(QWidget *parent) : QWidget(parent), ui(new Ui::theory)
{
    ui->setupUi(this);
}

theory::~theory() { delete ui; }

void theory::write_teo()
{
    if (writer.read_text(teo))
    {
        ui->teo->setText(writer.get_text());
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла " + teo); }

    if (writer.read_text(slovo))
    {
        ui->slovo->setText(writer.get_text());
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла " + slovo); }
    ui->teo->setOpenLinks(false);
}

void theory::on_teo_anchorClicked(const QUrl &arg1)
{
    if (arg1.fileName() == "slovo")
    {
        ui->slovo->scrollToAnchor(arg1.fragment());
    }
}
