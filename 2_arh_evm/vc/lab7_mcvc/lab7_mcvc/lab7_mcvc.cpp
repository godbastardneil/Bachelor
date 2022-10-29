#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

inline void asm_double_f1(double xn, double a, double h, double *y, int n)
{
	double znam = 0;
	unsigned int i = 0;
	double os(1.6), tn(2.9), ot(1.2);
	__asm {
		fld tn       // st0 = 2.9
		fmul a       // st0 = 2.9*a
		fadd ot      // st0 = 2.9*a + 1.2
		fstp znam    // znam = 2.9*a + 1.2

		mov ecx, n
		mov ebx, y

		cycl:
			fld xn       // st0 = xn
			fmul os      // st0 = 1.6*xn
			fmul a       // st0 = 1.6*xn*a
			fld xn       // st0 = xn, st1 = 1.6*xn*a
			fsqrt        // st0 = sqrt(xn), st1 = 1.6*xn*a
			faddp st(1), st        // st1 = st1 + st0 = 1.6*xn*a + sqrt(xn) (Потом в st0)

			fld znam     // st0 = znam, st1 = 1.6*xn*a + sqrt(xn)
			fdivp st(1), st        // st1 = st1 / st0 = (1.6*xn*a + sqrt(xn)) / znam(Потом в st0)
			fsqrt        // st0 = sqrt((1.6*xn*a + sqrt(xn)) / znam)

			fstp qword ptr[ebx]   // y = sqrt((1.6*xn*a + sqrt(xn)) / znam)
			add ebx, 8

			fld xn       // st0 = xn
			fadd h       // st0 = xn + h
			fstp xn      // xn = xn + h

			loop cycl    // Если n > 0, то
	}
}
inline void double_f1(double xn, double a, double h, double *y, int n)
{
	for (int i = 0; i < n; ++i)
	{
		y[i] = sqrt((1.6*a*xn + sqrt(xn)) / (2.9*a + 1.2));
		xn += h;
	}
}

inline void asm_double_f2a(double xn, double h, double *y, int n)
{
	double chis = 0;
	double one(1), four(4);
	double j = 1;
	int i = 0;
	__asm {
		mov ecx, 11
		mov ebx, y

		cycl1:
			mov i, ecx

			fld xn       // st0 = xn
			fstp chis    // chis = xn

			fld chis     // st0 = chis
			fstp qword ptr[ebx]  // y = chis

			fld1
			fstp j
			mov ecx, n

			cycl2:
				fld chis    // st0 = chis
				fmul xn     // st0 = chis * xn
				fmul xn     // st0 = chis * xn*xn
				fmul xn     // st0 = chis * xn*xn*xn
				fmul xn     // st0 = chis * xn*xn*xn*xn
				fstp chis   // chis = chis * xn*xn*xn*xn

				fld j       // st0 = j
				fmul four   // st0 = j * 4
				fadd one    // st0 = j * 4 + 1

				fld chis    // st0 = chis, st1 = j * 4 + 1

				fdivrp st(1), st      // st1 = st0 / st1 = chis / (j * 4 + 1) (Потом в st0)
				fadd qword ptr[ebx]       // st0 = y + chis / (4 * j + 1)
				fstp qword ptr[ebx]       // y = y + chis / (4 * j + 1)

				fld1
				fadd j
				fstp j

				loop cycl2        // Если n > 0, то

			fld xn       // st0 = xn
			fadd h       // st0 = xn + h
			fstp xn      // xn = xn + h

			add ebx, 8
			mov ecx, i

			loop cycl1      // Если i > 0, то
	}
}
inline void double_f2a(double xn, double h, double *y, int n)
{
	double chis;
	for (int i = 0; i < 11; ++i)
	{
		chis = xn;
		y[i] = chis;

		for (int j = 1; j <= n; ++j)
		{
			chis *= xn * xn*xn*xn;

			y[i] += chis / (4 * j + 1);
		}
		xn += h;
	}
}

inline void asm_double_f2b(double xn, double h, double *y, double e)
{
	double chis(0), s(0);
	double one(1), four(4);
	double j = 1;
	__asm {
		mov ecx, 11
		mov ebx, y

		cycl1 :

			fld xn       // st0 = xn
			fstp chis    // chis = xn

			fld chis     // st0 = chis
			fstp qword ptr[ebx]  // y = chis

			fld1
			fstp j

			cycl3 :
				finit
				fld chis    // st0 = chis
				fmul xn     // st0 = chis * xn
				fmul xn     // st0 = chis * xn*xn
				fmul xn     // st0 = chis * xn*xn*xn
				fmul xn     // st0 = chis * xn*xn*xn*xn
				fstp chis   // chis = chis * xn*xn*xn*xn

				fld j       // st0 = j
				fmul four   // st0 = j * 4
				fadd one    // st0 = j * 4 + 1

				fld chis    // st0 = chis, st1 = j * 4 + 1

				fdivrp st(1), st      // st1 = st0 / st1 = chis / (j * 4 + 1) (Потом в st0)
				fstp s		// y = chis / (4 * j + 1)
				fld s		// st0 = s
				fadd qword ptr[ebx]       // st0 = y + s
				fstp qword ptr[ebx]       // y = y + s

				fld1
				fadd j
				fstp j

				fld s		// st0 = s
				fld e		// st0 = e, st1 = s
				fcomip st, st(1)
				jb cycl3	// Если e < s, то

			fld xn       // st0 = xn
			fadd h       // st0 = xn + h
			fstp xn      // xn = xn + h

			add ebx, 8

			loop cycl1      // Если i > 0, то
	}
}
inline void double_f2b(double xn, double h, double *y, double e)
{
	double s;
	double chis;
	for (int i = 0; i < 10; ++i)
	{
		chis = xn;
		s = chis;
		y[i] = s;

		for (int j = 1; s > e; ++j)
		{
			chis *= xn * xn*xn*xn;

			s = chis / (4 * j + 1);

			y[i] += s;
		}
		xn += h;
	}
}

int main()
{
	cout << "1" << endl;
	double xn = 4.2;
	double xk = 6.0;
	double a = 0.1;
	int n = 10;
	double h = (xk - xn) / n;

	double *y1 = new double[10]{ 0,0,0,0,0,0,0,0,0,0 };
	double *y2 = new double[10]{ 0,0,0,0,0,0,0,0,0,0 };
	double_f1(xn, a, h, y1, n);
	asm_double_f1(xn, a, h, y2, n);

	for (int i = 0; i < 10; ++i)
	{
		assert(fabs(y1[i] - y2[i]) < 0.0001);
	}
	cout << endl;

	cout << "2a" << endl;
	xn = 0.1;
	xk = 0.8;
	h = (xk - xn) / 10;
	n = 10;

	delete[] y1;
	y1 = new double[11]{ 0,0,0,0,0,0,0,0,0,0,0 };
	delete[] y2;
	y2 = new double[11]{ 0,0,0,0,0,0,0,0,0,0,0 };

	double_f2a(xn, h, y1, n);
	asm_double_f2a(xn, h, y2, n);

	for (int i = 0; i < 11; ++i)
	{
		assert(fabs(y1[i] - y2[i]) < 0.0001);
	}
	cout << endl;

	cout << "2b" << endl;
	double e = 0.0001;

	double_f2b(xn, h, y1, e);
	asm_double_f2b(xn, h, y2, e);

	for (int i = 0; i < 11; ++i)
	{
		assert(fabs(y1[i] - y2[i]) < 0.0001);
	}
	cout << endl;

	return 0;

}
