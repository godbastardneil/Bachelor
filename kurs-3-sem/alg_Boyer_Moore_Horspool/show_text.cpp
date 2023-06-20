#include "show_text.h"
#include "ui_show_text.h"

show_text::show_text(QWidget *parent) : QWidget(parent), ui(new Ui::show_text)
{
    ui->setupUi(this);
}

show_text::~show_text() { delete ui; }

void show_text::write_text(const QString &fname)
{
    if (writer.read_text(fname))
    {
        ui->text->setText(writer.get_text());
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла " + fname); }
}

void show_text::write_stat(const QString &fname, const std::string &qs)
{
    if (writer.read_text(fname))
    {
        std::string t = "<h3 align=\"center\"> Стратистика </h3>";
        size_t m = qs.size();
        size_t i = t.size();
        t += writer.get_text().toStdString();
        while (i<t.size())
        {
            size_t f = t.find(qs, i);
            if (f != std::string::npos)
            {
                t.insert(f+m, "</font>");
                t.insert(f, "<font color=\"red\">");
                i = f+m+20;
            } else { i = t.size(); }
        }
        ui->text->setText(QString::fromStdString(t));
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла " + fname); }
}
