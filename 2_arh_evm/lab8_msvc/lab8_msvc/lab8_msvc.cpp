#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

double asm_length(double a[][3])
{
	double rez = 0;
	double d0(0), d(0);
	int n = 0;
	double a1, a0;
	__asm {
		mov ecx, 6
		mov eax, 0
		cycl1 :
			mov n, ecx

			mov ebx, a
			add ebx, eax

			fldz
			fstp d
			
			mov ecx, 3
			
			cycl2 :
				add ebx, 24
				fld qword ptr [ebx]

				sub ebx, 24
				fsub qword ptr[ebx]
				fstp d0

				fld d0
				fmul d0
				fadd d
				fstp d

				add ebx, 8
				loop cycl2
			fld d
			fsqrt
			fadd rez
			fstp rez

			add eax, 24
			mov ecx, n
			loop cycl1
	}
	return rez;
}
double length(double a[][3])
{
	double rez = 0;

	for (int i = 0; i < 6; ++i)
	{
		double d = 0;
		for (int j = 0; j < 3; ++j)
		{
			double d0 = a[i + 1][j] - a[i][j];
			d += d0 * d0;
		}
		rez += sqrt(d);
	}

	return rez;
}

double asm_max(double *mas, int n)
{
	double max(0);
	__asm {
		mov ecx, n
		mov ebx, mas
		fld qword ptr[ebx]
		fstp max

		add ebx, 8
		mov ecx, n
		cycl1 :
			finit

			fld max
			fld qword ptr[ebx]
			
			fcomi st, st(1)		// st0 = mas[i], st1 = max
			jbe if1				// mas[i] <= max

			fstp max

			if1:

			add ebx, 8
			loop cycl1
	}
	return max;
}
double max(double *mas, int n)
{
	double max = mas[0];

	for (int i = 1; i < n; ++i)
	{
		if (mas[i] > max) { max = mas[i]; }
	}

	return max;
}



int main()
{
	cout << "Задание №1" << endl;
	double a[7][3];
	for (int i = 0; i < 7; ++i)
	{
		cout << (i + 1) << endl;
		cout << "x: ";
		cin >> a[i][0];
		cout << "y: ";
		cin >> a[i][1];
		cout << "z: ";
		cin >> a[i][2];
	}
	assert(fabs(length(a) - asm_length(a)) < 0.0001);
	
	cout << "Задание №2" << endl;
	double *mas;
	int n;
	cout << " Введите n: ";
	cin >> n;

	mas = new double[n];
	for (int i = 0; i < n; ++i)
	{
		cout << i + 1 << ": ";
		cin >> mas[i];
	}
	assert(fabs(max(mas, n) - asm_max(mas, n)) < 0.0001);

	return 0;
}
