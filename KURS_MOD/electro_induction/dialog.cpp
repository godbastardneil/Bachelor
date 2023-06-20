#include "dialog.h"
#include "ui_dialog.h"

dialog::dialog(QWidget *parent) : QDialog(parent), ui(new Ui::dialog)
{
    ui->setupUi(this);
    c = 0;
    check = 0;
    data_base = reader::read_text(data);
    if (data_base == reader::get_warning())
    {
        on_buttonBox_rejected();
        QMessageBox::warning(this, "Ошибка", "Нет файла " + data);
    }
    ui->password->setEnabled(false);
}

dialog::~dialog() { delete ui; }

void dialog::on_checkBox_clicked(bool checked)
{
    check = checked;
    ui->password->setEnabled(checked);
}

void dialog::on_buttonBox_accepted()
{
    if (name != "")
    {
        if (check)
        {
            if ((data_base.indexOf("Администратор: " + name) >= 0) && (password != "" && data_base.indexOf("Пароль: " + password) >= 0))
            {
                c = 2;
            } else { c = 0; }
        } else
        {
            if (data_base.indexOf("Пользователь: " + name) >= 0)
            {
                c = 1;
            } else { c = 0; }
        }
    }
}
