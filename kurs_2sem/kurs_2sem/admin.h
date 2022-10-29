#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include <fstream>
#include <iostream>
#include <vector>

void crypt (const std::string &file);
void decrypt (const std::string &file);

bool checkadmin (const std::string &in, const std::string &admin);
bool insys ();

void admin_work (const int &con);

#endif // ADMIN_H_INCLUDED
