#include "print.h"
#include "stat.h"

#include "admin.h"

using namespace std;

const string adminpas = "adminpas";

void crypt (const string &file)
{
    ifstream in (file + ".txt");
    ofstream out (file + ".dat", ios::binary);
    string temp;
    while (getline(in, temp))
    {
        if (!in.eof()) { temp += "\r\n"; }
        for (char &i: temp) { i ^= 0xAABBC53; }
        out.write(temp.data(), temp.size());
    }
    in.close();
    out.close();
}
void decrypt (const string &file)
{
    ifstream in (file +".dat", ios::binary);
    ofstream out (file + ".txt", ios::binary);
    string temp;
    if (in) {
        getline(in, temp);
        for (char &i: temp) { i ^= 0xAABBC53; }
        out.write(temp.data(), temp.size());
    } else { cout << "Файл не найден" << endl; }
    in.close();
    out.close();
}

bool checkadmin (const string &in, const string &adminpas)
{
    size_t n = in.size();
    if (n != adminpas.size()) { return 0; }
    for (size_t i=0; i<n; i++) {
        if (adminpas[i] != in[i]) { return 0; }
    }
    return 1;
}
bool insys ()
{
    char c;
    string pas;
	int i = 0;
    cout << "\n Введите пароль: ";
    while ((c = getchar()) != 13) {
		if ((c != 8)) {
            pas.insert(pas.begin()+i, c);
            cout << "*";
            i++;
        } else if ((c == 8) && (i != 0)) {
            i--;
            pas.erase(pas.begin()+i, pas.end());
            cout << "\b \b";
        }
	}
	cout << endl;
	cin.clear();
    return checkadmin(pas, adminpas);
}

void admin_work (const int &con)
{
    system("chcp 1251 > nul");
    short int m_admin = 5;
    do {
        if (insys()) {
            system("cls");
            vector<string> AdminMenu = { "Редактировать теорию", "Редактировать тест", "Посмотреть статистику", "Очистить статистику", "Выйти" };
            Menu(m_admin, AdminMenu, con);
            gotoXY(0, 0);
            while (m_admin != 5)
            {
                string file = "";
                switch (m_admin)
                {
                case 1: {
                        file = "all_text";
                        decrypt(file);
                        cout << " Расшифровывается и открывается файл с теорией" << endl;
                        system((file+".txt").c_str());
                    break; }
                case 2: {
                        file = "all_test";
                        decrypt(file);
                        cout << " Расшифровывается и открывается файл с тестом" << endl;
                        system((file+".txt").c_str());
                    break; }
                break;
                case 3: {
                        init_stat(file, 1, con);
                    break; }
                case 4: {
                        ofstream stat ("all_stat.dat");
                        stat.close();
                        cout << " Удаляется содержание файла со статистикой" << endl;
                    }
                }
                cout << endl;
                system("pause");
                if (file.size() > 0) {
                    crypt(file);
                    remove((file+".txt").c_str());
                }
                system("cls");
                Menu(m_admin, AdminMenu, con);
            }
        }
    } while (m_admin != 5);
}
