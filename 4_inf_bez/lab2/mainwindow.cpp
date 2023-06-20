#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qcustomplot.h"

#include <QValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->addGraph();
    ui->widget->xAxis->setRange(0, size);
    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Оригинальный", 12));

    ui->widget_2->addGraph();
    ui->widget_2->xAxis->setRange(0, size);
    ui->widget_2->plotLayout()->insertRow(0);
    ui->widget_2->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget_2, "Зашифрованный", 12));

    ui->widget_3->addGraph();
    ui->widget_3->xAxis->setRange(0, size);
    ui->widget_3->plotLayout()->insertRow(0);
    ui->widget_3->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget_3, "Расшифрованный", 12));

    QRegularExpressionValidator *qrev = new QRegularExpressionValidator(QRegularExpression("\\d*"), this);
    ui->init_key->setValidator(qrev);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_init_key_textEdited(const QString &arg1)
{
    if ((QSet<QChar>(arg1.begin(), arg1.end()).size()) != arg1.length()) { ui->init_key->backspace(); }

    if (ui->init_key->text().length() == size) {
        k.clear();
        for (int t = 0; t < size; ++t) { k.push_back(2*arg1[t].digitValue()); }
        ui->OK_Button->setEnabled(true);
    } else if (ui->OK_Button->isEnabled()) { ui->OK_Button->setEnabled(false); }
}

void MainWindow::on_OK_Button_clicked()
{
    QVector<double> x;
    QVector<double> y;

    for (int t = 0; t < size; ++t)
    {
        x.push_back(t);
        y.push_back(X(t));

        x.push_back(t+1);
        y.push_back(X(t+1));
    }
    fun_print(ui->widget, x, y);


    QVector<double> crx;
    QVector<double> cry;

    for (int t = 0; t < size; ++t)
    {
        crx.push_back(t);
        cry.push_back(y[k[t]]);

        crx.push_back(t+1);
        cry.push_back(y[k[t]+1]);
    }
    fun_print(ui->widget_2, crx, cry);


    QVector<double> dcrx;
    QVector<double> dcry(2*size);

    for (int t = 0; t < size; ++t)
    {
        dcrx.push_back(t);
        dcry[k[t]] = cry[2*t];

        dcrx.push_back(t+1);
        dcry[k[t]+1] = cry[2*t+1];
    }
    fun_print(ui->widget_3, dcrx, dcry);
}

double MainWindow::X(const double &t)
{
    return (a*sin(t*alpha) + b*cos(t*beta) + t*c*cos( cos(t*gamma) ));
}

void MainWindow::fun_print(QCustomPlot *qcp, const QVector<double> &x, const QVector<double> &y)
{
    qcp->graph(0)->setData(x, y, true);
    qcp->yAxis->rescale();
    qcp->replot();
}

