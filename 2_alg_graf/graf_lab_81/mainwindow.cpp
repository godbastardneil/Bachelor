#include "mainwindow.h"
#include "ui_mainwindow.h"

    using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_histogram();
}

MainWindow::~MainWindow() { delete cV; delete ui; }

uint8_t MainWindow::creat_sets(QBarSeries *qBarS)
{
// сравниваемое множество
    QVector<QBarSet*> set {new QBarSet("БИЛАЙН"), new QBarSet("МТС"), new QBarSet("МЕГАФОН"), new QBarSet("СМАРТС")};
    int n = set.size();
    QVector<int> kol(n, 0); // подсчет количества обонентов оператора

    std::ifstream in ("data.txt");
    QString num = "Оператор: ";
    QString qs;
    bool b = 0;
    uint8_t j = 0; // счет количества работников
    if(in)
    {
        std::string ss;
        while (getline(in, ss))
        {
            qs = QString::fromStdString(ss);
            if (qs.contains(num))
            {
                qs.remove(num);
                for (int i=0; i<n && !b; ++i)
                {
                    if (qs.contains(set[i]->label()))
                    {
                        ++kol[i];
                        b = 1;
                    }
                }
                if (!b) // на случай если во множестве нет нужных операторов
                {
                    set.push_back(new QBarSet(qs.remove(0, qs.indexOf('\n'))));
                    kol.push_back(1);
                    ++n;
                }
                ++j;
                b = 0;
            }
        }
    }
    for (int i=0; i<n; ++i)
    {
        *set[i] << kol[i]; // ввожу количество каждого сравниваемого
        qBarS->append(set[i]); // ввожу из в множество сравниваемых
    }
    return j;
}

void MainWindow::create_histogram()
{
// создаю сравниваемое множество
    QBarSeries *qBarS = new QBarSeries();
    uint8_t n = creat_sets(qBarS);

// создаю диаграмму
    QChart *c = new QChart();

    c->addSeries(qBarS);
    c->setTitle("Операторы связи");
    c->setAnimationOptions(QChart::SeriesAnimations); // анимация показа данных

// горизонтальная шкала может понадобиться если вы делаете множество сравниваемых
    // то же самое исследование количество апператоров разделенное на месяц
    // тогда бы мы получили тот же график разделенный на месяцы
//    QBarCategoryAxis *axX = new QBarCategoryAxis();

//    axX->append(/*сюда и ввлжить те самые под категории для сравнения*/);
//    c->addAxis(axX, Qt::AlignBottom);
//    qBarS->attachAxis(axX);

// вертикальная шкала
    QValueAxis *axY = new QValueAxis();
    axY->setRange(0, n); // отскольки до скольки
    axY->setTickCount(n+1); // количество линий делений
    c->addAxis(axY, Qt::AlignLeft);
    qBarS->attachAxis(axY);

// показываем ли мы легенду диаграммы или нет
    c->legend()->setVisible(true); // да показываем
    c->legend()->setAlignment(Qt::AlignBottom);

// создаем виджет для показа диаграммы и делаем его на основе mainwindow
    cV = new QChartView(this);

    cV->resize(this->width(), this->height());
    cV->setRenderHint(QPainter::Antialiasing);
    cV->setChart(c);
}
