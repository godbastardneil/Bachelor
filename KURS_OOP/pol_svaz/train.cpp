#include "train.h"
#include "ui_train.h"

train::train(QWidget *parent) : QWidget(parent), ui(new Ui::train)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    ex = new QString[n];
    ans = new QString[n];
}

train::~train() { delete ui; }

void train::set_rul()
{
    QString text = reader::read_text(rul);
    if (text == reader::get_warning())
    {
        QMessageBox::warning(this, "Ошибка", "Нет файла " + rul);
    }
    ui->main->setText(text);
}

void train::on_stud_c_textChanged(const QString &arg1) { ans[i] = arg1; }


void train::on_l_back_clicked()
{
    --i;
    if (i >= 0)
    {
        ui->stud_c->setText(ans[i]);
        ui->main->setPlainText(QString::number(i+1) + ") " + ex[i]);
    } else { ++i; }
}
void train::on_l_forward_clicked()
{
    ++i;
    if (i < n)
    {
        ui->stud_c->setText(ans[i]);
        ui->main->setPlainText(QString::number(i+1) + ") " + ex[i]);
    } else { --i; }
}

void train::start_test()
{
    i = 0;
    ui->stackedWidget->setCurrentWidget(ui->open);
    ui->main->setPlainText(QString::number(i+1) + ") " + ex[i]);
    ui->stud_c->setText(ans[i]);
}

void train::on_Super_Easy_clicked()
{
    level = "Супер Легкий";
    for (int j=0; j<n; ++j) { ex[j] = train_comp::super_easy(rd, dis); }
    start_test();
}

void train::on_Easy_clicked()
{
    level = "Легкий";
    for (int j=0; j<n; ++j) { ex[j] = train_comp::easy(rd, dis); }
    start_test();
}

void train::on_Normal_clicked()
{
    level = "Нормальный";
    for (int j=0; j<n; ++j) { ex[j] = train_comp::normal(rd, dis); }
    start_test();
}

void train::on_Hard_clicked()
{
    level = "Сложный";
    for (int j=0; j<n; ++j) { ex[j] = train_comp::hard(rd, dis); }
    start_test();
}

void train::on_Random_clicked()
{
    level = "Случайный";
    for (int j=0; j<n; ++j)
    {
        switch (dis(rd)%4)
        {
        case 0:
            ex[j] = train_comp::super_easy(rd, dis);
            break;
        case 1:
            ex[j] = train_comp::easy(rd, dis);
            break;
        case 2:
            ex[j] = train_comp::normal(rd, dis);
            break;
        case 3:
            ex[j] = train_comp::hard(rd, dis);
            break;
        }
    }
    start_test();
}

void train::on_return_to_clicked() { emit return_to_menu(); }

void train::on_end_test_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->main->setHtml(train_comp::check_stat(name, level, ex, ans, n));
    for (int j=0; j<n; ++j) { ex[j].clear(); ans[j].clear(); }
}

