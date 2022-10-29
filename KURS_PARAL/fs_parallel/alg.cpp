
#include <vector>
#include <stack>
#include <algorithm>
#include <thread>

using namespace std;

int partition(vector<int> &str, const int &i1, const int &i2)
{
    int pivot = str[i1];
    int is = i1;
    for ( int i = i1+1; i<i2; ++i )
    {
        if ( str[i] <= pivot )
        {
            swap(str[++is], str[i]);
        }

    }
    swap(str[i1], str[is]);
    return is;
}
void rec_alg(vector<int> &str, const int &i1, const int &i2)
{
    if (i1 < i2)
    {
        int q = partition(str, i1, i2);

        rec_alg(str, i1, q);
        rec_alg(str, q+1, i2);
    }
}
void norec_alg(vector<int> &str)
{
    stack<pair<int, int>> s;
    s.push({0, str.size()});

    while (!s.empty())
    {
        pair<int, int> i = s.top(); s.pop();
        if (i.first < i.second)
        {
            int q = partition(str, i.first, i.second);
            s.push({i.first, q});
            s.push({q+1, i.second});
        }
    }
}

void paral_alg(vector<int> &str, vector<thread> &thr)
{
    int n = str.size();
    int m = thr.size();
    int m_ = m-1;
    int s = n/m;

    vector<vector<int>> tmp(m);
    for (int i=0; i<m_; ++i)
    {
        tmp[i] = vector<int>(str.begin()+i*s, str.begin()+(i+1)*s);
        thr[i] = thread(rec_alg, ref(tmp[i]), 0, s);
    }
    tmp[m_] = vector<int>(str.begin()+s*m_, str.begin()+n);
    thr[m_] = thread(rec_alg, ref(tmp[m_]), 0, tmp[m_].size());

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

void paral_gl_alg(vector<int> &str, const int &i1, const int &i2, int i, int m)
{
    if (i1 < i2)
    {
        int q = partition(str, i1, i2);

        if (i < m)
        {
            thread thr1(paral_gl_alg, ref(str), i1, q, i+1, m);
            thread thr2(paral_gl_alg, ref(str), q+1, i2, i+1, m);

            thr1.join();
            thr2.join();
        } else
        {
            paral_gl_alg(str, i1, q, i+1, m);
            paral_gl_alg(str, q+1, i2, i+1, m);
        }
    }

}
