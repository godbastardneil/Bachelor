#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "processor.h"

using namespace std;


bool uploader(processor &proc, const string &fname)
{
    ifstream in(fname);
    if (!in.is_open()) { return false; }

    uint16_t address = 0;
    char t = ' ';

    while (t != 's')
    {
        string s;
        getline(in, s);
        stringstream ss(s);
        ss >> t;
        switch (t)
        {
            case 'a':
            {
                ss >> address;
                break;
            }
            case 'i':
            {
                DataType dt;
                ss >> dt.Int;
                proc.ram.push_memory(dt, address);
                address += sizeof(dt);
                break;
            }
            case 'u':
            {
                DataType dt;
                ss >> dt.UInt;
                proc.ram.push_memory(dt, address);
                address += sizeof(dt);
                break;
            }
            case 'f':
            {
                DataType dt;
                ss >> dt.Float;
                proc.ram.push_memory(dt, address);
                address += sizeof(dt);
                break;
            }
            case 'c':
            {
                CommandType ct;
                uint16_t tmp;
                ss >> tmp;
                ct.cmd.cop = uint8_t(tmp);
                ss >> tmp;
                ct.cmd.r1 = uint8_t(tmp);
                ss >> tmp;
                ct.cmd.r2 = uint8_t(tmp);
                ss >> tmp;
                ct.cmd.offset = (tmp);
                proc.ram.push_memory(ct, address);
                address += sizeof(ct);
                break;
            }
            case 's':
            {
                CommandType ct;
                ct.cmd.cop = 0;
                proc.ram.push_memory(ct, address);
                uint16_t tmp;
                ss >> tmp;
                proc.psw.ip = tmp;
                break;
            }
        }
    }
    in.close();
    return true;
}

int main(int argc, char* argv[])
{
    processor proc;
    if (argc>1)
    {
        cout << "\n File: " << argv[1];
        if (uploader(proc, argv[1]))
        {
            cout << "\n File uploaded" << std::endl;
            proc.run();
        } else { cout << "\n File not uploaded" << std::endl; }
    } else { cout << "\n Where is File" << std::endl; }
    cout << "\n End." << endl;
    system("pause");
    return 0;
}
