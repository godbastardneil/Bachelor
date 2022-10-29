#include <iostream>

using namespace std;

struct kal
{
    uint8_t days: 5; // 2^5 = 32, 0000 0000 0010 0000
    uint8_t month: 4; // 2^3 = 16, 0000 0000 0001 0000
    uint16_t year: 15; // 2^15 = 32768, 1000 0000 0000 0000
} __attribute__((packed));

int to_days(const kal &k) { return k.days+12*k.month+365*k.year; }


inline int asm_int_f(const int var, const int mask)
{
    int res; // результат
    asm (
        "\tmov eax, %[var]\n" // eax = var
        "\tmov ebx, %[mask]\n" // ebx = mask
        "\tand eax, ebx\n" // eax = eax & ebx
        "\tmov %[res], eax\n" // res = eax
        : [res]"=m"(res)
        : [var]"m"(var), [mask]"m"(mask)
    );
    return res;
}


int main()
{
// первое задание - Вариант №1. Написать программу компактного представления календарной даты с соответствующим набором констант
    kal k{0b010000, 0b01010, 0b0000011111010000}; // 16 день, 10 месяц, 2000 год

    printf("kol_day_bool = %d.\n", to_days(k) == 730136);
    printf("days_bool = %d.\n", k.days == 16);
    printf("month_bool = %d.\n", k.month == 10);
    printf("year_bool = %d.\n", k.year == 2000);

// второе задание - Вариат №1. Ислользуя операцию "логическое И", выделите первые три бита числа
    const int var1 = 0b00000111; // ожиается 0b00000111
    const int var2 = 0b11100101; // ожиается 0b00000101
    const int var3 = 0b10101001; // ожиается 0b00000001
    const int var4 = 0b11111111; // ожиается 0b00000111


    const int mask = 0b111; // 111 - первые три бита

    int res1 = var1 & mask; // == 0b00000111
    int res2 = var2 & mask; // == 0b00000101
    int res3 = var3 & mask; // == 0b00000001
    int res4 = var4 & mask; // == 0b00000111

    printf("r1_bool  = %d.\n", res1 == 0b00000111);
    printf("r2_bool  = %d.\n", res2 == 0b00000101);
    printf("r3_bool  = %d.\n", res3 == 0b00000001);
    printf("r4_bool  = %d.\n", res4 == 0b00000111);


    printf("asm_r1_bool  = %d.\n", asm_int_f(var1, mask) == res1);
    printf("asm_r2_bool  = %d.\n", asm_int_f(var2, mask) == res2);
    printf("asm_r3_bool  = %d.\n", asm_int_f(var3, mask) == res3);
    printf("asm_r4_bool  = %d.\n", asm_int_f(var4, mask) == res4);

    return 0;
}
