#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget_1->setShowGrid(true);
    // Разрешаем выделение колонок
    ui->tableWidget_1->setSelectionBehavior(QAbstractItemView::SelectColumns);

    ui->shenofano->setShowGrid(true);
    // Разрешаем выделение колонок
    ui->shenofano->setSelectionBehavior(QAbstractItemView::SelectColumns);

    ui->haffman->setShowGrid(true);
    // Разрешаем выделение колонок
    ui->haffman->setSelectionBehavior(QAbstractItemView::SelectColumns);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::set_first_table()
{
    int n = qs.size();
    int word_n = word[0].size();

    ui->tableWidget_1->clear();
    ui->tableWidget_1->setColumnCount(word_n+1);
    ui->tableWidget_1->setRowCount(3); // Указываем число строк

    for (int k=0; k<word_n; ++k)
    {
        ui->tableWidget_1->setItem(0, k, new QTableWidgetItem(word[0][k].sym));
        ui->tableWidget_1->setItem(1, k, new QTableWidgetItem(QString::number(word[0][k].n)));
        ui->tableWidget_1->setItem(2, k, new QTableWidgetItem(QString::number(word[0][k].n) + "/" + QString::number(n)));
    }
    ui->tableWidget_1->setItem(0, word_n, new QTableWidgetItem("E"));
    ui->tableWidget_1->setItem(1, word_n, new QTableWidgetItem(QString::number(n)));
    ui->tableWidget_1->setItem(2, word_n, new QTableWidgetItem("1"));

    // Устанавливаем заголовки
    ui->tableWidget_1->setVerticalHeaderLabels(QStringList() << "x" << "n" << "p");
    // Ресайзим колонки по содержимому
    ui->tableWidget_1->resizeColumnsToContents();
}

void MainWindow::sort(QVector<el> &w)
{
    int word_n = w.size();
    int t = 0;
    for (int i=0; i<word_n; ++i)
    {
        t = i;
        for (int j=i+1; j<word_n; ++j)
        {
            if (w[j].n>w[t].n) { t = j; }
        }
        std::swap(w[i], w[t]);
    }
}

void MainWindow::shenofano(const int &start, const int &end)
{
    int i = start;
    int j = end;
    double isum = word[0][i].px, jsum = word[0][j].px;

    while(i < (j-1))
    {
        while((isum >= jsum) && (i < (j-1)))
        {
            j--;
            jsum += word[0][j].px;
        }
        while((isum <= jsum) && (i < (j-1)))
        {
            i++;
            isum += word[0][i].px;
        }
    }

    if(i == start) {
        word[0][start].code1 += '0';
    } else if((i-start) >= 1)
    {
        for(int k=start; k<=i; ++k) { word[0][k].code1 += '0'; }

        shenofano(start, i);
    }

    if(j == end) {
        word[0][end].code1 += '1';
    } else if((end-j) >= 1)
    {
        for(int k=j; k<=end; ++k) { word[0][k].code1 += '1'; }

        shenofano(j, end);
    }
}
void MainWindow::set_shenofano()
{
    int word_n = word[0].size();

    shenofano(0, word_n-1);
    int count = word[0][word_n-1].code1.size();

    ui->shenofano->clear();
    ui->shenofano->setColumnCount(count+3);
    ui->shenofano->setRowCount(word_n); // Указываем число строк

    int s = 0;
    for (int k=0; k<word_n; ++k)
    {
        ui->shenofano->setItem(k, 0, new QTableWidgetItem(word[0][k].sym));
        ui->shenofano->setItem(k, 1, new QTableWidgetItem(QString::number(word[0][k].px)));
        ui->shenofano->setItem(k, count+2, new QTableWidgetItem(word[0][k].code1));

        s = word[0][k].code1.size();
        for (int i=0; i<s; ++i)
        {
            ui->shenofano->setItem(k, i+2, new QTableWidgetItem(QString(word[0][k].code1[i])));
        }
    }

    // Устанавливаем заголовки
    QString head(count+2, ' ');
    ui->shenofano->setHorizontalHeaderLabels(QStringList(head.begin(), head.end()));
    ui->shenofano->setHorizontalHeaderItem(0, new QTableWidgetItem("Символ"));
    ui->shenofano->setHorizontalHeaderItem(1, new QTableWidgetItem("p"));
    ui->shenofano->setHorizontalHeaderItem(count+2, new QTableWidgetItem("код"));
    // Ресайзим колонки по содержимому
    ui->shenofano->resizeColumnsToContents();
}

