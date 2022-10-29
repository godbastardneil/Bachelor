#include "command.h"

Command::~Command() {}

/* --------------------------КОМАНДЫ ВВОДА-ВЫВОДА------------------------- */

/*
 * команда ввода/вывода целых чисел,
 * операция конкретизируется значением первого регистра: 0 - ввод, 1 - вывод.
 */
void Iio::operator()(CPU &processor) noexcept
{
    DataType buf;
    if(!processor.get_cmd_r1())
    {
        std::cout << "\nВВОД int: ";
        std::cin >> buf.intEl;
        processor.memory.push_memory(buf, processor.get_cmdAR_address());
    }
    else
    {
        buf = processor.memory.pop_memory(processor.get_cmdAR_address());
        std::cout << "\nВЫВОД int: " << buf.intEl;
    }
}

/*
 * команда ввода-вывода вещественных чисел,
 * операция конкретизируется значением первого регистра: 0 - ввод, 1 - вывод.
 */
void Fio::operator()(CPU &processor) noexcept
{
    DataType buf;
    if(!processor.get_cmd_r1())
    {
        std::cout << "\nВВОД float: ";
        std::cin >> buf.flEl;
        processor.memory.push_memory(buf,processor.get_cmdAR_address());
    }
    else
    {
        buf = processor.memory.pop_memory(processor.get_cmdAR_address());
        std::cout << "\nВЫВОД float: " << buf.flEl;
    }
}

/*
 * ввод/вывод целого/дробного числа из регистра
 * в r1: 0 - ввод, 1 - вывод (ввод по адресу в регистре r3)
 * в r2: 0 - целое, 1 - дробное
 * в r3: номер выводимого регистра, регистра ввода
 */
void REGio::operator()(CPU &processor) noexcept
{
                                                 // 0/1
    addressReg print = processor.get_cmd_r1(),   // Ввод/вывод
            floating = processor.get_cmdU_r2(),  // Целое/дробное
            regNum = processor.get_cmdU_r3();    // Номер выводимого регистра
    DataType buf; // Переменная - буфер

    if(!print)
    {
       if(!floating)
       {
           std::cout << "\nВВОД int: ";
           std::cin >> buf.intEl;
           processor.memory.push_memory(buf, processor.addressRegister[regNum]);
       }
       else
       {
           std::cout << "\nВВОД float: ";
           std::cin >> buf.flEl;
           processor.memory.push_memory(buf, processor.addressRegister[regNum]);
       }
    }
    else
    {
        if(!floating)
        {
            buf = processor.memory.pop_memory(processor.addressRegister[regNum]);
            std::cout << "\nВЫВОД int: " << buf.intEl;
        }
        else
        {
            buf = processor.memory.pop_memory(processor.addressRegister[regNum]);
            std::cout << "\nВЫВОД float: " << buf.flEl;
        }
    }
}




/* ----------------------------КОМАНДЫ ПЕРЕСЫЛКИ-------------------------- */

// команда загрузки адресного регистра
void Load::operator()(CPU &processor) noexcept
{
    addressReg regNum = processor.get_cmd_r1(); // номер адресного регистра

    address address = processor.get_cmdAR_address(); // адрес памяти, куда надо загрузить значение регистра

    processor.addressRegister[regNum] = address; // Загрузка адреса в регистр
}
// есть тест
// команда сохранения адресного регистра в память
void Save::operator()(CPU &processor) noexcept
{
    addressReg regNum = processor.get_cmd_r1(); // номер адресного регистра

    address address = processor.get_cmdAR_address(); // адрес памяти, куда надо загрузить значение регистра

    // Загрузка в память адреса из адресного регистра
    DataType addressToUpload;
    addressToUpload.uintEl = processor.addressRegister[regNum];
    processor.memory.push_memory(addressToUpload, address);
}
// есть тест
// команда копирования/обмена адресными регистрами
void Swap::operator()(CPU &processor) noexcept
{
    addressReg cmdType = processor.get_cmd_r1(), // тип команды - обмен/копирование
            regNum1 = processor.get_cmdU_r2(),   // номер первого регистра
            regNum2 = processor.get_cmdU_r3();   // номер второго регистра

    // Копирование значений адресных регистров
    if(cmdType == 0)
    {
         processor.addressRegister[regNum2] = processor.addressRegister[regNum1];
    }

    // Обмен значениями адресных регистров
    if(cmdType == 1)
    {
        address addBuf = processor.addressRegister[regNum1];
        processor.addressRegister[regNum1] = processor.addressRegister[regNum2];
        processor.addressRegister[regNum2] = addBuf;
    }
}
// есть тест
// команда пересылки память-регистр
void Mov::operator()(CPU &processor) noexcept
{
    addressReg regNum = processor.get_cmd_r1(); // номер адресного регистра

    address addressCMD = processor.get_cmdAR_address(); // адрес памяти, откуда надо взять искомый адрес и загрузить в регистр

    // Загрузка в регистра адреса из памяти
    address addresToTransmit = processor.memory.pop_memory(addressCMD).addr;
    processor.addressRegister[regNum] = addresToTransmit;
}
// есть тест


