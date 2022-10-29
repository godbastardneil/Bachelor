#include "demo.h"
#include "ui_demo.h"

demo::demo(QWidget *parent) : QWidget(parent), ui(new Ui::demo)
{
    ui->setupUi(this);

    algs << "1. Последовательная рекурсивная быстрая сортировка"
         << "2. Последовательная нерекурсивная быстрая сортировка"
         << "3. Параллельная быстрая сортировка №1"
         << "4. Параллельная быстрая сортировка №2";
    pot << "2" << "4" << "8" << "16";

    ui->algobox->addItems(algs);
}

demo::~demo() { delete ui; }

void demo::on_return_to_clicked() { emit return_to_menu(); }

void demo::on_begin_clicked()
{
    int n = QInputDialog::getInt(this, "Введите количество чисел", "N:");
    int m;

    QVector<int> str = generate_str(n);
    QByteArray data;

    std::copy(str.begin() , str.end() , std::back_inserter(data));
    ui->startline->setText(data.toHex(' '));

    unsigned int start;
    if (i == 0)
    {
        start = clock();
        norec_alg(str);
    } else if (i == 1)
    {
        start =  clock();
        rec_alg(str, 0, str.size());
    } else if  (i == 2)
    {
        m = QInputDialog::getItem(this, "Введите количество потоков", "M:",
                                 pot, 0).toInt();
        QVector<std::thread> thr(m);
        start =  clock();
        paral_alg(str, thr);
    } else
    {
        m = QInputDialog::getItem(this, "Введите глубину", "M:",
                                 pot, 0).toInt();
        QVector<std::thread> thr(m);
        start =  clock();
        paral_gl_alg(str, 0, n, 0, m);
    }
    unsigned int end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    qDebug() << seconds;


    std::copy(str.begin() , str.end() , std::back_inserter(data));
    ui->startline->setText(data.toHex(' '));
}


void demo::on_algobox_currentTextChanged(const QString &arg1)
{
    i = ui->algobox->currentIndex();
    QFile file(arg1 + ".html");
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        stat = file.readAll();
        ui->stat->setText(stat);
        file.close();
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла или он пуст " + arg1 + ".html"); }
}

QVector<int> demo::generate_str(const int &n)
{
    std::mt19937 mt(static_cast<int>(time(nullptr)));

    QVector<int> res(n);
    generate(res.begin(), res.end(), mt);

    return res;
}

void demo::init_stat(const int &n, const int &m, const double &time)
{
    QString tmp = "<tr><td>"+QString::number(n)+"</td>";
    int j = stat.indexOf("<tr><td>"+QString::number(n)+"</td>");
    int j_;
    if (i == 1 || i == 2)
    {
        if (j == -1)
        {
            j_ = stat.lastIndexOf("</tr>")+5;
            stat.insert(j_, tmp+"<td>"+QString::number(time)+"</td></tr>");
        } else
        {
            j = j+8;
            j_ = stat.indexOf("<td>", j)+4;
            stat.insert(j_, QString::number(time)+" / ");
        }
    } else if (i == 3 || i == 4)
    {
        if (j == -1)
        {
            j_ = stat.lastIndexOf("</tr>")+5;

            for (int m_=0; m_<4; ++m_)
            {
                if (m_ == m/4)
                {
                    tmp += "<td>" + QString::number(time) + "</td>";
                } else { tmp += "<td></td>"; }
            }
            tmp += "</tr>";
            stat.insert(j_, tmp);
        } else
        {
            j = j+8;
            j_ = j;
            for (int m_=0; m_<4 && m_ != 1+m/4; ++m_)
            {
                j_ = stat.indexOf("<td>", j_)+4;
            }
            int _j = stat.indexOf("</td>", j_);
            tmp = QString::number(time);
            if (_j == j_)
            {
                tmp += " / ";
            }
            stat.insert(j_, tmp);
        }
    }


    QFile file("files/" + QString::number(i) + ".html");
    if ((file.exists())&&(file.open(QIODevice::WriteOnly|QIODevice::Truncate)))
    {
        file.write(stat.toStdString().c_str());
        file.close();
    } else { QMessageBox::warning(this, "Ошибка", "Нет файла " + ui->algobox->currentText() + ".html"); }
}

