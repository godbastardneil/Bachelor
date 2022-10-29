#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(false);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::get_g()
{
    bit tmp ("1"+std::string(BCH[what][N]-1, '0')+"1");

    g = g_table[h][0];
    for (int j=1; j<i && j<g_table[h].size(); ++j) { g *= g_table[h][j]; }
    tmp.clear();
}
void MainWindow::init(QString arg1)
{
    int size = arg1.size();
    for (int k=0; k<BCH.size(); ++k)
    {
        if (BCH[k][K] == size)
        {
            what = k;
            k = BCH.size();
        }
    }

    ui->K_->setText(QString::number(BCH[what][K]));
    ui->R_->setText(QString::number(BCH[what][R]));
    ui->N_->setText(QString::number(BCH[what][N]));
    i = BCH[what][S];
    h = std::ceil(std::log2(BCH[what][N]+1))-2;

    get_g();
    try {
        a = bit(arg1.toStdString()+std::string(BCH[what][R], '0'));
    } catch (...) {
        arg1[arg1.size()-1] = '1';
        a = bit(arg1.toStdString()+std::string(BCH[what][R], '0'));
        ui->init->setText(arg1);
    }
}

void MainWindow::on_init_textEdited(const QString &arg1)
{
    int size = arg1.size();
    if ((size >= 5 && size <= 8) || size == 10 || size == 11 || size == 15)
    {
        ui->checkBox->setChecked(true);

        a.clear(), g.clear(), b.clear();

        init(arg1);
        ui->G_->setText(QString::fromStdString(g.toString()));
        ui->a_x_->setText(QString::fromStdString(a.toString()));

        b = a^(a%g);

        ui->B_->setText(QString::fromStdString(b.toString()));
    } else { ui->checkBox->setChecked(false); }
}

void MainWindow::find_error()
{
    bit tmp = _b;
    bit res("111");
    int k = 0;

    do {
        res = tmp%g;
        tmp <<= 1; ++k;
    } while (tmp != _b && std::count(res.begin(), res.end(), 1) > BCH[what][S]);

    if (res != bit("0"))
    {
        tmp >>= 1; --k;
        tmp ^= res;
        tmp >>= k;
        bi = tmp;
    } else { bi = res; }
    tmp.clear(); res.clear();
}

void MainWindow::on_pushButton_clicked()
{
    int tmp_S = ui->spinBox->value();
    if (tmp_S > BCH[what][S]) { tmp_S = BCH[what][S]; ui->spinBox->setValue(tmp_S); }

    if (BCH[what][K] >= 5)
    {
        _b.clear(); bi.clear();

        std::string st = b.toString();
        std::string s = b.toString();

        std::random_device rd;
        std::uniform_int_distribution<int> dis(0, BCH[what][N]-1);
        for (int k=0; k<tmp_S; ++k)
        {
            int j = dis(rd);
            if (st[j] == '1')
            {
                st[j] = '0';
            } else { st[j] = '1'; }

            if (st == s)
            {
                --k;
            } else { s = st; }
        }
        _b = bit(s);

        ui->_B_->setText(QString::fromStdString(_b.toString()));

        find_error();
        ui->_B_ispr->setText(QString::fromStdString(bi.toString()));
    }
}
