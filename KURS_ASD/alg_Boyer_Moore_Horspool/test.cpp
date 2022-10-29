#include "test.h"
#include "ui_test.h"

#include <QDebug>

test::test(QWidget *parent) : QWidget(parent), ui(new Ui::test)
{
    ui->setupUi(this);
}

test::~test() { delete ui; }

void test::write_test(const QString u_name)
{
    name = u_name;
    if (writer.read_text(fname))
    {
        testing = test_comp::Instance().create_test(writer.get_text());
        n = testing.size();
        ans.resize(n);
        i = 0;
        ui->qwest->setText(testing[i].question);
        ui->stackedWidget->setCurrentWidget(ui->page);
        ui->stackedWidget->setEnabled(false);
        ui->l_back->setEnabled(true);
        ui->l_forward->setEnabled(true);
        ui->end_test->setEnabled(true);
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла " + fname); }
}

void test::show_test()
{
    ui->qwest->setText(QString::number(i) + ". " + testing[i].question);
    int m = testing[i].q_answer.size();
    if (m>1)
    {
        ui->stackedWidget->setCurrentWidget(ui->close);
        ui->checkBox_0->setChecked(false);
        ui->checkBox_1->setChecked(false);
        ui->checkBox_2->setChecked(false);
        ui->checkBox_3->setChecked(false);
        ui->checkBox_0->setText(testing[i].q_answer[0].ans);
        ui->checkBox_1->setText(testing[i].q_answer[1].ans);
        ui->checkBox_2->setText(testing[i].q_answer[2].ans);
        ui->checkBox_3->setText(testing[i].q_answer[3].ans);
        for (int j=0; j<ans[i].size(); ++j)
        {
            if (ans[i][j] == '1')
            {
                ui->checkBox_0->setChecked(true);
            } else if (ans[i][j] == '2')
            {
                ui->checkBox_1->setChecked(true);
            } else if (ans[i][j] == '3')
            {
                ui->checkBox_2->setChecked(true);
            } else { ui->checkBox_3->setChecked(true); }
        }
    } else
    {
        ui->stackedWidget->setCurrentWidget(ui->open);
        ui->stud_c->setText(ans[i]);
    }
}

void test::on_checkBox_0_clicked(bool checked)
{
    if (checked)
    {
        ans[i] += '1';
    } else { ans[i].remove('1'); }
}
void test::on_checkBox_1_clicked(bool checked)
{
    if (checked)
    {
        ans[i] += '2';
    } else { ans[i].remove('2'); }
}
void test::on_checkBox_2_clicked(bool checked)
{
    if (checked)
    {
        ans[i] += '3';
    } else { ans[i].remove('3'); }
}
void test::on_checkBox_3_clicked(bool checked)
{
    if (checked)
    {
        ans[i] += '4';
    } else { ans[i].remove('4'); }
}
void test::on_stud_c_textChanged(const QString &arg1) { ans[i] = arg1; }


void test::on_l_back_clicked()
{
    ui->stackedWidget->setEnabled(true);
    --i;
    if (i<1)
    {
        ++i;
    } else { show_test(); }
}
void test::on_l_forward_clicked()
{
    ui->stackedWidget->setEnabled(true);
    ++i;
    if (i==n)
    {
        --i;
    } else { show_test(); }
}


void test::on_end_test_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->stackedWidget->setEnabled(false);
    ui->l_back->setEnabled(false);
    ui->l_forward->setEnabled(false);
    ui->end_test->setEnabled(false);
    int win = 0;
    for (int j=1; j<n; ++j)
    {
        win += test_comp::Instance().check_ans(testing[j].q_answer, ans[j]);
    }
    ans.clear();
    ui->qwest->setText(test_comp::Instance().input_stat(name, win));
}

