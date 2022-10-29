#include <iostream>

using namespace std;

#include <random>
#include <algorithm>
#include <vector>
#include <stack>

static std::random_device rd;
static std::mt19937 mt(rd());


std::vector<std::vector<bool>> spisok_adj(const int &n)
{
    std::vector<std::vector<bool>> v (n, vector<bool>(n, 0));

    uniform_int_distribution<int> Mm(std::ceil(n/2.0), n-1);
    uniform_int_distribution<int> J(0, n-1);

    int j;
    for (int i=0; i<n; ++i)
    {
        int m = Mm(mt); // количество рёбер
        int k = std::count(v[i].begin(), v[i].end(), 1);

        while(k < m)
        {
            do {
                j = J(mt);
            } while (j == i || v[i][j] == 1);

            v[i][j] = v[j][i] = 1;
            ++k;
        }
    }
    return v;
}
void cout_adj(const std::vector<std::vector<bool>> &A)
{
    cout << "adj" << endl;
    cout << "   ";
    for (size_t i=0; i<A.size(); ++i) { cout << " " << i; }
    cout << endl;
    cout << "   ";
    for (size_t i=0; i<A.size(); ++i) { cout << " -"; }
    cout << endl;

    for (size_t i=0; i<A.size(); ++i)
    {
        cout << i << "---";
        for (size_t j=0; j<A[i].size(); ++j) { cout << A[i][j] << ' '; }
        cout << endl;
    }
}

void find_gam_perem(const std::vector<std::vector<bool>> &A, const int &n)
{
    vector<int> v;
    for (int i=0; i<n; ++i) { v.push_back(i); }

    bool valid;
    do
    {
        valid = true;
        for (int i=0; i<n-1 && valid == true; ++i)
        {
            if (A[v[i]][v[i+1]] == false) { valid = false; }
        }
    } while (next_permutation(v.begin(), v.end()) && !valid);

    if (valid)
    {
        cout << v[n-1];
        for (int k=0; k<n; ++k) { cout << v[k]; }
        cout << endl;
    } else { cout << "НЕТУ" << endl; }
}


bool dfs(const int &j, stack<int> &v, vector<int> &label, const int &k, const std::vector<std::vector<bool>> &A, const int &n)
{
    if (k == n)
    {
        v.push(j);
        return true;
    }

    for (int i=0; i<n; ++i)
    {
        if (A[j][i] && label[i] == 0)
        {
            label[i]=1;
            if (dfs(i, v, label, k+1, A, n))
            {
                v.push(j);
                return true;
            }
            label[i]=0;
        }

    }
    return false;
}
void find_gam_dfs(const std::vector<std::vector<bool>> &adj, const int &n)
{
    stack<int> v;
    vector<int> label;
    for (int i=0; i<n; ++i) { label.push_back(0); }

    v.push(0);
    label[0] = 1;
    if (dfs(0, v, label, 1, adj, n))
    {
        while (!v.empty())
        {
            cout << v.top();
            v.pop();
        }
        cout << endl;
    }
}

int main()
{
    int n = 10;
    std::vector<std::vector<bool>> adj = spisok_adj(n);
    cout_adj(adj);

    cout << "Гамильтонов цикл перемешиванием: "; find_gam_perem(adj, n);

    cout << "Гамильтонов цикл в глибину:      "; find_gam_dfs(adj, n);

    cout << "ВСЕ!" << endl;

    return 0;
}
