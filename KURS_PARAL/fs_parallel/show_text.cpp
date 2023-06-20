#include "show_text.h"
#include "ui_show_text.h"

show_text::show_text(QWidget *parent) : QWidget(parent), ui(new Ui::show_text)
{
    ui->setupUi(this);
    read_info();
}

show_text::~show_text() { delete ui; }

void show_text::on_return_to_clicked() { emit return_to_menu(); }

void show_text::read_info()
{
    QFile file(info);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        ui->text->setText(file.readAll());
        file.close();
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла или он пуст " + info); }
}
