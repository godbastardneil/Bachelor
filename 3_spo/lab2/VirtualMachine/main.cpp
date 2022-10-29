#include "assembler.h"
#include "cpu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include "windows.h"

using namespace std;

// загрузчик программы для виртуальной машины
bool uploader(CPU &processor, const string &filename)
{
    ifstream file(filename, ios::binary);
    if(!file.is_open()) { return false; }

    // текущий адрес, адрес загрузки
    address curraddress = 0;

    char type = ' '; // тип операции

    while(type != 'e') // 'e' - команда остановки считывания
    {
        file >> type;
        switch(type)
        {
            case 'a': // установка базового адреса загрузки
            {
                file.read(reinterpret_cast<char*>(&curraddress), sizeof(address));
                std::cout << curraddress;
                break;
            }
            case 'i': // загрузка целого знакового числа
            case 'u': // загрузка целого беззнакового числа
            case 'f': // загрузка дробного числа
            {
                DataType num;
                file.read(reinterpret_cast<char*>(&num), sizeof(DataType));
                processor.memory.push_memory(num, curraddress);
                ++curraddress;
                break;
            }
            case 'r': // команда загрузки адресного регистра
            {
                DataType cmd;
                uint16_t bufLoad;

                file.read(reinterpret_cast<char*>(&bufLoad), sizeof(uint8_t));
                cmd.anyCommand.cmdAR.opcode = uint8_t(bufLoad);
                file.read(reinterpret_cast<char*>(&bufLoad), sizeof(uint8_t));
                cmd.anyCommand.cmdAR.r1 = uint8_t(bufLoad);
                file.read(reinterpret_cast<char*>(&bufLoad), sizeof(uint16_t));
                cmd.anyCommand.cmdAR.addr = bufLoad;
                processor.memory.push_memory(cmd, curraddress);
                ++curraddress;
                break;
            }
            case 'c': // загрузка команды процессора
            {
                DataType cmd;
                uint16_t bufLoad;

                file.read(reinterpret_cast<char*>(&bufLoad), sizeof(uint8_t));
                cmd.anyCommand.cmdU.opcode = uint8_t(bufLoad);
                file.read(reinterpret_cast<char*>(&bufLoad), sizeof(uint8_t));
                cmd.anyCommand.cmdU.r1 = uint8_t(bufLoad);
                file.read(reinterpret_cast<char*>(&bufLoad), sizeof(uint8_t));
                cmd.anyCommand.cmdU.r2 = uint8_t(bufLoad);
                file.read(reinterpret_cast<char*>(&bufLoad), sizeof(uint8_t));
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
                file.read(reinterpret_cast<char*>(&IP), sizeof(address));
                processor.PSW.ip = IP;
                break;
            }
        }
    }
    file.close();

    return true;
}

int main(int argc, char* argv[])
{
    //system("chcp 1251 > nul");

    CPU proc;
    if (argc>1)
    {
        std::string file = argv[1];

        cout << "\n File: " << file;
        assembler ass(file);

        file = file.substr(0, file.find_last_of('/'));
        file += "/programm.bin";
        cout << "\n File: " << file;

        ass.bin(file);

        if (uploader(proc, file))
        {
            cout << "\n File uploaded" << std::endl;
            proc.run();
        } else { cout << "\n File not uploaded" << std::endl; }
    } else { cout << "\n Where is File" << std::endl; }
    cout << "\n End." << endl;
    //system("pause");

    return 0;
}
