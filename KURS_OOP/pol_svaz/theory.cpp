#include "theory.h"
#include "ui_theory.h"

theory::theory(QWidget *parent) : QWidget(parent), ui(new Ui::theory)
{
    ui->setupUi(this);

}

theory::~theory() { delete ui; }

void theory::read_theory()
{
    QString text = reader::read_text(teo);
    if (text == reader::get_warning())
    {
        QMessageBox::warning(this, "Ошибка", "Нет файла " + teo);
    }
    ui->teo->setText(text);

    text = reader::read_text(slovo);
    if (text == reader::get_warning())
    {
        QMessageBox::warning(this, "Ошибка", "Нет файла " + slovo);
    }
    ui->slovo->setText(text);
    ui->teo->setOpenLinks(false);
}

void theory::on_teo_anchorClicked(const QUrl &arg1)
{
    if (arg1.fileName() == "slovo")
    {
        ui->slovo->scrollToAnchor(arg1.fragment());
    }
}

void theory::on_return_to_clicked()
{
    emit return_to_menu();
}
