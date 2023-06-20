#include <iostream>
#include <cmath>

using namespace std;

inline double asm_double_f1(double x)
{
	double res(0);
	__asm {
		fld x        // st0 = x
		fldz         // st0 = 0, st1 = x
		fcomip st, st(1)
		jae iff      // Если 0 >= x, то iff
		fld1         // st0 = 1, st1 = x
		fcomip st, st(1)
		jb iff       // Если 1 < x, то iff

		fmul x       // st0 = x ^ 2
		fsub x       // st0 = st0 - x = x2 - x

		jmp endif

	iff:
		fmul x      // st0 = x ^ 2
		fldpi       // st0 = pi, st1 = x ^ 2
		fmulp st(1), st       // st1 = st1 * st0 = pi * x ^ 2 (потом в st0)
		fsin        // st0 = sin(pi*x ^ 2)
		fld x       // st0 = x, st1 = sin(pi*x ^ 2)
		fmul x      // st0 = x ^ 2, st1 = sin(pi*x ^ 2)
		fsubrp st(1), st     // st1 = st0 - st1 = x - sin(pi*x ^ 2) (потом в st0)

		jmp endif

	endif:
		fstp res
	}
	return res;
}
inline double double_f1(double x)
{
	double res;
	if ((0 >= x) || (1 < x))
	{
		res = x * x - sin(atan(1) * 4 * x*x);
	}
	else { res = x * x - x; }

	return res;
}

inline double asm_double_f2_1(double x)
{
	double tf(25), ei(8), two(2), five(5), res(0);
	__asm {
		fld x			// st0 = x

		fld tf			// st0 = 25, st1 = x
		fcomip st, st(1)
		jb if1          // Если 25 < x, то

		fld ei			// st0 = 8, st1 = x
		fcomip st, st(1)
		jb if2          // Если 8 < x, то

		fld two			// st0 = 2, st1 = x
		fcomip st, st(1)
		jb if3          // Если 2 < x, то

		fldz            // st0 = 0, st1 = x
		fsubrp st(1), st          // st1 = st0 - st1 = 0 - x(РїРѕС‚РѕРј РІ st0)
		fldl2e          // st0 = log2(e), st1 = -x
		fmulp st(1), st           // st1 = -x * log2(e) (РїРѕС‚РѕРј РІ st0)
		fld st          // st0 = -x * log2(e), st1 = -x * log2(e)
		frndint         // st0 = int(-x * log2(e)), st1 = -x * log2(e)
		fsub st(1), st  // st0 = int(-x * log2(e)), st1 = -x * log2(e) - int(-x * log2(e))
		fxch            // st0 = -x * log2(e) - int(-x * log2(e)), st1 = int(-x * log2(e))
		f2xm1           // st0 = 2 ^ (-x * log2(e) - int(-x * log2(e))) - 1, st1 = int(-x * log2(e))
		fld1            // st0 = 1, st1 = 2 ^ (-x * log2(e) - int(-x * log2(e))) - 1, st2 = int(-x * log2(e))
		faddp st(1), st           // st0 = 2 ^ (-x * log2(e) - int(-x * log2(e))), st1 = int(-x * log2(e))
		fscale
		fstp st(1)	 
		fmul five		// st0 = 5 * e ^ (-x);

		jmp fin

	if1:
		fmul x			// st0 = x ^ 2
		fld1			// st0 = 1, st1 = x ^ 2
		faddp st(1), st			// st1 = st0 + st1 = 1 + x ^ 2 (потом в st0)

		jmp fin

	if2:
		fmul x			// st0 = x ^ 2
		fmul x			// st0 = x ^ 3
		fld1			// st0 = 1, st1 = x ^ 3
		faddp st(1), st			// st1 = st0 + st1 = 1 + x ^ 3 (потом в st0)
		fdiv x			// st0 = (1 + x ^ 3) / x

		jmp fin

	if3 :
		fmul x       // st0 = x ^ 2
		fld x        // st0 = x, st1 = x ^ 2
		fsqrt        // st0 = sqrt(x), st1 = x ^ 2
		fsubrp st(1), st      // st1 = st0 - st1 = sqrt(x) - x ^ 2 (потом в st0)

		jmp fin

	fin:
		fstp res
	}
	return res;
}
inline double double_f2_1(double x)
{
	double res;
	if (25 < x)
	{
		res = 1 + x * x;
	}
	else if (8 < x)
	{
		res = (1 / x) + x * x;
	}
	else if (2 < x)
	{
		res = sqrt(x) - x * x;
	}
	else
	{
		res = 5 * exp(-x);
	}
	return res;
}
inline double asm_double_f2_2(double x)
{
	double tf(25), ei(8), two(2), five(5), res(0);
	__asm {
		fld x			 // st0 = x

		fld tf			// st0 = 25, st1 = x
		fcomip st, st(1)
		jb if11          // Если 25 < x, то
		jmp next1

	if11:
		fmul x			// st0 = x ^ 2
		fld1            // st0 = 1, st1 = x ^ 2
		faddp st(1), st           // st1 = st0 + st1 = 1 + x ^ 2 (потом в st0)
		fstp res
		fld x


	next1:
		fld tf			// st0 = 25, st1 = x
		fcomip st, st(1)
		jae if21        // Если 25 >= x, то
		jmp next2
	if21 :
		fld ei			// st0 = 8, st1 = x
		fcomip st, st(1)
		jb if22         // Если 8 < x, то
		jmp next2

	if22:
		fmul x			// st0 = x ^ 2
		fmul x			// st0 = x ^ 3
		fld1            // st0 = 1, st1 = x ^ 3
		faddp st(1), st           // st1 = st0 + st1 = 1 + x ^ 3 (потом в st0)
		fdiv x			// st0 = (1 + x ^ 3) / x
		fstp res
		fld x


	next2:
		fld ei			// st0 = 8, st1 = x
		fcomip st, st(1)
		jae if31        // Если 8 >= x, то
		jmp next3
	if31:
		fld two			// st0 = 2, st1 = x
		fcomip st, st(1)
		jb if32         // Если 2 < x, то
		jmp next3

	if32:
		fmul x			// st0 = x ^ 2
		fld x			// st0 = x, st1 = x ^ 2
		fsqrt           // st0 = sqrt(x), st1 = x ^ 2
		fsubrp st(1), st          // st1 = st0 - st1 = sqrt(x) - x ^ 2 (потом в st0)
		fstp res
		fld x


	next3:
		fld two		   // st0 = 2, st1 = x
		fcomip st, st(1)
		jae if41       // Если 2 >= x, то
		jmp next4

	if41:
		fldz            // st0 = 0, st1 = x
		fsubrp st(1), st          // st1 = st0 - st1 = 0 - x(потом в st0)
		fldl2e          // st0 = log2(e), st1 = -x
		fmulp st(1), st           // st1 = -x * log2(e) (РїРѕС‚РѕРј РІ st0)
		fld st          // st0 = -x * log2(e), st1 = -x * log2(e)
		frndint         // st0 = int(-x * log2(e)), st1 = -x * log2(e)
		fsub st(1), st  // st0 = int(-x * log2(e)), st1 = -x * log2(e) - int(-x * log2(e))
		fxch            // st0 = -x * log2(e) - int(-x * log2(e)), st1 = int(-x * log2(e))
		f2xm1           // st0 = 2 ^ (-x * log2(e) - int(-x * log2(e))) - 1, st1 = int(-x * log2(e))
		fld1            // st0 = 1, st1 = 2 ^ (-x * log2(e) - int(-x * log2(e))) - 1, st2 = int(-x * log2(e))
		faddp st(1), st           // st0 = 2 ^ (-x * log2(e) - int(-x * log2(e))), st1 = int(-x * log2(e))
		fscale
		fstp st(1)
		fmul five
		fstp res

	next4:

	}
	return res;
}
inline double double_f2_2(double x)
{
	double res;

	if (25 < x) { res = 1 + x * x; }

	if (25 >= x && 8 < x) { res = (1 / x) + x * x; }

	if (8 >= x && 2 < x) { res = sqrt(x) - x * x; }

	if (2 >= x) { res = 5 * exp(-x); }

	return res;
}

