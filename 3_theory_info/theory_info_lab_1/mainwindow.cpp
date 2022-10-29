#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->menu);

    on_to_menu_clicked();

    ui->tableWidget->setShowGrid(true);
    // Разрешаем выделение колонок
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);

    // создадим пустой график функции
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(Qt::blue));
    ui->widget->graph(1)->setPen(QPen(Qt::green));
    // добавим возможность зумить и перемещаться по графику
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

MainWindow::~MainWindow() { delete ui; }

double MainWindow::C_(const int &n, const int &k)
{
    if (n == 0) return 0;
    if (n == k || k == 0) return 1;
    return C_(n-1, k-1)*n/k;
}

void MainWindow::draw_graph(const QVector<double> x, const QVector<double> y)
{
    ui->widget->graph(1)->data()->clear();
    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}

void MainWindow::on_ex_1_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->exersize);
    ui->stackedWidget_2->setCurrentWidget(ui->exersize_1);

    ui->tableWidget->clear();

    ui->widget->graph(0)->data()->clear();
    ui->widget->xAxis->setLabel("p");
    ui->widget->yAxis->setLabel("H");
    ui->widget->replot();
}
void MainWindow::on_start_1_clicked()
{
    int n = ui->N_1->value();
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(n+1);

    ui->tableWidget->setRowCount(2); // Указываем число строк

    // Выполняем заполнение QTableWidget с помощью цикла
    double *C = new double[n];
    for (int k=0; k<=n; ++k)
    {
        ui->tableWidget->setItem(0, k, new QTableWidgetItem(QString::number(k)));
        C[k] = C_(n, k);
        ui->tableWidget->setItem(1, k, new QTableWidgetItem(QString::number(C[k]) + "*p^(" + QString::number(k) + ")*q^(" + QString::number(n-k) + ")"));
    }

    // Устанавливаем заголовки
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "x" << "y");
    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();

    double Pi;
    QVector<double> P;
    QVector<double> H;
    double q;
    P.push_back(0);
    H.push_back(0);
    for (double p_=0.001; fabs(p_-1) > 0.00001; p_ += 0.001)
    {
        P.push_back(p_);
        H.push_back(0);
        q = 1-p_;
        for (int k=0; k<=n; ++k)
        {
            Pi = C[k]*pow(p_, k)*pow(q, n-k);
            H[H.size()-1] += -Pi*log2(Pi);
        }
    }
    P.push_back(1);
    H.push_back(0);
    draw_graph(P, H);
}

std::vector<double> MainWindow::entro_val_2(const double &p_)
{
    std::vector<double> H;
    H.push_back(0);
    if (p_ < 1)
    {
        double CurPi = 0;
        double Pi = 0;
        double q = 1-p_;
        double mnoz = 1; // q^0
        while(fabs(CurPi-1) > 0.001)
        {
            Pi = p_*mnoz;
            H.push_back(Pi);
            mnoz *= q;
            CurPi += Pi;
        }
        double entr = 0;
        for (size_t k=1; k<H.size(); ++k) { entr += H[k]*log2(H[k]); }
        H.push_back(-entr);
    }
    return H;
}
void MainWindow::on_ex_2_clicked()
{
    ui->tableWidget->clear();
    ui->stackedWidget->setCurrentWidget(ui->exersize);
    ui->stackedWidget_2->setCurrentWidget(ui->exersize_2);

    ui->widget->graph(0)->data()->clear();
    ui->widget->xAxis->setLabel("p");
    ui->widget->yAxis->setLabel("H");
    ui->widget->replot();

    QVector<double> P;
    QVector<double> H;
    ui->max_2->setText(QString::number(entro_val_2(0.01).back()));
    for (double p_=0.01; fabs(p_-1) > 0.00001; p_ += 0.001)
    {
        P.push_back(p_);
        H.push_back(entro_val_2(p_).back());
    }
    ui->min_2->setText(QString::number(H[H.size()-1]));

    draw_graph(P, H);
}
void MainWindow::on_start_2_clicked()
{
    double p = ui->P_2->value();
    std::vector<double> H = entro_val_2(p);

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(H.size()-2);

    ui->tableWidget->setRowCount(2); // Указываем число строк

    ui->entro_2->setText(QString::number(H.back()));
    for (size_t k=1; k<H.size()-1; ++k)
    {
        ui->tableWidget->setItem(0, k-1, new QTableWidgetItem(QString::number(k)));
        ui->tableWidget->setItem(1, k-1, new QTableWidgetItem(QString::number(H[k])));
    }
    // Устанавливаем заголовки
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "x" << "p");
    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_ex_3_clicked()
{
    ui->tableWidget->clear();

    ui->stackedWidget->setCurrentWidget(ui->exersize);
    ui->stackedWidget_2->setCurrentWidget(ui->exersize_3);

    ui->widget->graph(0)->data()->clear();
    ui->widget->xAxis->setLabel("k");
    ui->widget->yAxis->setLabel("H");
    ui->widget->replot();
}

