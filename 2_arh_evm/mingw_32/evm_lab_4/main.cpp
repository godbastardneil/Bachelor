#include <iostream>
#include <cmath>

using namespace std;


inline int asm_int_f(const int x)
{
    int zn, x2, res;
    asm (
        R"(
            mov eax, %[x]
            imul eax, eax
            mov %[x2], eax
            mov %[zn], eax
            mov eax, %[x]
            imul eax, 8

            sub %[zn], eax
            add %[zn], 12

            mov eax, %[x]
            imul eax, -7
            add eax, %[x2]
            add eax, 10
            cdq
            idiv %[zn]
            mov %[res], eax
        )"
        : [res]"=m"(res)
        : [x]"m"(x), [x2]"m"(x2), [zn]"m"(zn)
    );
    return res;
}
inline int int_f(const int x) { return (x*x-7*x+10)/(x*x-8*x+12); }

inline float asm_float_f(const float x)
{
    float znam(0), res(0);
    float f8(8), f12(12), f7(7), f10(10);
    asm (
        R"(
            fld %[x]        # st0 = x
            fsub %[f8]      # st0 = x-8
            fld %[x]        # st0 = x, st1 = x-8
            fmulp           # st0 = (x-8)*x
            fadd %[f12]     # st0 = (x-8)*x+12
            fstp %[znam]    # znam = (x-8)*x+12

            fld %[x]        # st0 = x
            fsub %[f7]      # st0 = x-7
            fld %[x]        # st0 = x, st1 = x-7
            fmulp           # st0 = (x-7)*x
            fadd %[f10]     # st0 = (x-7)*x+10

            fld %[znam]     # st0 = znam, st1 = (x-7)*x+10
            fdivp           # st1 = st1 / st0
            fstp %[res]
        )"
        : [res]"=m"(res)
        : [x]"m"(x), [znam]"m"(znam), [f8]"m"(f8), [f12]"m"(f12), [f7]"m"(f7), [f10]"m"(f10)
    );
    return res;
}
inline float float_f(const float x) { return (x*x-7*x+10)/(x*x-8*x+12); }

int main()
{
    cout << "сравнение = " << (asm_int_f(1) == int_f(1)) << endl;
    cout << "сравнение = " << (asm_int_f(20) == int_f(20)) << endl;
    cout << "сравнение = " << (asm_int_f(542) == int_f(542)) << endl;
    cout << "сравнение = " << (asm_int_f(1010) == int_f(1010)) << endl;

    cout << "сравнение = " << (fabs(asm_float_f(1) - float_f(1)) < 0.001f) << endl;
    cout << "сравнение = " << (fabs(asm_float_f(20) - float_f(20)) < 0.001f) << endl;
    cout << "сравнение = " << (fabs(asm_float_f(542) - float_f(542)) < 0.001f) << endl;
    cout << "сравнение = " << (fabs(asm_float_f(1010) - float_f(1010)) < 0.001f) << endl;

    return 0;
}
