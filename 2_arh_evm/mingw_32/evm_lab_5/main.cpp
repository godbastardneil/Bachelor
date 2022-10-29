#include <iostream>
#include <cmath>

using namespace std;


inline double asm_double_f(const double x)
{
    double x2(0), e2x(0), znam(0), res(0), two(2);
    asm (
        R"(
            fld %[x]        # st0 = x
            fmul %[two]     # st0 = 2x
            fstp %[x2]      # x2 = 2x

            fld %[x2]       # st0 = x2
            fsincos         # st0 = cos(x2)
            #fld %[x2]      # st0 = x2, st1 = cos(x2)
            #fsin           # st0 = sin(x2)
            faddp           # st1 = st1+st0 = cos(x2)+sin(x2) (потом в st0)
            fadd %[two]     # st0 = sin(x2)+cos(x2)+two
            fstp %[znam]


            fld %[x2]       # st0 = x2
            fldl2e          # st0 = log2(e), st1 = x2
            fmulp           # st1 = st1*st0 = x2*log2(e) (потом в st0)
            fld ST          # st(0) = st(0), st(1) = st(0)
            frndint         # st(0) = int(st(0))
            fsub st(1), st  # st(1) = st(1) - st(0)
            fxch            # меняем местами st(0) и st(1)
            f2xm1           # st(0) = (2^st(0))-1
            fld1            # st(0) = 1, st(1) = (2^st(0))-1, st(2) =
            fadd st(1), st  # прибавляем 1, т.е возвращаем единичку обратно
            fscale          # теперь число в st(0) умножаем на 2^st(1)
            fmulp
            fstp st(1)      # функция fscale не выталкивает из стека значение порядка, делаем это вручную


            fld %[x2]       # загрузка x2 в st0
            fldl2e          # загрузка константы log2(e)
            fmulp           # st1 = st1*st0 = x2*log2(e) (потом в st0)
            fld ST          # загружаем копию из st0 => st0 = st0, st1 = st0, st2 = x2*log2(e)
            frndint         # st0 = int(st0)
            fsub st(1), st  # st1 = st1 - st0
            fxch            # меняем местами st(0) и st(1), таким образом в st(0) - дробная часть
            f2xm1           # возводим 2 в степень st(0) (где дробная часть) и отнимаем от результата 1
            fld1            # загружаем 1.0
            faddp           # прибавляем 1, т.е возвращаем единичку обратно
            fscale          # теперь число в st(0) умножаем на 2^st(1)
            fstp st(1)      # функция fscale не выталкивает из стека значение порядка, делаем это вручную
            fstp %[e2x]

            fld1            # загрузили 1.0 - нужна для fyl2x
            fld %[x2]       # загрузка x2 в st0
            fyl2x           # 1.0*log2(x2)
            fldln2          # константа перевода ln(2)
            fmulp           # ln(x2)

            fsub %[e2x]    # st1 = ln(x2)-e^2x (потом в st0)

            fld %[two]      # загрузка two в st0, а (ln(x2)-e^2x) в st1
            fxch            # st0 и st1 меняется местами
            fsubp           # st1 = st1-st0 = two-(ln(x2)-e^2x) (потом в st0)


            fld %[znam]     # st0 = znam, st1 = 2 - ln(2x)+e^2x
            fdivp           # st1 = st1 / st0 (потом в st0)
            fstp %[res]
        )"
        : [res]"=m"(res)
        : [x]"m"(x), [x2]"m"(x2), [e2x]"m"(e2x), [znam]"m"(znam), [two]"m"(two)
    );
    return res;
}
inline double double_f(double x) { return (2-log(2*x)+exp(2*x))/(2+cos(2*x)+sin(2*x)); }

int main()
{
    double df1 = double_f(1);
    double df3 = double_f(3);
    double df5 = double_f(5);
    double df7 = double_f(7);

    double adf1 = asm_double_f(1);
    double adf3 = asm_double_f(3);
    double adf5 = asm_double_f(5);
    double adf7 = asm_double_f(7);

    cout << "1 " << adf1 << "  " << df1 << endl;
    cout << "3 " << adf3 << "  " << df3 << endl;
    cout << "5 " << adf5 << "  " << df5 << endl;
    cout << "7 " << adf7 << "  " << df7 << endl;

    cout << "сравнение = " << (fabs(adf1 - df1) < 0.0001) << endl;
    cout << "сравнение = " << (fabs(adf3 - df3) < 0.0001) << endl;
    cout << "сравнение = " << (fabs(adf5 - df5) < 0.0001) << endl;
    cout << "сравнение = " << (fabs(adf7 - df7) < 0.0001) << endl;

    return 0;
}
