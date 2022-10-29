#ifndef ALG_H
#define ALG_H

#include <vector>
#include <stack>
#include <algorithm>
#include <thread>

using namespace std;

int partition(vector<int> &str, const int &i1, const int &i2);
void rec_alg(vector<int> &str, const int &i1, const int &i2);
void norec_alg(vector<int> &str);

void paral_alg(vector<int> &str, vector<thread> &thr);

void paral_gl_alg(vector<int> &str, const int &i1, const int &i2, int i, int m);

#endif // ALG_H
