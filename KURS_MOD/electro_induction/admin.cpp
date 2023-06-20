#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) : QWidget(parent), ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin() { delete ui; }

void admin::show_text(const QString s)
{
    fname = s;
    text = reader::read_text(fname);
    if (text == reader::get_warning())
    {
        QMessageBox::warning(this, "Ошибка", "Нет файла или он пуст " + fname);
        text.clear();
        ui->Do->setText("");
    } else { ui->text->setPlainText(text); }
}

void admin::setEnabl()
{
    ui->r_Main->setEnabled(true);
    ui->r_Theory->setEnabled(true);
    ui->r_Slovo->setEnabled(true);
    ui->r_Test->setEnabled(true);
    ui->r_Statistic->setEnabled(true);
    ui->r_Rules->setEnabled(true);
    ui->r_Exercise->setEnabled(true);
    ui->r_Names->setEnabled(true);
}


void admin::on_r_Main_clicked()
{
    setEnabl();
    ui->r_Main->setEnabled(false);
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    show_text("files/begin.txt");
}

void admin::on_r_Theory_clicked()
{
    setEnabl();
    ui->r_Theory->setEnabled(false);
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    show_text("files/teo.txt");
}

void admin::on_r_Slovo_clicked()
{
    setEnabl();
    ui->r_Slovo->setEnabled(false);
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    show_text("files/slovo.txt");
}

void admin::on_r_Test_clicked()
{
    setEnabl();
    ui->r_Test->setEnabled(false);
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    show_text("files/test.txt");
}

void admin::on_r_Statistic_clicked()
{
    setEnabl();
    ui->r_Statistic->setEnabled(false);
    ui->text->setReadOnly(true);
    ui->Do->setText("Удалить");
    show_text("files/stat.txt");
}

void admin::on_r_Rules_clicked()
{
    setEnabl();
    ui->r_Rules->setEnabled(false);
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    show_text("files/rules.txt");
}

void admin::on_r_Exercise_clicked()
{
    setEnabl();
    ui->r_Exercise->setEnabled(false);
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    show_text("files/exercise.txt");
}

void admin::on_r_Names_clicked()
{
    setEnabl();
    ui->r_Names->setEnabled(false);
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    show_text("files/names.txt");
}

void admin::on_Do_clicked()
{
    std::ofstream out (fname.toStdString().data(), std::ios::binary);
    if (ui->Do->text() == "Удалить")
    {
        out.clear();
    } else if (ui->Do->text() == "Сохранить")
    {
        if (out)
        {
            int c = reader::get_code();
            std::string block = ui->text->toPlainText().toStdString();
            for (char &i: block) { i ^= c; }
            out.write(block.data(), int(block.size()));
        }
    }
    out.close();
}
