#pragma once

#include <random>
#include <fstream>
#include <ctime>
#include "Resource.h"
#include "complex.h"

#define qest 0		// количество заданий
#define prav 1		// количество правильных
#define prav_proz 2		// количество неправильных
#define neprav 3		// процент правильных
#define neprav_proz 4		// процент неправильных
#define otnoh 5		// отношение правильных к неправильным

#define psir 6		// серия правильных
#define npsir 7		// серия неправильных

#define spsrsir 8		// средняя серия правильных
#define snpsrsir 9		// средняя серия неправильных


#define c_hint 10		// количество подсказок
#define phint 11		// количество правильных с подсказкой
#define nphint 12		// количество неправильных с подсказкой

#define sk 13		// количество пропусков
#define rep 14		// количество повторов

class trenerovca
{
private:
	std::wstring name; // имя ползователя
	complex fir; // первое слагаемое
	complex sec; // второе слагаемое
	complex rez; // результат
	uint8_t i; // номер задания
	bool hint; // была использована подсказка или нет
	int ex; // тип тренеровки
	int e; // тип нынешнего задания
	float *stat; // статистические показатели, придумать нужно, что тут и сколько
	float ps; // текущая серия правильных
	float nps; // текущая серия неправильных
	float c_ps; // количество серий правильных ответов
	float c_nps; // количество серий правильных ответов

public:
	trenerovca()
	{
		name = L"user";
		i = 0;
		hint = false;
		e = 0;
		ps = 0;
		nps = 0;
		c_ps = 0;
		c_nps = 0;
		stat = new float[15]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		
	}

	inline void set_name(const std::wstring n) noexcept { name = n; } // установить подсказку
	inline void set_hint(const bool h) noexcept { hint = h; } // установить подсказку
	inline void set_ex(const int E) noexcept { ex = E; } // установить тип задания

	std::wstring get_i() noexcept { return std::to_wstring(i); } // подучить номер задания
	std::wstring get_hint() noexcept; // получить подсказку

	std::wstring create_ex() noexcept; // создание задания
	
	/*ПРОВЕРКА*/
	void checker(const bool check) noexcept;
	bool check_ans(const bool skip, int a = 0, int b = 0) noexcept;

	void dodel_stat(const bool skip) noexcept; // доделывание статистики - пункты, которые основываются на других пунктах
	void re() noexcept; // обнулить тренировку

	std::wstring get_stat(const bool skip) noexcept; // получить статистику за тренировку
	std::wstring get_all_stat() noexcept; // получить всю статистику
	
	void povtor() noexcept; // повтов
};