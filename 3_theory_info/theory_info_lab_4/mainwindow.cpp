#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->H_matrix->setShowGrid(true);
    // Разрешаем выделение колонок
    ui->H_matrix->setSelectionBehavior(QAbstractItemView::SelectColumns);

    ui->G_matrix->setShowGrid(true);
    // Разрешаем выделение колонок
    ui->G_matrix->setSelectionBehavior(QAbstractItemView::SelectColumns);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::init(const QString &arg1)
{
    A_gh.clear(); E_h.clear(); E_g.clear();
    qs.clear(); b.clear(); _b.clear(); _s.clear();

    qs = arg1;

    k = qs.size();
    r = std::ceil(std::log2(k+1 + std::log2(k+1)));
    n = k+r;
    er = n;
    ui->K_->setText(QString::number(k));
    ui->R_->setText(QString::number(r));
    ui->N_->setText(QString::number(n));

    std::random_device rd;
    std::uniform_int_distribution<int> dis(0, r-1);
    for (int i=0; i<k; ++i)
    {
        int t;
        QString tmp(r, '0');
        do { t = 2+dis(rd)%r; } while (t == 1);

        int tt = -1;
        for (int j=0; j<t; ++j)
        {
            int tt_t;
            do { tt_t = dis(rd); } while (tt_t == tt);
            tt = tt_t;
            tmp[tt] = '1';
        }

        if ((std::find(A_gh.begin(), A_gh.end(), tmp) == A_gh.end()))
        {
            A_gh.push_back(tmp);

            E_g.push_back(QString(k, '0'));
            E_g[i][i] = '1';
        } else { --i; }
    }
    for (int i=0; i<r; ++i)
    {
        E_h.push_back(QString(r, '0'));
        E_h[i][i] = '1';
    }
}

void MainWindow::H_table()
{
    ui->H_matrix->clear();
    ui->H_matrix->setColumnCount(n);
    ui->H_matrix->setRowCount(r); // Указываем число строк

    for (int i=0; i<r; ++i)
    {
        for (int j=0; j<k; ++j)
        {
            ui->H_matrix->setItem(i, j, new QTableWidgetItem(QString(A_gh[j][i])));
        }
        for (int j=0; j<r; ++j)
        {
            ui->H_matrix->setItem(i, k+j, new QTableWidgetItem(QString(E_h[i][j])));
        }
    }
    // Ресайзим колонки по содержимому
    ui->H_matrix->resizeColumnsToContents();
}
void MainWindow::G_table()
{
    ui->G_matrix->clear();
    ui->G_matrix->setColumnCount(n);
    ui->G_matrix->setRowCount(k); // Указываем число строк

    QVector<int> ves(n, 0);
    int f;
    int s;
    for (int i=0; i<k; ++i)
    {
        if (qs[i] == '1')
        {
            s = 1;
        } else { s = 0; }
        for (int j=0; j<k; ++j)
        {
            ui->G_matrix->setItem(i, j, new QTableWidgetItem(QString(E_g[i][j])));
            if (E_g[i][j] == '1')
            {
                f = 1;
            } else { f = 0; }
            ves[j] += s*f;
        }
        for (int j=0; j<r; ++j)
        {
            ui->G_matrix->setItem(i, k+j, new QTableWidgetItem(QString(A_gh[i][j])));
            if (A_gh[i][j] == '1')
            {
                f = 1;
            } else { f = 0; }
            ves[k+j] += s*f;
        }
    }
    // Ресайзим колонки по содержимому
    ui->G_matrix->resizeColumnsToContents();


    for (int i=0; i<n; ++i)
    {
        if (ves[i]%2 == 0)
        {
            b[i] = '0';
        } else { b[i] = '1'; }
    }
}

void MainWindow::on_init_textEdited(const QString &arg1)
{
    if (arg1.size() > 2)
    {
        init(arg1);

        b.resize(n, '0');
        _b.resize(n, '0');
        _s.resize(r, '0');

        H_table();
        G_table();

        ui->B_->setText(b);
        ui->spinBox->setValue(1);
        on_spinBox_valueChanged(1);
    }
}


void MainWindow::find_error()
{
    QVector<int> ves(r, 0);
    int f;
    int s;
    for (int i=0; i<r; ++i)
    {
        for (int j=0; j<k; ++j)
        {
            if (A_gh[j][i] == '1')
            {
                f = 1;
            } else { f = 0; }
            if (_b[j] == '1')
            {
                s = 1;
            } else { s = 0; }
            ves[i] += s*f;
        }
        f = 0;
        for (int j=0; j<r && f == 0; ++j)
        {
            if (j == i)
            {
                f = 1;
            } else { f = 0; }
            if (_b[k+j] == '1')
            {
                s = 1;
            } else { s = 0; }
            ves[i] += s*f;
        }
    }
    for (int i=0; i<r; ++i)
    {
        if (ves[i]%2 == 0)
        {
            _s[i] = '0';
        } else { _s[i] = '1'; }
    }

    for (int j=0; j<k && er == n; ++j)
    {
        if (A_gh[j] == _s) { er = j; }
    }
    for (int j=0; j<r && er == n; ++j)
    {
        if (E_h[j] == _s) { er = k+j; }
    }
    ++er;
}
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (qs.size())
    {
        er = n;
        if (arg1 > n)
        {
            arg1 = n;
            ui->spinBox->setValue(arg1);
        }
        --arg1;
        _b = b;
        if (_b[arg1] == '0')
        {
            _b[arg1] = '1';
        } else { _b[arg1] = '0'; }
        ui->_B_->setText(_b);

        find_error();
        ui->_S_->setText(_s);
        ui->er_->setText(QString::number(er));
    }
}

