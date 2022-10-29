#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget_1->setShowGrid(true);
    // Разрешаем выделение колонок
    ui->tableWidget_1->setSelectionBehavior(QAbstractItemView::SelectColumns);

    ui->tableWidget_2->setShowGrid(true);
    // Разрешаем выделение колонок
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectColumns);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::first_table()
{
    px.clear();
    Hx = 0;
    int t = 0;
    int n = qs.size();
    int qsl1_n = qsl1.size();

    ui->tableWidget_1->clear();
    ui->tableWidget_1->setColumnCount(qsl1_n+1);
    ui->tableWidget_1->setRowCount(3); // Указываем число строк

    for (int k=0; k<qsl1_n; ++k)
    {
        ui->tableWidget_1->setItem(0, k, new QTableWidgetItem(qsl1[k]));
        t = qs.count(qsl1[k]);
        ui->tableWidget_1->setItem(1, k, new QTableWidgetItem(QString::number(t)));
        px.push_back(double(t)/n);
        ui->tableWidget_1->setItem(2, k, new QTableWidgetItem(QString::number(t) + "/" + QString::number(n)));

        Hx += -px[px.size()-1]*log2(px[px.size()-1]);
    }
    ui->tableWidget_1->setItem(0, qsl1_n, new QTableWidgetItem("E"));
    ui->tableWidget_1->setItem(1, qsl1_n, new QTableWidgetItem(QString::number(n)));
    ui->tableWidget_1->setItem(2, qsl1_n, new QTableWidgetItem("1"));

    ui->H_x->setText(QString::number(Hx));

    // Устанавливаем заголовки
    ui->tableWidget_1->setVerticalHeaderLabels(QStringList() << "x" << "n" << "p");
    // Ресайзим колонки по содержимому
    ui->tableWidget_1->resizeColumnsToContents();


}

void MainWindow::second_table()
{
    Hyx = 0;
    H_xy = 0;
    int t = 0;
    int n = qs.size();
    int qsl2_n = qsl2.size();

    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(qsl2_n+1);
    ui->tableWidget_2->setRowCount(3); // Указываем число строк

    for (int k=0; k<qsl2_n; ++k)
    {
        ui->tableWidget_2->setItem(0, k, new QTableWidgetItem(qsl2[k]));
        t = qs.count(qsl2[k]);
        if (qsl2[k] == QString(qs[n-1])+QString(qs[0])) { ++t; }
        ui->tableWidget_2->setItem(1, k, new QTableWidgetItem(QString::number(t)));
        p_yx.push_back(double(t)/n);
        if (p_yx[qsl2_n-1] == 0) { p_yx[qsl2_n-1] = (1/n); }
        ui->tableWidget_2->setItem(2, k, new QTableWidgetItem(QString::number(t) + "/" + QString::number(n)));

        H_xy += -p_yx[p_yx.size()-1]*log2(p_yx[p_yx.size()-1]);
    }
    ui->tableWidget_2->setItem(0, qsl2_n, new QTableWidgetItem("E"));
    ui->tableWidget_2->setItem(1, qsl2_n, new QTableWidgetItem(QString::number(n)));
    ui->tableWidget_2->setItem(2, qsl2_n, new QTableWidgetItem("1"));

    ui->H_xy->setText(QString::number(H_xy));

    // Устанавливаем заголовки
    ui->tableWidget_2->setVerticalHeaderLabels(QStringList() << "x" << "n" << "p");
    // Ресайзим колонки по содержимому
    ui->tableWidget_2->resizeColumnsToContents();

    for (int i=0; i<qsl1.size(); ++i)
    {
        for (int j=0; j<qsl2_n; ++j)
        {
            if (qsl2[j].indexOf(qsl1[i]) == 0)
            {
                Hyx += -p_yx[j]*log2(p_yx[j]/px[i]);
            }
        }
    }
    ui->Hyx->setText(QString::number(Hyx));
}


void MainWindow::on_start_clicked()
{
    qs = ui->lineEdit->text();

    qsl1 = QStringList(qs.begin(), qs.end());
    qsl1.removeDuplicates();

    qsl2.clear();

    int n = qs.size()-1;
    for (int i=0; i<n; ++i)
    {
        qsl2.push_back(QString(qs[i])+QString(qs[i+1]));
    }
    qsl2.push_back(QString(qs[n])+QString(qs[0]));
    qsl2.removeDuplicates();

    first_table();
    second_table();

    ui->I_->setText(QString::number(Hx-Hyx));

    ui->D_o->setText(QString::number(1 - (log2(qsl1.size())/(ceil(log2(qsl1.size()))+1))));

    Dp = 1 - (Hx/log2(qsl1.size()));
    ui->D_p->setText(QString::number(Dp));

    Ds = 1 - (Hyx/Hx);
    ui->D_s->setText(QString::number(Ds));

    ui->D_->setText(QString::number(Dp + Ds - Dp*Ds));
}
