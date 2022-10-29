#include <iostream>

#include <random>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <chrono>

using namespace std;

using rebro = pair<int, int>;

static std::random_device rd;
static std::mt19937 mt(rd());

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

std::vector<std::vector<bool>> create_inc(const int &n, const int &m)
{
    std::vector<std::vector<bool>> A;
    for (int i=0; i<n; ++i) { A.push_back(std::vector<bool>(n, 0)); }
    std::vector<std::vector<bool>> res;
    std::vector<bool> r(m, 0);
    for (int i=0; i<n; i++) { res.push_back(r); }

    int ai;
    int bi;
    for (int i=0; i<n; ++i)
    {
        ai = i;
        do {
            do { bi = mt()%n; } while (ai == bi);

        } while (A[ai][bi] == 1);
        A[ai][bi] = 1;
        A[bi][ai] = 1;
    }
    for (int i=n; i<m; ++i)
    {
        ai = mt()%n;
        do {
            do { bi = mt()%n; } while (ai == bi);

        } while (A[ai][bi] == 1);
        A[ai][bi] = 1;
        A[bi][ai] = 1;
    }

    int k=0;
    for (int i=0; i<n; ++i)
    {
        for (int j=i+1; j<n; ++j)
        {
            if (A[i][j] == 1)
            {
                res[i][k] = 1;
                res[j][k] = 1;
                ++k;
            }
        }
    }
    return res;
}
std::vector<rebro> create_rebra(const std::vector<std::vector<bool>> &A, const int &n, const int &m)
{
    std::vector<rebro> res;

    int k = 0;
    for (int i=0; i<n; ++i)
    {
        for (int j=k; j<m && A[i][j] == 1; ++j)
        {
            int s = i+1;
            while (A[s][j] == 0) { ++s; }
            res.push_back(rebro(i, s));
            ++k;
        }
    }
    sort_rebra(res); // сортируем
    return res;
}

void cout_inc(const std::vector<std::vector<bool>> &A)
{
    ofstream file ("Graph.txt");
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
void cout_rebra(const std::vector<rebro> &A)
{
    ofstream file ("Graph1.txt");
    int n = A.size();
    cout << "rebra" << endl;
    file << "rebra" << endl;
    for (int i=0; i<n; ++i)
    {
        cout << "(" << A[i].first << ", " << A[i].second << "), ";
        file << "(" << A[i].first << ", " << A[i].second << "), ";
    }
    file << endl;
    cout << endl;
    file.close();
}



void deep_alg(ofstream &file, const std::vector<std::vector<bool>> &A, const int &i, const int &n)
{
    vector<int> nodes(n, 0);

    int m = A[i].size();
    int t = 0;

    stack<int> st;

    st.push(i);
    while(!st.empty())
    {
        t = st.top();
        st.pop();
        nodes[t] = 1;

        for (int j=0; j<m; ++j)
        {
            if (A[t][j] == 1)
            {
                for (int s=0; s<n; ++s)
                {
                    if (A[s][j] == 1 && s != t && nodes[s] == 0)
                    {
                        st.push(s); nodes[s] = 1;
                        s = n;
                    }
                }
            }
        }

        if (nodes[t] != 2)
        {
            cout << t << ' ';
            file << t << ' ';
        }
        nodes[t] = 2;
    }
    cout << "  -  ";
    file << "  -  ";
}
void detour_deep(const std::vector<std::vector<bool>> &A, const int &n)
{
    ofstream file("Graph.txt", ios_base::app);

    cout << "detour_deep" << endl;
    file << "detour_deep" << endl;

    auto mbegin = chrono::system_clock::now();
    for (int i=0; i<n; ++i)
    {
        auto mbegin = chrono::system_clock::now();

        deep_alg(file, A, i, n);

        auto mend = std::chrono::system_clock::now();
        auto mtime = std::chrono::duration_cast<std::chrono::nanoseconds>(mend - mbegin);

        cout << i << ". время: " << mtime.count() << endl;
        file << i << ". время: " << mtime.count() << endl;
    }
    auto mend = std::chrono::system_clock::now();
    auto mtime = std::chrono::duration_cast<std::chrono::nanoseconds>(mend - mbegin);

    cout << "Общее время: " << mtime.count() << endl;
    file << "Общее время: " << mtime.count() << endl;

    file.close();
}



void breadth_alg(ofstream &file, const std::vector<rebro> &A, const int &i, const int &n, int &res)
{
    vector<bool> nodes(n, 0);
    vector<int> d(n, 0);
    queue<int> qu;
    qu.push(i);
    int t = 0;
    while (!qu.empty())
    {
        t = qu.front();
        qu.pop();
        nodes[t] = 1;

        for (size_t j=0; j<A.size(); ++j)
        {
            if (A[j].first == t && nodes[A[j].second] == 0)
            {
                qu.push(A[j].second);
                nodes[A[j].second] = 1;
            }
            if (A[j].second == t && nodes[A[j].first] == 0)
            {
                qu.push(A[j].first);
                nodes[A[j].first] = 1;
            }
        }
        cout << t << ' ';
        file << t << ' ';
    }
    for (int j=0; j<n; ++j)
    {
        if (d[j] > res) { res = d[j]; }
    }
    cout << "  -  ";
    file << "  -  ";
}
void detour_breadth(const std::vector<rebro> &A, const int &n)
{
    ofstream file("Graph1.txt", ios_base::app);

    int res = 0;

    cout << "detour_breadth с поиском диаметра" << endl;
    file << "detour_breadth с поиском диаметра" << endl;


    auto mbegin = chrono::system_clock::now();
    for (int i=0; i<n; ++i)
    {
        auto mbegin = chrono::system_clock::now();

        breadth_alg(file, A, i, n, res);

        auto mend = std::chrono::system_clock::now();
        auto mtime = std::chrono::duration_cast<std::chrono::nanoseconds>(mend - mbegin);

        cout << i << ". время: " << mtime.count() << endl;
        file << i << ". время: " << mtime.count() << endl;
    }
    auto mend = std::chrono::system_clock::now();
    auto mtime = std::chrono::duration_cast<std::chrono::nanoseconds>(mend - mbegin);

    cout << "Общее время: " << mtime.count() << endl;
    file << "Общее время: " << mtime.count() << endl;

    cout << "Диаменр графа = " << res << endl;
    file << "Диаменр графа = " << res << endl;
    file.close();
}

int main()
{
    int n = /*20+mt()%*/10; // количество вершин/

    uniform_int_distribution<int> Mm(n, (n*(n-1)/2));
    int m = Mm(mt); // количество рёбер


    cout << "incidents" << endl;
    std::vector<std::vector<bool>> incidents = create_inc(n, m); // матрица инцидентности графа
    cout_inc(incidents); // выводим инцидентность
    detour_deep(incidents, n);

    std::vector<rebro> rebra = create_rebra(incidents, n, m); // список рёбер
    cout_rebra(rebra);
    detour_breadth(rebra, n);



    return 0;
}