/* --------------------------КОМАНДЫ АРИФМЕТИКИ--------------------------- */

/* **** КОМАНДЫ ЦЕЛОЧИСЛЕННОЙ АРИФМЕТИКИ **** */

// команда установки флаго
void ArithmInt::setFlags(CPU &processor) noexcept
{
    // адрес, лежащий в адресном регистре, номер которого указан в команде
    address address = processor.addressRegister[processor.get_cmd_r1()];

    // возврат значения из памяти по заданному адресу
    int32_t number = processor.memory.pop_memory(address).intEl;

    // Сравнение значения с нулём и установка флагов
    if (number == 0)
    {
        processor.PSW.flags.zf = 1;
    } else { processor.PSW.flags.zf = 0; }
    if (number < 0)
    {
        processor.PSW.flags.sf = 1;
    } else { processor.PSW.flags.sf = 0; }
}
// есть тест
//вычислительная команда
void ArithmInt::operator()(CPU &processor)
{
    // адрес, лежащий в адресном регистре
    address resultAddress = processor.addressRegister[processor.get_cmd_r1()];

    // адрес из первого регистра команды
    // адрес из второго регистра команды
    address paramAddress1 = processor.addressRegister[processor.get_cmdU_r2()],
            paramAddress2 = processor.addressRegister[processor.get_cmdU_r3()];

    // число из памяти, взятое по адресу из первого регистра
    // число из памяти, взятое по адресу из второго регистра
    int parametr1 = processor.memory.pop_memory(paramAddress1).intEl,
        parametr2 = processor.memory.pop_memory(paramAddress2).intEl;

    // Выполнение вычисления
    DataType result;
    result.intEl = calculation(parametr1, parametr2);
    processor.memory.push_memory(result, resultAddress);

    // Установка флагов по результатам выполнения команды
    setFlags(processor);
}
// есть тест


/* **** КОМАНДЫ ДРОБНОЙ АРИФМЕТИКИ **** */

//команда установки флагов
void ArithmFLong::setFlags(CPU &processor) noexcept
{
    // адрес, лежащий в адресном регистре, номер которого указан в команде
    address address = processor.addressRegister[processor.get_cmd_r1()];

    // дробное число взятое из памяти по адресу
    float number = processor.memory.pop_memory(address).flEl;

    // Сравнение числа с нулём и установка флагов
    if (fabsf(number) < 0.00001f)
    {
        processor.PSW.flags.zf = 1;
    } else { processor.PSW.flags.zf = 0; }
    if (number < 0)
    {
        processor.PSW.flags.sf = 1;
    } else { processor.PSW.flags.sf = 0; }
}
// есть тест
// вычислительная команда
void ArithmFLong::operator()(CPU &processor)
{
    // адрес, лежащий в адресном регистре, номер которого указан в команде
    address resultAddress = processor.addressRegister[processor.get_cmd_r1()];

    // адрес из первого регистра команды
    // адрес из второго регистра команды
    address paramAddress1 = processor.addressRegister[processor.get_cmdU_r2()],
            paramAddress2 = processor.addressRegister[processor.get_cmdU_r3()];

    // число из памяти, взятое по адресу из первого регистра
    // число из памяти, взятое по адресу из второго регистра
    float parametr1 = processor.memory.pop_memory(paramAddress1).flEl,
        parametr2 = processor.memory.pop_memory(paramAddress2).flEl;

    // Выполнение вычисления
    DataType result;
    result.flEl = calculation(parametr1, parametr2);
    processor.memory.push_memory(result, resultAddress);

    // Установка флагов по результатам выполнения команды
    setFlags(processor);
}
// есть тест


/* --------------------------АДРЕСНАЯ АРИФМЕТИКА-------------------------- */

