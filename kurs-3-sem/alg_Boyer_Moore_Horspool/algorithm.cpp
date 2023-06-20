#include "algorithm.h"
#include "ui_algorithm.h"

Algorithm::Algorithm(QWidget *parent) : QWidget(parent), ui(new Ui::Algorithm)
{
    ui->setupUi(this);
    ui->str->setText(sp.get_str());
    ui->pattern->setText(sp.get_pattern());
    ui->table->setText("таблица");

    ui->main->setText("<strong>начало</strong>");

    ui->status->setText("статус");
}

Algorithm::~Algorithm() { delete ui; }

void Algorithm::on_str_textEdited(const QString &arg1) { sp.set_str(arg1); }

void Algorithm::on_pattern_textChanged(const QString &arg1) { sp.set_pattern(arg1); }

void Algorithm::show_alg()
{
    ui->main->setText(s[i][j]);
}

void Algorithm::on_Ok_clicked()
{
    ui->table->setText("таблица");
    if (sp.BMH())
    {
        ui->status->setText("ДА");
    } else { ui->status->setText("НЕТ"); }

    if (sp.get_table_size() > 0)
    {
        ui->table->setText(sp.get_table());
    }
    s = sp.get_proz();
    n = s.size(); i=0; j=0;
    show_alg();
    sp.clear();
}

void Algorithm::on_b_back_clicked()
{
    --i;
    if (i<0) { i = n-1; }
    j = s[i].size()-1;
    show_alg();
}

void Algorithm::on_l_back_clicked()
{
    --j;
    if (j<0) { on_b_back_clicked(); }
    show_alg();
}

void Algorithm::on_l_forward_clicked()
{
    ++j;
    if (j==s[i].size()){ on_b_forward_clicked(); }
    show_alg();
}

void Algorithm::on_b_forward_clicked()
{
    ++i; j=0;
    if (i==n) { i=0; }
    show_alg();
}
