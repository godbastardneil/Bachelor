#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <thread>

using namespace std;

pair<int, int> partition(vector<int> &str, const int &i1, const int &i2)
{
    int pivot = str[(i1+i2)/2];
    int i = i1;
    int j = i2;
    while (i <= j)
    {
        while (str[i] < pivot) { i++; }
        while (str[j] > pivot) { j--; }
        if (i<=j) { swap(str[i++], str[j--]); }
    }
    return pair<int, int>(i, j);
}
void rec_alg(vector<int> &str, const int &i1, const int &i2)
{
    if (i1 < i2)
    {
        pair<int, int> q = partition(str, i1, i2);

        rec_alg(str, i1, q.second);
        rec_alg(str, q.first, i2);
    }
}
void norec_alg(vector<int> &str)
{
    stack<pair<int, int>> s;
    s.push({0, str.size()-1});

    while (!s.empty())
    {
        pair<int, int> i = s.top(); s.pop();
        if (i.first < i.second)
        {
            pair<int, int> q = partition(str, i.first, i.second);
            s.push({i.first, q.second});
            s.push({q.first, i.second});
        }
    }
}

void paral_alg(vector<int> &str, vector<thread> &thr)
{
    int n = str.size();
    int m = thr.size();
    int s;
    if (m >= n)
    {
        s = 1;
        m = n;
    } else { s = n/m; }
    int m_ = m-1;

    vector<vector<int>> tmp(m);
    for (int i=0; i<m_; ++i)
    {
        tmp[i] = vector<int>(str.begin()+i*s, str.begin()+(i+1)*s);
        thr[i] = thread(rec_alg, ref(tmp[i]), 0, s-1);
    }
    tmp[m_] = vector<int>(str.begin()+s*m_, str.begin()+n);
    thr[m_] = thread(rec_alg, ref(tmp[m_]), 0, tmp[m_].size()-1);

    for (int i=0; i<m; ++i) { thr[i].join(); }

    vector<int> t_;
    for (int i=0; i<m_; ++i)
    {
        merge(tmp[i].begin(), tmp[i].end(),
                tmp[i+1].begin(), tmp[i+1].end(),
                back_inserter(t_));
        tmp[i+1] = t_;
        t_.clear();
    }
    str = tmp[m_];
}

void paral_gl_alg(vector<int> &str, int i1, int i2, int i, int m)
{
    if (i1 < i2)
    {
        pair<int, int> q = partition(str, i1, i2);

        if (i < m)
        {
            thread thr1(paral_gl_alg, ref(str), i1, q.second, i+1, m);
            thread thr2(paral_gl_alg, ref(str), q.first, i2, i+1, m);

            thr1.join();
            thr2.join();
        } else
        {
            rec_alg(str, i1, q.second);
            rec_alg(str, q.first, i2);
        }
    }

}

