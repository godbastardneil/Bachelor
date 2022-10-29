#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector<int> add_gen(const int &n)
{
    int m = 4096;
    std::vector<int> res(n, 0);
    res[0] = 4003;
    res[1] = 59;
    for (int i=2; i<n; ++i)
    {
        res[i] = (res[i-1]+res[i-2])%m;
    }

    return res;
}
string crypt(const string &str, const std::vector<int> &key)
{
    string res(str.size(), ' ');
    for (int i=0; i<str.size(); ++i)
    {
        res[i] = (str[i])^(key[i%key.size()]) + '\0';
    }
    return res;
}
string decrypt(const string &cry, const std::vector<int> &key)
{
    string res(cry.size(), ' ');
    for (int i=0; i<cry.size(); ++i)
    {
        res[i] = (cry[i])^(key[i%key.size()]) + '\0';
    }
    return res;
}

int main()
{
    string str;
    std::vector<int> key;

    cout << "Введите строку: ";
    cin >> str;
    key = add_gen(str.size());
    cout << "Ключ:";
    for (int i: key) { cout << ' ' << i; }
    cout << endl;

    string cry = crypt(str, key);
    string dec = decrypt(cry, key);

    cout << "Зашифрованная строка: " << cry << endl;
    cout << "Расшифрованная строка: " << dec << endl;

    return 0;
}
