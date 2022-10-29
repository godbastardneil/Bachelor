#include "exercise.h"
#include "ui_exercise.h"

exercise::exercise(QWidget *parent) : QWidget(parent), ui(new Ui::exercise)
{
    ui->setupUi(this);
    write_exercise();
}

exercise::~exercise() { delete ui; }

void exercise::change_exercise()
{
    int n = ex.size();
    ui->exersize->clear();
    for (int j=0; j<n; ++j) { ui->exersize->addItem("Задача №" + QString::number(j+1)); }
    on_exersize_activated(i);
}

void exercise::on_exersize_activated(int index)
{
    i = index;
    ui->task_text->setText(ex[i].ex);
    ui->explanation->clear();
    ui->answer->clear();
    ui->check->setEnabled(true);
}

void exercise::write_exercise()
{
    QString text = reader::read_text(fname_ex);
    if (text != reader::get_warning())
    {
        ex = exercise_comp::create_exercise(text);
        i = 0;
        change_exercise();
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла " + fname_ex); }
}


void exercise::on_answer_textChanged(const QString &arg1) { ans = arg1; }

void exercise::on_check_clicked()
{
    ui->check->setEnabled(false);
    if (ex[i].ans == ans)
    {
        ui->explanation->setText("<p>Правильно</p>" + ex[i].how);
    } else { ui->explanation->setText("<p>Неправильно</p>" + ex[i].how); }
}

void exercise::on_return_to_clicked()
{
    emit return_to_menu();
}
