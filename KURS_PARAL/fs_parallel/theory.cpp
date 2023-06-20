#include "theory.h"
#include "ui_theory.h"

theory::theory(QWidget *parent) : QWidget(parent), ui(new Ui::theory)
{
    ui->setupUi(this);
    read_theory();
}

theory::~theory() { delete ui; }

void theory::on_return_to_clicked() { emit return_to_menu(); }

void theory::read_theory()
{
    QFile f1(teo);
    if ((f1.exists())&&(f1.open(QIODevice::ReadOnly)))
    {
        ui->teo->setText(f1.readAll());
        f1.close();
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла или он пуст " + teo); }

    QFile f2(slovo);
    if ((f2.exists())&&(f2.open(QIODevice::ReadOnly)))
    {
        ui->slovo->setText(f2.readAll());
        f2.close();
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла или он пуст " + slovo); }
    ui->teo->setOpenLinks(false);
}

void theory::on_teo_anchorClicked(const QUrl &arg1)
{
    if (arg1.fileName() == "slovo")
    {
        ui->slovo->scrollToAnchor(arg1.fragment());
    }
}
