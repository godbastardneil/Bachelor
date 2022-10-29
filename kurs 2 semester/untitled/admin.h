#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include <string>

using namespace std;

void crypt (const string &file);
void decrypt (const string &file);

bool checkadmin (const string &in, const string &admin);
bool insys ();

void admin_work (const int &con);

#endif // ADMIN_H_INCLUDED
