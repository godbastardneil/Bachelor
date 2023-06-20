#include "stdafx.h"
#include "complex.h"

std::wstring complex::to_String() const noexcept
{
	return (std::to_wstring(a) + L" + " + std::to_wstring(b) + L"*i");
}


complex& complex::operator+=(const complex &sec) noexcept
{
	a += sec.a;
	b += sec.b;
	return *this;
}
complex& complex::operator-=(const complex &sec) noexcept
{
	a -= sec.a;
	b -= sec.b;
	return *this;
}
complex& complex::operator*=(const complex &sec) noexcept
{
	int A = (a * sec.a) - (b * sec.b);
	b = (a * sec.b) + (b * sec.a);
	a = A;
	return *this;
}
complex& complex::operator/=(const complex &sec) noexcept
{
	int A = ((a * sec.a) + (b * sec.b)) / ((sec.a * sec.a) + (sec.b * sec.b));
	b = ((b * sec.a) - (a * sec.b)) / ((sec.a * sec.a) + (sec.b * sec.b));
	a = A;
	return *this;
}


complex operator+(const complex &fir, const complex &sec) noexcept
{
	complex tmp = fir;
	tmp += sec;
	return tmp;
}
complex operator-(const complex &fir, const complex &sec) noexcept
{
	complex tmp = fir;
	tmp -= sec;
	return tmp;
}
complex operator*(const complex &fir, const complex &sec) noexcept
{
	complex tmp = fir;
	tmp *= sec;
	return tmp;
}
complex operator/(const complex &fir, const complex &sec) noexcept
{
	complex tmp = fir;
	tmp /= sec;
	return tmp;
}


bool operator==(const complex &fir, const complex &sec) noexcept
{
	return ((fir.a == sec.a) && (fir.b == fir.b));
}
bool operator!=(const complex &fir, const complex &sec) noexcept
{
	return !(fir == sec);
}