int init_menu()
{
    int m = -1;
    cout << "1. Статистика - Последовательная рекурсивная быстрая сортировка\n"
            << "2. Статистика - Последовательная нерекурсивная быстрая сортировка\n"
            << "3. Статистика - Параллельная быстрая сортировка №1\n"
            << "4. Статистика - Параллельная быстрая сортировка №2\n"
            << "5. Последовательная рекурсивная быстрая сортировка\n"
            << "6. Последовательная нерекурсивная быстрая сортировка\n"
            << "7. Параллельная быстрая сортировка №1\n"
            << "8. Параллельная быстрая сортировка №2\n"
            << "0. Выход\n";
    do {
        cout << "выберете пункт меню: ";
        cin >> m;
    } while (m < 0 || m > 8);

    return m;
}
void init_stat(const int &n, const int &m, const int &time, const int &i)
{
    std::ifstream in(string("/home/gbn/somethings/projects/KURS_PARAL/files/"+to_string(i)+".html"));

    if (in.is_open())
    {
        string line;
        string stat;
        while (getline(in, line)) { stat += line + '\n'; }
        in.close();

        string tmp = "<tr><td>"+to_string(n)+"</td>";
        int j = stat.find(tmp);
        int j_ = 0;
        if (i == 1 || i == 2)
        {
            if (j == -1)
            {
                while(stat.find("</tr>", j_) != std::string::npos) { j_ = stat.find("</tr>", j_)+5; }
                stat.insert(j_, tmp + "<td>" + to_string(time) + "</td></tr>");
            } else
            {
                j = j+8;
                j_ = stat.find("<td>", j)+4;
                stat.insert(j_, to_string(time)+" / ");
            }
        } else if (i == 3 || i == 4)
        {
            if (j == -1)
            {
                while(stat.find("</tr>", j_) != std::string::npos) { j_ = stat.find("</tr>", j_)+5; }

                for (int m_=0; m_<4; ++m_)
                {
                    if (m_ == m-1)
                    {
                        tmp += "<td>" + to_string(time) + "</td>";
                    } else { tmp += "<td></td>"; }
                }
                tmp += "</tr>";
                stat.insert(j_, tmp);
            } else
            {
                j = j+8;
                j_ = j;
                for (int m_=0; m_<4 && m_ != m; ++m_)
                {
                    j_ = stat.find("<td>", j_)+4;
                }
                int _j = stat.find("</td>", j_);
                tmp = to_string(time);
                if (_j != j_)
                {
                    tmp += " / ";
                }
                stat.insert(j_, tmp);
            }
        }
        std::ofstream out(string("/home/gbn/somethings/projects/KURS_PARAL/files/"+to_string(i)+".html")); // окрываем файл для записи
        if (out.is_open()) { out << stat << std::endl; }
        out.close();
    }
}


int main()
{
    int n = -1;
    int m = -1;
    char h = ' ';

    vector<int> str;

    std::mt19937 mt(static_cast<int>(time(nullptr)));

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    int menu = init_menu();
    while (menu != 0)
    {
        if (menu > 0 && menu < 5)
        {
            string str = "/usr/bin/x-www-browser file:///home/gbn/somethings/projects/KURS_PARAL/files/"+to_string(menu)+".html &";
            system(str.c_str());

        } else if (menu >= 5 && menu < 9)
        {
            do {
                cout << "введите количество элементов: ";
                cin >> n;
            } while (n < 10);
            str.resize(n);
            generate(str.begin(), str.end(), mt);

            if (menu == 5)
            {
                start = std::chrono::steady_clock::now();
                rec_alg(str, 0, n-1);
            } else if (menu == 6)
            {
                start =  std::chrono::steady_clock::now();
                norec_alg(str);
            } else if (menu == 7)
            {
                do {
                    cout << "введите количество потоков (2, 4, 8, 16): ";
                    cin >> m;
                } while (m != 2 && m != 4 && m != 8 && m != 16);
                vector<thread> thr = vector<thread>(m);

                start =  std::chrono::steady_clock::now();
                paral_alg(str, thr);

                if (m == 2) { m  = 1; }
                else if (m == 4) { m = 2; }
                else if (m == 8) { m = 3; }
                else if (m == 16) { m = 4; }
            } else if (menu == 8)
            {
                do {
                    cout << "введите глубину (1, 2, 3, 4): ";
                    cin >> m;
                } while (m != 1 && m != 2 && m != 3 && m != 4);

                start =  std::chrono::steady_clock::now();
                paral_gl_alg(str, 0, n-1, 0, m);
            }
            end = std::chrono::steady_clock::now();
            std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            cout << "Время обработки массива " << menu << " - " << n << ": "
                 << elapsed.count() << endl;
            init_stat(n, m, elapsed.count(), menu-4);
        }
        cout << "Продолжить? (Y/N)";
        do {
            cin >> h;
        } while (h != 'Y' && h != 'N');
        if (h == 'Y')
        {
            menu = init_menu();
        } else { menu = 0; }
    }

    return 0;
}
