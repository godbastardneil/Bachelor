#include <iostream>

using namespace std;

#include <random>
#include <algorithm>
#include <vector>
#include <fstream>

using rebro = pair<int, int>;

static std::random_device rd;
static std::mt19937 mt(rd());


std::vector<std::vector<bool>> create_smeh_matr(const int &n, const int &m, std::vector<int> &step_ver)
{
    std::vector<std::vector<bool>> res;
    for (int i=0; i<n; ++i) { res.push_back(std::vector<bool>(n, 0)); }

    for (int i=0; i<n; ++i) { step_ver[i] = 0; } // обнуляем степени вершин и считаем заново

    int ai;
    int bi;
    for (int i=0; i<n; ++i)
    {
        ai = i;
        do {
            do { bi = mt()%n; } while (ai == bi);

        } while (res[ai][bi] == 1);
        res[ai][bi] = 1;
        res[bi][ai] = 1;

        // считаем степени вершин ai, bi
        ++step_ver[ai];
        ++step_ver[bi];
    }
    for (int i=n; i<m; ++i)
    {
        ai = mt()%n;
        do {
            do { bi = mt()%n; } while (ai == bi);

        } while (res[ai][bi] == 1);
        res[ai][bi] = 1;
        res[bi][ai] = 1;

        // считаем степени вершин ai, bi
        ++step_ver[ai];
        ++step_ver[bi];
    }
    return res;
}


void sort_rebra(std::vector<rebro> &A)
{
    rebro key;
    int i = 0;
    for (size_t j=1; j<A.size(); ++j)
    {
        key = A[j];
        i = j-1;
        while((i >= 0) && ((A[i].first>key.first) || ((A[i].first == key.first) && (A[i].second > key.second))))
        {
            A[i+1] = A[i];
            i = i-1;
            A[i+1]=key;
        }
    }
}
std::vector<rebro> create_rebra(const std::vector<std::vector<bool>> &A, const int &n, std::vector<int> &step_ver)
{
    std::vector<rebro> res;

    for (size_t i=0; i<step_ver.size(); ++i) { step_ver[i] = 0; }

    for (int i=0; i<n; ++i)
    {
        for (int j=i+1; j<n; ++j)
        {
            if (A[i][j] == 1)
            {
                res.push_back(rebro(i, j));

                // считаем степени вершин ai, bi
                ++step_ver[i];
                ++step_ver[j];
            }
        }
    }
    sort_rebra(res); // сортируем
    return res;
}
std::vector<std::vector<bool>> create_inc(const std::vector<rebro> &A, const int &n, std::vector<int> &step_ver)
{
    std::vector<std::vector<bool>> res;
    int m = A.size();
    for (int i=0; i<n; i++) { res.push_back(std::vector<bool>(m, 0)); }

    for (size_t i=0; i<step_ver.size(); ++i) { step_ver[i] = 0; }

    for (int i=0; i<m; ++i)
    {
        res[A[i].first][i] = 1;
        res[A[i].second][i] = 1;

        // считаем степени вершин ai, bi
        ++step_ver[A[i].first];
        ++step_ver[A[i].second];
    }
    return res;
}

void cout_smeh_matr(const std::vector<std::vector<bool>> &A)
{
    ofstream file ("Graph.txt");
    int n = A.size();
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cout << A[i][j] << ' ';
            file << A[i][j] << ' ';
        }
        cout << endl;
        file << endl;
    }
    file.close();
}
void cout_rebra(const std::vector<rebro> &A)
{
    ofstream file ("Graph1.txt");
    int n = A.size();
    for (int i=0; i<n; ++i)
    {
        cout << "(" << A[i].first << ", " << A[i].second << "), ";
        file << "(" << A[i].first << ", " << A[i].second << "), ";
    }
    file.close();
    cout << endl;
}
void cout_inc(const std::vector<std::vector<bool>> &A)
{
    ofstream file ("Graph2.txt");
    int n = A.size();
    int m = A[0].size();
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cout << A[i][j] << ' ';
            file << A[i][j] << ' ';
        }
        cout << endl;
        file << endl;
    }
    file.close();
}


void cout_step_ver(const std::vector<int> &A)
{
    ofstream file ("Degree.txt");
    int n = A.size();
    for (int i=0; i<n; ++i)
    {
        cout << A[i] << " ";
        file << A[i] << " ";
    }
    file << endl;
    cout << endl;
    file.close();
}
void compare_step_ver(const std::vector<int> &A)
{
    ifstream file ("Degree.txt");
    int n = A.size();
    int k = 0;
    for (int i=0; i<n; ++i)
    {
        file >> k;
        if (k == A[i])
        {
            cout << 1;
        } else { cout << 0; }
    }
    cout << endl;
    file.close();
}

void check_teorema(const std::vector<int> &A, const int &m)
{
    ofstream file ("Degree.txt", ios_base::app);
    int count = 0;
    for (size_t i=0; i<A.size(); ++i) { count += A[i]; }
    cout << "Теорема №1. Сумма степеней всех его вершин равна удвоенному числу рёбер графа." << endl;
    cout << count << " / " << m << " = " << (count/m) << endl;

    cout << "Теорема №2. Сумма степеней всех его вершин - число чётное." << endl;
    cout << count << "%2 = " << (count%2) << endl;


    file << "Теорема №1. Сумма степеней всех его вершин равна удвоенному числу рёбер графа." << endl;
    file << count << " / " << m << " = " << (count/m) << endl;

    file << "Теорема №2. Сумма степеней всех его вершин - число чётное." << endl;
    file << count << "%2 = " << (count%2) << endl;
    file.close();
}

int main()
{
    int n = /*20+mt()%*/10; // количество вершин

    uniform_int_distribution<int> Mm(n, (n*(n-1)/2));
    int m = Mm(mt); // количество рёбер

    std::vector<int> step_ver(n, 0); // степени вершин


    std::vector<std::vector<bool>> smeh_matr = create_smeh_matr(n, m, step_ver); // список рёбер
    cout << "smeh_matr" << endl;
    cout_smeh_matr(smeh_matr); // выводим рёбра

    cout << "step_ver" << endl;
    cout_step_ver(step_ver); // выводим степени вершин
    check_teorema(step_ver, m);
    compare_step_ver(step_ver); // сравниваем степени вершин с тем, что в файле



    std::vector<rebro> rebra = create_rebra(smeh_matr, n, step_ver); // список рёбер
    cout << "rebra" << endl;
    cout_rebra(rebra); // выводим рёбра

    cout << "step_ver" << endl;
    cout_step_ver(step_ver); // выводим степени вершин
    compare_step_ver(step_ver); // сравниваем степени вершин с тем, что в файле



    std::vector<std::vector<bool>> incidents = create_inc(rebra, n, step_ver); // матрица инцидентности графа
    cout << "incidents" << endl;
    cout_inc(incidents); // выводим инцидентность

    cout << "compare_step_ver" << endl;
    compare_step_ver(step_ver); // сравниваем степени вершин с тем, что в файле

    return 0;
}
