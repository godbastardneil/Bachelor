#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include "windows.h"
#include "cpu.h"

using namespace std;

 // загрузчик программы для виртуальной машины
bool uploader(CPU &processor, const string &filename)
{
    ifstream file(filename);
    if(!file.is_open()) { return false; }

    // текущий адрес, адрес загрузки
    address curraddress = 0;

    char type = ' '; // тип операции

    while(type != 'e') // 'e' - команда остановки считывания
    {
        string s;
        getline(file, s); // получение строки ассемблера

        stringstream ss(s);
        ss >> type;
        switch(type)
        {
            case 'a': // установка базового адреса загрузки
            {
                ss >> curraddress;
                break;
            }
            case 'i': // загрузка целого знакового числа
            {
                DataType num;
                ss >> num.intEl;
                processor.memory.push_memory(num, curraddress);
                ++curraddress;
                break;
            }
            case 'u': // загрузка целого беззнакового числа
            {
                DataType num;
                ss >> num.uintEl;
                processor.memory.push_memory(num, curraddress);
                ++curraddress;
                break;
            }
            case 'f': // загрузка дробного числа
            {
                DataType num;
                ss >> num.flEl;
                processor.memory.push_memory(num, curraddress);
                ++curraddress;
                break;
            }
            case 'r': // команда загрузки адресного регистра
            {
                DataType cmd;
                uint16_t bufLoad;

                ss >> bufLoad;
                cmd.anyCommand.cmdAR.opcode = uint8_t(bufLoad);
                ss >> bufLoad;
                cmd.anyCommand.cmdAR.r1 = uint8_t(bufLoad);
                ss >> bufLoad;
                cmd.anyCommand.cmdAR.addr = bufLoad;
                processor.memory.push_memory(cmd, curraddress);
                ++curraddress;
                break;
            }
            case 'c': // загрузка команды процессора
            {
                DataType cmd;
                uint16_t bufLoad;

                ss >> bufLoad;
                cmd.anyCommand.cmdU.opcode = uint8_t(bufLoad);
                ss >> bufLoad;
                cmd.anyCommand.cmdU.r1 = uint8_t(bufLoad);
                ss >> bufLoad;
                cmd.anyCommand.cmdU.r2 = uint8_t(bufLoad);
                ss >> bufLoad;
                cmd.anyCommand.cmdU.r3 = uint8_t(bufLoad);
                processor.memory.push_memory(cmd, curraddress);
                ++curraddress;
                break;
            }
            case 'e': // остановка считывания, программный код загружен
            {
                DataType cmd;

                cmd.anyCommand.cmdU.opcode = 0; // комнда стоп
                processor.memory.push_memory(cmd, curraddress);

                address IP;
                ss >> IP;
                processor.PSW.ip = IP;
                break;
            }
        }
    }
    //system("pause");
    file.close();

    return true;
}

int main(int argc, char* argv[])
{
    //system("chcp 1251 > nul");

    CPU processor;
    CPU proc;
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
    //system("pause");

    return 0;
}
