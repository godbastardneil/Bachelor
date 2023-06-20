#include "command.h"


/* ------------------------ Команда ввода-вывода --------------------------- */
void io::operator()(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    const uint8_t r2_i = processor.get_cmd_r2();
//    const uint16_t bios = processor.get_cmd_bios();

    if (r2_i == 0) // Ввод Int
    {
        std::cin >> processor.ron[r1_i].Int;
    } else if (r2_i == 1) // Ввод UInt
    {
        std::cin >> processor.ron[r1_i].UInt;
    } else if (r2_i == 2) // Ввод Float
    {
        std::cin >> processor.ron[r1_i].Float;
    } else if (r2_i == 3) // Вывод Int
    {
        std::cout << "Result int: " << processor.ron[r1_i].Int << std::endl;
    } else if (r2_i == 4) // Вывод UInt
    {
        std::cout << "Result uint: " << processor.ron[r1_i].UInt << std::endl;
    }  else if (r2_i == 5) // Вывод Float
    {
        std::cout << "Result float: " << processor.ron[r1_i].Float << std::endl;
    }
}


/* ----------------- Команды управления адресным регистром ----------------- */
// Загрузка адресного регистра
void load::operator()(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    const uint8_t r2_i = processor.get_cmd_r2();
    const uint16_t bios = processor.get_cmd_offset();

    if (r2_i == 0)
    {
        processor.ron[r1_i].UInt = bios;
    } else if (r2_i == 1)
    {
        processor.ron[r1_i] = processor.ram.get_data(bios);
    }
}
// Сохранения адреса из адресного регистра в память
void save::operator()(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
//    const uint8_t r2_i = processor.get_cmd_r2();
    const uint16_t bios = processor.get_cmd_offset();

    processor.ram.push_memory(processor.ron[r1_i], bios);
}
// Обмен значениями между адресными регистрами
void exchange::operator()(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    const uint8_t r2_i = processor.get_cmd_r2();

    std::swap(processor.ron[r2_i], processor.ron[r1_i]);
}

/* --------------------- Команды знаковой целой арифметики ---------- */
void iMath::setFlags(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    if (processor.ron[r1_i].Int == 0)
    {
        processor.psw.flags.zf = 1;
    } else { processor.psw.flags.zf = 0; }
    if (processor.ron[r1_i].Int < 0)
    {
        processor.psw.flags.sf = 1;
    } else { processor.psw.flags.sf = 0; }
}
void iMath::operator()(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    const uint8_t r2_i = processor.get_cmd_r2();
    const uint16_t bios = processor.get_cmd_offset();

    int32_t r2 = processor.ron[r2_i].Int;

    const uint16_t address = (uint16_t(processor.ron[r1_i].UInt) + bios);
    int32_t r1_bios = processor.ram.get_data(address).Int;

    processor.ron[r1_i].Int = calculation(r2, r1_bios);
    setFlags(processor);
}

/* --------------------- Команды беззнаковой целой арифметики ---------- */
void uiMath::setFlags(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    if (processor.ron[r1_i].UInt == 0)
    {
        processor.psw.flags.zf = 1;
    } else { processor.psw.flags.zf = 0; }
    processor.psw.flags.sf = 0;
}
void uiMath::operator()(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    const uint8_t r2_i = processor.get_cmd_r2();
    const uint16_t bios = processor.get_cmd_offset();

    uint32_t r2 = processor.ron[r2_i].UInt;

    const uint16_t address = (uint16_t(processor.ron[r1_i].UInt) + bios);
    uint32_t r1_bios = processor.ram.get_data(address).UInt;

    processor.ron[r1_i].UInt = calculation(r2, r1_bios);
    setFlags(processor);
}

/* --------------------- Команды дробной арифметики ---------- */
void fMath::setFlags(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    if (fabsf(processor.ron[r1_i].Float) < 0.00001f)
    {
        processor.psw.flags.zf = 1;
    } else { processor.psw.flags.zf = 0; }
    if (processor.ron[r1_i].Float < 0)
    {
        processor.psw.flags.sf = 1;
    } else { processor.psw.flags.sf = 0; }
}
void fMath::operator()(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
    const uint8_t r2_i = processor.get_cmd_r2();
    const uint16_t bios = processor.get_cmd_offset();

    float r2 = processor.ron[r2_i].Float;

    const uint16_t address = (uint16_t(processor.ron[r1_i].UInt) + bios);
    float r1_bios = processor.ram.get_data(address).Float;

    processor.ron[r1_i].Float = calculation(r2, r1_bios);
    setFlags(processor);
}

/* --------------------------- Команды  переходов ---------------------------- */
void Jump::go_to(processor &processor) noexcept
{
    const uint8_t r1_i = processor.get_cmd_r1();
//    const uint8_t r2_i = processor.get_cmd_r2();
    const uint16_t bios = processor.get_cmd_offset();
    if (r1_i == 0)
    {
        processor.psw.ip = bios;
    } else if (r1_i == 1)
    {
        processor.psw.ip += bios;
    } else if (r1_i == 2)
    {
        processor.psw.ip -= bios;
    }
}

void Jump::operator()(processor &processor) noexcept
{
    jumpTo(processor);
}

void uncondJump::jumpTo(processor &processor) noexcept
{
    go_to(processor);
}
void zfJump::jumpTo(processor &processor) noexcept
{
    if (int(processor.psw.flags.zf) == 1) { go_to(processor); }
}
void sfJump::jumpTo(processor &processor) noexcept
{
    if (int(processor.psw.flags.sf) == 1) { go_to(processor); }
}
void nzfJump::jumpTo(processor &processor) noexcept
{
    if (int(processor.psw.flags.zf) == 0) { go_to(processor); }
}
void nsfJump::jumpTo(processor &processor) noexcept
{
    if (int(processor.psw.flags.sf) == 0) { go_to(processor); }
}
void callPr::jumpTo(processor &processor) noexcept
{
    processor.ron[7].UInt = processor.psw.ip;
    go_to(processor);
}
void returnPr::jumpTo(processor &processor) noexcept
{
    processor.psw.ip = uint16_t(processor.ron[7].UInt);
}
