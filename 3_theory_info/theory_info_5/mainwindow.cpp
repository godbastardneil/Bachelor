#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::get_g()
{
    bit tmp ("1"+std::string(n-1, '0')+"1");

    int siz = g_table.size();
    for (int i=r-1; i<siz; ++i)
    {
        int siz_i = g_table[i].size();
        for (int j=0; j<siz_i; ++j)
        {
            g = g_table[i][j];
            if (std::count(g.begin(), g.end(), 1) >= 3 && tmp%g == bit("0")) { r = i+1; n = k+r; j = siz_i; i = siz; }
        }
    }
}

void MainWindow::on_init_textEdited(const QString &arg1)
{
    if (arg1.size() > 2)
    {
        qs = arg1;
        k = arg1.size();
        r = std::ceil(std::log2(k+1 + std::log2(k+1)));
        n = k+r;
        ui->K_->setText(QString::number(k));
        ui->R_->setText(QString::number(r));
        ui->N_->setText(QString::number(n));
    }
}

void MainWindow::find_error()
{
    bit tmp = _b;
    bit res("111");
    int i = 0;

    do {
        res = tmp%g;
        tmp <<= 1; ++i;
    } while (tmp != _b && std::count(res.begin(), res.end(), 1) > 1);

    if (res != bit("0"))
    {
        tmp >>= 1; --i;
        tmp ^= res;
        tmp >>= i;
        bi = tmp;
    } else { bi = res; }
}
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (k > 2)
    {
        do
        {
            a.clear(); b.clear(); _b.clear(); bi.clear(); g.clear();
            get_g();

            a = bit(qs.toStdString()+std::string(r, '0'));

            ui->a_x_->setText(QString::fromStdString(a.toString()));

            ui->G_->setText(QString::fromStdString(g.toString()));

            qDebug() << QString::fromStdString((g).toString());
            b = a^(a%g);
            qDebug() << "1";


            ui->B_->setText(QString::fromStdString(b.toString()));
            if (arg1 > n)
            {
                arg1 = n;
                ui->spinBox->setValue(arg1);
            }
            qDebug() << "2";
            --arg1;
            _b = b;
            if (_b[arg1] == 0)
            {
                _b[arg1] = 1;
            } else { _b[arg1] = 0; }
            qDebug() << "3";
            ui->_B_->setText(QString::fromStdString(_b.toString()));
            qDebug() << "4";

            find_error();
            qDebug() << "5";
            ui->_B_ispr->setText(QString::fromStdString(bi.toString()));
            qDebug() << QString::fromStdString((bi).toString()) << QString::fromStdString((b).toString());
        } while (bi != b);
        qDebug() << '-';
    }
}