//команда адресной арифметики (сложение/вычитание адресов)
void ArithmAddress::operator()(CPU &processor) noexcept
{
    // номер регистра, куда сохраняется результат вычисления нового адреса
    // первый регистр, откуда берётся адрес
    // второй регистр, откуда берётся адрес
    addressReg regResult = processor.get_cmd_r1(),
               regNum1 = processor.get_cmdU_r2(),
               regNum2 = processor.get_cmdU_r3();



    address parametr1 = processor.addressRegister[regNum1], // адрес из первого регистра
            parametr2 = processor.addressRegister[regNum2]; // адрес из второго регистра

    // новый вычисленный адрес
    address result = calculation(parametr1, parametr2);
    processor.addressRegister[regResult] = result;
}
// есть тест


/* ------------------АДРЕСНАЯ АРИФМЕТИКА СО СМЕЩЕНИЕМ--------------------- */

// команда адресной арифметика со смещением (сложение/вычитание адреса со смещения)
void ArithmOffset::operator()(CPU &processor) noexcept
{
    // номер адресного регистра в команде
    addressReg regNum = processor.get_cmd_r1();

    // базовый адрес из первого регистра команды
    address resultAddress = processor.addressRegister[regNum];

    // смещение из константного поля команды
    address replace = processor.get_cmdAR_address();

    // вычисление нового адреса
    address replacedAddress = calculation(resultAddress, replace);
    processor.addressRegister[regNum] = replacedAddress;
}
// есть тест



/* --------------------------КОМАНДЫ ПЕРЕХОДОВ---------------------------- */

void Jump::operator()(CPU &processor) noexcept
{
    jumpTo(processor);
}

//команда прямого перехода
void Jump::forwardJ(CPU &processor)
{
    // адрес из команды
    address address = processor.get_cmdAR_address();
    processor.PSW.ip = address - 1;
}
// команда ПРЯМОГО КОСВЕННОГО ПЕРЕХОДА
void Jump::forwardIndJ (CPU &processor)
{
    // адрес из константного поля команды
    address relAddress = processor.get_cmdAR_address();

    // адрес из памяти
    DataType address = processor.memory.pop_memory(relAddress);
    processor.PSW.ip = address.addr - 1;
}
// команда прямого косвенного регистрового перехода
void Jump::forwardIndRegJ (CPU &processor)
{
    addressReg regN2 = processor.get_cmdU_r2(), // номер второго регистра команды
               regN3 = processor.get_cmdU_r3(); // номер третьего регистра команды

    // адрес, который лежит в первом регистре
    // адрес, который лежит во втором регистре
    address address1 = processor.addressRegister[regN2],
            address2 = processor.addressRegister[regN3];

    processor.PSW.ip = address1 + address2 - 1;
}
// команда относительного перехода
void Jump::relativeJ (CPU &processor)
{
    address address = processor.get_cmdAR_address(); // смещение из команды
    processor.PSW.ip += address - 1;
}

// команда перехода
void Jump::go_to(CPU &processor) noexcept
{
    addressReg type = processor.get_cmd_r1(); // тип совершаемого перехода
    switch (type)
    {
        case 0: // Прямой переход
        {
            forwardJ(processor);
            break;
        }
        case 1: // Прямой косвенный
        {
            forwardIndJ(processor);
            break;
        }
        case 2: // Прямой косвенный регистровый
        {
            forwardIndRegJ(processor);
            break;
        }
        case 3: // Относительный
        {
            relativeJ(processor);
            break;
        }
    }
}



// команда перехода к подпрограмме (прямой переход)
void Call::jumpTo(CPU &processor) noexcept
{
    // номер адресного регистра из команды
    addressReg regNum = processor.get_cmd_r1();

    // Сохранение адреса возврата в адресный регистр
    processor.addressRegister[regNum] = processor.PSW.ip;

    // Прямой переход к подпрограмме
    forwardJ(processor);
}

// команда возврата из подпрограммы
void Return::jumpTo(CPU &processor) noexcept
{
    // номер адресного регистра, куда сохранён адрес возврата
    addressReg regNum = processor.get_cmd_r1();

    processor.PSW.ip = processor.addressRegister[regNum];
}

// команда безусловного перехода
void UJump::jumpTo(CPU &processor) noexcept
{
    go_to(processor);
}

// условный переход с проверкой флага нуля.
void ZFJump::jumpTo(CPU &processor) noexcept
{
    if (processor.PSW.flags.zf == 1) { go_to(processor); }
}
void NOTZFJump::jumpTo(CPU &processor) noexcept
{
    if (processor.PSW.flags.zf == 0) { go_to(processor); }
}

// условный переход с проверкой знака результата.
void SFJump::jumpTo(CPU &processor) noexcept
{
    if (processor.PSW.flags.sf == 1) { go_to(processor); }
}
void NOTSFJump::jumpTo(CPU &processor) noexcept
{
    if (processor.PSW.flags.sf == 0) { go_to(processor); }
}