void MainWindow::haffman()
{
    QVector<el> w;
    QVector<int> poses;
    double tmp;
    bool add;
    for (int i=0; word[i].size()>2; ++i)
    {
        int n = word[i].size();
        tmp = word[i][n - 1].px + word[i][n - 2].px;
        for (int j = 0; j < n-2; j++)
        {
            w.push_back(word[i][j]);
        }
        add = false;
        for (int j=n-3; j>=0; --j)
        {
            if (w[j].px>=tmp)
            {
                w.insert(w.begin() + j+1, word[i][n-2].sym + word[i][n-1].sym);
                w[j+1].px = tmp;
                poses.push_back(j+1);
                j = -1;
                add = true;
            }
        }
        if (!add)
        {
            w.insert(w.begin(), word[i][n-2].sym + word[i][n-1].sym);
            w[0].px = tmp;
            poses.push_back(0);
        }
        word.push_back(w);
        w.clear();
    }
    QVector<QString> res, tmpw;
    res.push_back("0");
    res.push_back("1");
    for (int i=word.size()-1; i>0; --i)
    {
        for (int j=0; j<word[i].size(); ++j)
        {
            if (poses[i-1] != j) { tmpw.push_back(res[j]); }
        }
        tmpw.push_back(res[poses[i - 1]] + "0");
        tmpw.push_back(res[poses[i - 1]] + "1");
        res = tmpw;
        tmpw.clear();
    }
    for (int i=0; i<res.size(); ++i) { word[0][i].code2 = res[i]; }
}
void MainWindow::set_haffman()
{
    haffman();
    int word_n = word[0].size();
    int count = word[0][word_n-1].code1.size()+2;

    ui->haffman->clear();
    ui->haffman->setColumnCount(count+word.size());
    ui->haffman->setRowCount(word_n); // Указываем число строк

    int s = 0;
    for (int k=0; k<word_n; ++k)
    {
        ui->haffman->setItem(k, 0, new QTableWidgetItem(word[0][k].sym));
        ui->haffman->setItem(k, 1, new QTableWidgetItem(QString::number(word[0][k].px)));
        ui->haffman->setItem(k, count, new QTableWidgetItem(word[0][k].code2));

        s = word[0][k].code2.size();
        for (int i=0; i<s; ++i)
        {
            ui->haffman->setItem(k, i+2, new QTableWidgetItem(QString(word[0][k].code2[i])));
        }
    }

    for (int i=1; i<word.size(); ++i)
    {
        word_n = word[i].size();
        for (int j=0; j<word_n; ++j)
        {
            ui->haffman->setItem(j, count+i, new QTableWidgetItem(word[i][j].sym+" "+QString::number(word[i][j].px)));
        }
    }

    // Устанавливаем заголовки
    ui->haffman->setHorizontalHeaderLabels(QStringList() << "Символ" << "p");
    ui->haffman->setHorizontalHeaderItem(count, new QTableWidgetItem("код"));
    // Ресайзим колонки по содержимому
    ui->haffman->resizeColumnsToContents();
}



int MainWindow::find(const QChar &qc, QVector<el> &w)
{
    int s = w.size();
    int i = 0;
    while (i<s && qc != w[i].sym) { ++i; }

    return i;
}

void MainWindow::on_start_clicked()
{
    for (int i=0; i<word.size(); ++i) { word[i].clear(); }
    word.clear();
    word.push_back(QVector<el>());

    qs = ui->lineEdit->text();

    int n = qs.size();
    double t = 1.0/n;
    for (int i=0; i<n; ++i)
    {
        int k = find(qs[i], word[0]);
        if (k == word[0].size()) { word[0].push_back(QString(qs[i])); }
        ++word[0][k].n;
        word[0][k].px += t;
    }

    set_first_table();

    sort(word[0]);
    set_shenofano();
    set_haffman();
}
