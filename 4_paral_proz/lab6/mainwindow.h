#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTime>

#include <QMainWindow>
#include <QTimer>
#include <QThreadPool>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Potential { live = 2, alive = 3 }; // потенциалы
    QString start = "start", end = "end"; // состояния

    using TableRow = std::vector<bool>; // живо - true, мертво - false
    using LifeTable = std::vector<TableRow>;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *timer; // таймер
    const int step = 200; // 1 секунда

    QTime ct; // общий счётчик времени
    double def = 0; // счётчик времени для одного прогона
    size_t k = 0; // количество просчётов

    LifeTable table; // клентки
    size_t cell_size; // размер клетки
    size_t cell_in_height; // количество клеток в строке
    size_t cell_in_width; // количество клеток в столбце

    bool lifeRules(const size_t &p, const bool &state);

    size_t calcPotential(const size_t &i, const size_t &j);
    bool calcState(const size_t &i, const size_t &j);
    void calcStates();

    void posled(LifeTable &tableNew);
    void paral_po_strokam(LifeTable &tableNew);
    void paral_po_stolbzam(LifeTable &tableNew);

    void getTable();
    void paintTable();

    void repaint();

    void start_game();
    void end_game();
};
#endif // MAINWINDOW_H
