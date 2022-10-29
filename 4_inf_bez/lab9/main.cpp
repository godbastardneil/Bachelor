#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

const string alf = "abcdefghijklmnopqrstuvwxyz ";


string crypt(const string &text, const vector<size_t> &K)
{
    string res(text.size(), 'a');

    vector<size_t> X(text.size());
    transform(text.begin(), text.end(), X.begin(),
                       [](unsigned char uc) { return alf.find(uc); });

    vector<size_t> Y(text.size());
    for (size_t i=0; i<text.size(); ++i)
    {
        Y[i] = (X[i] + K[i]) % alf.size();
    }

    transform(Y.begin(), Y.end(), res.begin(),
                [](size_t i) { return alf[i]; });

    return res;
}
string decrypt(const string &text, const vector<size_t> &K)
{
    string res(text.size(), 'a');

    vector<size_t> Y(text.size());
    transform(text.begin(), text.end(), Y.begin(),
                   [](unsigned char uc) { return alf.find(uc); });

    vector<size_t> X(text.size());
    for (size_t i=0; i<text.size(); ++i)
    {
        int x = int(Y[i] - K[i]) ;
        if (x < 0) { x += alf.size(); }
        X[i] = x % alf.size();
    }

    transform(X.begin(), X.end(), res.begin(),
                [](int
              i) { return alf[i]; });

    return res;
}

int main()
{
    string text;
    cout << "Введите текст: ";
    do {
        cin >> text;
    } while (text.size() == 0);

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<size_t> dist(0, alf.size() - 1);

    vector<size_t> K(text.size());
    generate(K.begin(), K.end(), [&](){  return dist(mt); } );

    cout << "Ключ:";
    for (int i: K) { cout << ' ' << i; }
    cout << endl;

    string cry = crypt(text, K);
    string decry = decrypt(cry, K);

    cout << "Зашифрованный: " << cry << endl;
    cout << "Расшифрованный: " << decry << endl;

    return 0;
}
