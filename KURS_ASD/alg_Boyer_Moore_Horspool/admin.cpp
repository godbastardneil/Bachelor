#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) : QWidget(parent), ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin() { delete ui; }

void admin::show_text()
{
    if (writer.read_text(fname))
    {
        ui->text->setPlainText(writer.get_text());
    }
}

void admin::on_Main_clicked()
{
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    fname = "files/begin.txt";
    show_text();
}

void admin::on_Theory_clicked()
{
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    fname = "files/teo.txt";
    show_text();
}

void admin::on_Slovo_clicked()
{
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    fname = "files/slovo.txt";
    show_text();
}

void admin::on_Test_clicked()
{
    ui->text->setReadOnly(false);
    ui->Do->setText("Сохранить");
    fname = "files/test.txt";
    show_text();
}

void admin::on_Statistic_clicked()
{
    ui->text->setReadOnly(true);
    ui->Do->setText("Удалить");
    fname = "files/stat.txt";
    show_text();
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
            int c = writer.get_code();
            QString text = ui->text->toPlainText();
            std::string block = text.toStdString();
            for (char &i: block) { i ^= c; }
            out.write(block.data(), int(block.size()));
        }
    }
    out.close();
}

