#include "show_text.h"
#include "ui_show_text.h"

show_text::show_text(QWidget *parent) : QWidget(parent), ui(new Ui::show_text)
{
    ui->setupUi(this);
}

show_text::~show_text() { delete ui; }

void show_text::write_text(const QString &fname)
{
    text = reader::read_text(fname);
    if (text != reader::get_warning())
    {
        ui->text->setText(text);
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла или он пуст" + fname); }
}

void show_text::write_stat(const QString &fname, const std::string &qs)
{
    text = reader::read_text(fname);
    if (text != reader::get_warning())
    {
        std::string t = "<h3 align=\"center\"> Стратистика </h3>";
        size_t m = qs.size();
        size_t i = t.size();
        t += text.toStdString();
        while (i<t.size())
        {
            size_t f = t.find(qs, i);
            if ((f != std::string::npos))
            {
                t.insert(f+m, "</font>");
                t.insert(f, "<font color=\"red\">");
                i = 20;
            } else if (f == std::string::npos) { i = t.size(); }
            i += f+m;
        }
        ui->text->setText(QString::fromStdString(t));
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла или он пуст" + fname); }
}