inline double asm_double_f3(double m, double n, double p)
{
	double res(0);
	__asm {
		fld m			// st0 = m
		fld st          // st0 = m, st1 = m
		frndint         // st0 = int(m), st1 = m
		fsubp st(1), st           // st1 = st1 - st0 = m - int(m)(потом в st0)
		fldz            // st0 = 0, st1 = m - int(m)
		fcomip st, st(1)
		jne do1         // Если 0 != m - int(m), то

		fld1
		fadd res
		fstp res

	do1:
		finit
		fld n			// st0 = n
		fld st          // st0 = n, st1 = n
		frndint         // st0 = int(n), st1 = n
		fsubp st(1), st           // st1 = st1 - st0 = n - int(n)(потом в st0)
		fldz            // st0 = 0, st1 = n - int(n)
		fcomip st, st(1)
		jne do2         // Если 0 != n - int(n), то

		fld1
		fadd res
		fstp res

	do2:
		finit
		fld p			// st0 = p
		fld st          // st0 = p, st1 = p
		frndint         // st0 = int(p), st1 = p
		fsubp st(1), st           // st1 = st1 - st0 = p - int(p)(потом в st0)
		fldz            // st0 = 0, st1 = p - int(p)
		fcomip st, st(1)
		jne do3         // Если 0 != p - int(p), то

		fld1
		fadd res
		fstp res

	do3:
	}
	return res;
}
inline double double_f3(double m, double n, double p)
{
	int res = 0;
	if ((m - int(m)) == 0) { ++res; }
	if ((n - int(n)) == 0) { ++res; }
	if ((p - int(p)) == 0) { ++res; }
	return res;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double *a = new double[7]{ -2, -1, -0.5, 0, 0.5, 1, 2 };
	cout << "Задание №1." << endl;
	for (int i = 0; i < 7; ++i)
	{
		cout << a[i] << ":  " << (double_f1(a[i]) - asm_double_f1(a[i]) < 0.001) << endl;
	}
	delete[] a;

	a = new double[9]{ -4, 0, 2, 4, 8, 10, 25, 26, 30 };
	cout << "Задание №2." << endl;
	for (int i = 0; i < 9; ++i)
	{
		cout << a[i] << endl;
		cout << "   - Полное ветвление:    " << (double_f2_1(a[i]) - asm_double_f2_1(a[i]) < 0.001) << endl;
		cout << "   - Неволное ветвление:  " << (double_f2_2(a[i]) - asm_double_f2_2(a[i]) < 0.001) << endl;
	}
	delete[] a;

	cout << "Задание №3." << endl;
	double m, n, p;
	cout << " Введите m: "; cin >> m;
	cout << " Введите n: "; cin >> n;
	cout << " Введите p: "; cin >> p;

	cout << " Количество: " << double_f3(m, n, p) << "; " << asm_double_f3(m, n, p) << '.' << endl;

	return 0;
}