std::vector<double> MainWindow::entro_val_3(const int &n, const int &m, const int &k, const double &t)
{
    int size = std::min(m, k)+2;
    double Pi;
    std::vector<double> H(size, 0);
    if (k == 0 || k == n)
    {
        for (int i=0; i<size-1; ++i) { H[i] = 0; }
        H[size-2] = 1;
        H[size-1] = 0;
    } else if (k < n)
    {
        for (int i=0; i<size-1; ++i)
        {
            Pi =  C_(k, i)*C_(n-k, m-i)/t;
            H[i] = -Pi*log2(Pi);
            if (H[i] != H[i]) { H[i] = 0; }
            H[size-1] += H[i];
        }
    }
    return H;
}
void MainWindow::on_start_31_clicked()
{
    int n = ui->N_3->value();
    int m = ui->M_3->value();

    QVector<double> K;
    QVector<double> H;

    double t = C_(n, m);
    for (int k=0; k<n+1; ++k)
    {
        K.push_back(k);
        H.push_back(entro_val_3(n, m, k, t).back());
    }

    double* Mm = std::max_element(H.begin(), H.end()-1);
    ui->max_3->setText(QString::number(*Mm));

    draw_graph(K, H);
    ui->widget->graph(1)->addData(K, QVector<double>(n+1,*Mm));
    ui->widget->replot();
}

void MainWindow::on_start_32_clicked()
{
    int n = ui->N_3->value();
    int m = ui->M_3->value();
    int k = ui->K_3->value();

    double t = C_(n, m);
    int size = std::min(m, k)+1;
    std::vector<double> H(size, 0);
    for (int i=0; i<size; ++i)
    {
        H[i] = C_(k, i)*C_(n-k, m-i)/t;
    }
    if (k == n) { H[size-1] = 1; }


    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(H.size());

    ui->tableWidget->setRowCount(2); // Указываем число строк

    ui->entro_3->setText(QString::number(H.back()));
    for (size_t k=0; k<H.size(); ++k)
    {
        ui->tableWidget->setItem(0, k, new QTableWidgetItem(QString::number(k)));
        ui->tableWidget->setItem(1, k, new QTableWidgetItem(QString::number(H[k])));
    }
    // Устанавливаем заголовки
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "x" << "p");
    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::on_M_3_valueChanged(int arg1)
{
    int n = ui->N_3->value();
    if (arg1 > n) { ui->M_3->setValue(n); }
}
void MainWindow::on_K_3_valueChanged(int arg1)
{
    int n = ui->N_3->value();
    if (arg1 > n) { ui->K_3->setValue(n); }
}

void MainWindow::on_to_menu_clicked()
{
    ui->tableWidget->clear();
    ui->stackedWidget->setCurrentWidget(ui->menu);
}
