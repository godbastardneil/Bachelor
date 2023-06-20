#pragma once

#include <string>

using value = int;

class complex
{
private:
	value a; // вещественнная часть
	value b; // мнимая часть


public:
	complex(value A = 0, value B = 0) noexcept : a(A), b(B) {}
	complex(const complex &sec) noexcept : a(sec.a), b(sec.b) {}
	~complex() {}

	std::wstring to_String() const noexcept;

	value get_a() const noexcept { return a; }
	value get_b() const noexcept { return b; }
	void set_a(value A) noexcept { a = A; }
	void set_b(value B) noexcept { b = B; }

	complex& operator+=(const complex &sec) noexcept;
	complex& operator-=(const complex &sec) noexcept;
	complex& operator*=(const complex &sec) noexcept;
	complex& operator/=(const complex &sec) noexcept;

	friend complex operator+(const complex &fir, const complex &sec) noexcept;
	friend complex operator-(const complex &fir, const complex &sec) noexcept;
	friend complex operator*(const complex &fir, const complex &sec) noexcept;
	friend complex operator/(const complex &fir, const complex &sec) noexcept;

	friend bool operator==(const complex &fir, const complex &sec) noexcept;
	friend bool operator!=(const complex &fir, const complex &sec) noexcept;
};

