#include <iostream>
#include "money.h"

using namespace std;

struct name
{
    uint32_t a :3;
    uint32_t b :3;
    uint32_t c :8;
    uint16_t d :10;
};
int menu () {
    int n;
    cout << endl;
    cout << "1. Сложение сум" << endl;
    cout << "2. Вычитание сум" << endl;
    cout << "3. Деление сум" << endl;
    cout << "4. Операция сравнения" << endl;
    cout << "5. Деление суммы на дробное число" << endl;
    cout << "6. Умножение на дробное число" << endl;
    cout << "0. Выход" << endl; // завершение выполнения программы
    do {
        cout << " Ввод: ";
        cin >> n;
    } while ((n<0) || (n>6));
    return n;
}

int main()
{
    cout << sizeof (name);
    cout << "Инициализация суммы mt0 ничем: " << endl;
    money mt;
    cout << mt;

    cout << "Инициализация суммы mt1 1им рублем и 1ой копейкой: " << endl;
    money mt1(1, 1);
    cout << mt1;
    cout << "Размер класса: " << sizeof(mt1) << endl;

    money m1;
    cout << "Введите сумму m1 (рубли и копейки через пробел неотрцательными числами): ";
    cin >> m1;

    cout << "Инициализация суммы mt2 суммой m1 (mt2(m1)): ";
    money mt2(m1);
    cout << mt2;

    cout << "Инициализация суммы mt3 суммой mt2 (mt3 = mt2): ";
    money mt3 = mt2;
    cout << mt3;

    cout << "Инициализация суммы mt4 (mt4{}): ";
    money mt4{};
    cout << mt4;

    int m = menu();
    while (m != 0)
    {
        if (m<5) { // первые 4 задния с money
            money m2;
            cout << " Введите сумму m2: ";
            cin >> m2;
            switch (m)
            {
                case 1: { // прибавление суммы m2 к m1
                    m1 += m2;
                    cout << m1;
                    break; }
                case 2: {  // вычитание суммы m2 из m1. Если результат вычитания меньше 0, то операция не проходит, и выдается сообщение об этом
                        try {
                            m1 -= m2;
                        } catch (money::less_then_0) {
                            cout << "Результат меньше 0, операция не прошла" << endl;
                        }
                        cout << m1;
                    break; }
                case 3: { // деление m1 на m2
                        cout << " Деление суммы m1 на m2 = " << m1 / m2;
                    break; }
                case 4: { // сравнение сумм m1 и m2
                    if (m1 == m2) {
                        cout << " Сумма m1 сравнима с m1";
                    } else if (m1 > m2) {
                        cout << " Сумма m1 больше m2";
                    } else { cout << " Сумма m2 больше m1"; }
                }
            }
        } else { // задания с дробным числом
            double d;
            cout << " Введите число: ";
            cin >> d;
            switch (m)
            {
                case 5: { // деление суммы на дробное число
                    cout << " Деление суммы m1 на d = " << m1 / d;
                    break; }
                case 6: { // умножение суммы на дробное число
                    m1 *= d;
                    cout << " Умножение суммы m1 на d = " << m1;
                }
            }
        }
        cout << endl;
        m = menu();
    }
    return 0;
}
