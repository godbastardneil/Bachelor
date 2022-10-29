#include "stdafx.h"
#include "trenerovca.h"

std::wstring trenerovca::get_hint() noexcept
{
	std::wstring ws;
	hint = true;
	if (e == id_hBtn_Sum) // выбор подсказки
	{
		ws = L"(a + b*i) + (c + d*i) = (a + c) + (b + d)*i";
	}
	else if (e == id_hBtn_Min)
	{
		ws = L"(a + b*i) - (c + d*i) = (a - c) + (b - d)*i";
	}
	else if (e == id_hBtn_Umn)
	{
		ws = L"(a + b*i) * (c + d*i) = (a*c – b*d) + (a*d + b*c)*i";
	}
	else { ws = L"(a + b*i) / (c + d*i) = ((a*c – b*d) + ((b*c - a*d))*i) / (c*c + d*d)"; }
	return ws;
}

std::wstring trenerovca::create_ex() noexcept
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(-15, 15);
	fir.set_a(dist(mt));	fir.set_b(dist(mt)); // какие границы
	sec.set_a(dist(mt));	sec.set_b(dist(mt));
	std::wstring ws = L"(" + (fir.to_String()) + L")"; // создание строки задания, которую выведут на экран
	
	if (ex == id_hBtn_Rand)
	{
		e = id_hBtn_Sum + mt() % 4;
	}
	else { e = ex; }

	if (e == id_hBtn_Sum)
	{
		ws += L" + ";
		rez = fir + sec;
	}
	else if (e == id_hBtn_Min)
	{
		ws += L" - ";
		rez = fir - sec;
	}
	else if (e == id_hBtn_Umn)
	{
		ws += L" * ";
		rez = fir * sec;
	}
	else if (e == id_hBtn_Del)
	{
		ws += L" / ";
		rez = fir / sec;
	}
	ws += L"(" + (sec.to_String()) + L")";
	++i;
	hint = false;

	return ws;
}


void trenerovca::checker(const bool check) noexcept
{
	if (check) // проверка верности ответа
	{
		++ps; // увеличить серию правильных ответов
		if (nps > stat[npsir]) { stat[npsir] = nps; } // записать длинейшую серию неправильных ответов
		if (nps != 0) { ++c_nps; nps = 0; }
		++stat[prav]; // записать новый правильный ответ
	}
	else
	{
		++nps; // увеличить серию неправильных ответов
		if (ps > stat[psir]) { stat[psir] = ps; ++c_ps; } // записать длинейшую серию неправильных ответов
		if (ps != 0) { ++c_ps; ps = 0;}
		++stat[neprav]; // записать новый неправильный ответ
	}
}
bool trenerovca::check_ans(const bool skip, int a, int b) noexcept
{
	bool check;
	if (skip) // проверка на пропуск
	{
		++stat[sk]; // запись нового пропуска
		check = false; // пропуск считается ошибкой
	}
	else { check = ((a == rez.get_a()) && (b = rez.get_b())); }

	checker(check); // запись статистики
	if (hint) // была ли подсказака или нет
	{
		++stat[c_hint]; // записать новую подсказку
		if (check)
		{
			++stat[phint]; // записать новое количество правильных с подсказкой
		}
		else
		{
			++stat[nphint]; // записать новое количество неправильных с подсказкой
		}
	}
	return check;
}

void trenerovca::dodel_stat(const bool skip) noexcept
{
	if (skip) { --i; }
	if (i < int(stat[sk])) { --stat[sk]; }
	if (i < int(stat[rep])) { --stat[rep]; }
	stat[qest] = i; // запись количества заданий
	if (ps > stat[psir]) { stat[psir] = ps; ++c_ps; } // записать длинейшую серию неправильных ответов
	if (nps > stat[npsir]) { stat[npsir] = nps; ++c_nps; } // записать длинейшую серию неправильных ответов
	if (stat[neprav] != 0)
	{
		stat[neprav_proz] = ((stat[neprav] / i) * 100); // процент неправильных
		stat[otnoh] = stat[prav] / stat[neprav]; // отношение правильных и неправильных
		stat[snpsrsir] = stat[neprav] / c_nps; // средняя серия неправильных ответов
	}
	else
	{
		stat[neprav_proz] = 0; // процент неправильных
		stat[otnoh] = 0; // отношение правильных и неправильных
		stat[snpsrsir] = 0; // средняя серия неправильных ответов
	}

	if (stat[prav] != 0)
	{
		stat[prav_proz] = ((stat[prav] / i) * 100); // процент правильных
		stat[spsrsir] = stat[prav] / c_ps; // средняя серия правильных ответов
	}
	else
	{
		stat[prav_proz] = 0; // процент правильных
		stat[spsrsir] = 0; // средняя серия правильных ответов
	}
}

void trenerovca::re() noexcept
{
	name = L"user";
	i = 0;
	hint = false;
	e = 0;
	ps = 0;
	nps = 0;
	c_ps = 0;
	c_nps = 0;
	delete[] stat;
	stat = new float[15]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

std::wstring trenerovca::get_stat(const bool skip) noexcept
{
	time_t t = time(nullptr);
	wchar_t wt[100];
	tm times;
	localtime_s(&times, &t);

	std::wcsftime(wt, 100, L"%A %c", &times);

	dodel_stat(skip);
	std::wstring ws = L"-----------------------------\r\n";
	ws += L"Имя: " + name;
	ws += L"\r\nДата: " + std::wstring(wt);
	ws += L"\r\nТренеровка: ";
	if (ex == id_hBtn_Sum)
	{
		ws += L"Сумма";
	}
	else if (ex == id_hBtn_Min)
	{
		ws += L"Разность";
	}
	else if (ex == id_hBtn_Umn)
	{
		ws += L"Умножение";
	}
	else if (ex == id_hBtn_Del)
	{
		ws += L"Деление";
	}
	else { ws += L"Cлучайно"; }

	ws += L"\r\n\nКоличество вопросов: " + std::to_wstring(int(stat[qest]));
	ws += L"\r\nКоличество правильных ответов: " + std::to_wstring(int(stat[prav]));
	ws += L"\r\nПроцент правильных ответов: " + std::to_wstring(int(stat[prav_proz]));
	ws += L"\r\nКоличество неправильных ответов: " + std::to_wstring(int(stat[neprav]));
	ws += L"\r\nПроцент неправильных ответов: " + std::to_wstring(int(stat[neprav_proz]));
	ws += L"\r\nОтношение правильных к неправильным: " + std::to_wstring(stat[otnoh]);
	
	ws += L"\r\n\nСерия правильных ответов: " + std::to_wstring(int(stat[psir]));
	ws += L"\r\nСерия неправильных ответов: " + std::to_wstring(int(stat[npsir]));
	ws += L"\r\nСредняя серия неправильных: " + std::to_wstring(int(stat[snpsrsir]));
	ws += L"\r\nСредняя серия правильных: " + std::to_wstring(int(stat[spsrsir]));

	ws += L"\r\n\nКоличество подсказок: " + std::to_wstring(int(stat[c_hint]));
	ws += L"\r\nКоличество правильных с подсказкой: " + std::to_wstring(int(stat[phint]));
	ws += L"\r\nКоличество неправильных с подсказкой: " + std::to_wstring(int(stat[nphint]));

	ws += L"\r\n\nКоличество пропусков: " + std::to_wstring(int(stat[sk]));
	ws += L"\r\nКоличество повторов: " + std::to_wstring(int(stat[rep]));

	ws += L"\r\n-----------------------------\r\n";

	std::wofstream out("stat.txt", std::ios::app);
	out.imbue(std::locale(".1251"));
	if (out.is_open()) { out.write(ws.c_str(), ws.size()); }
	out.close();
	
	re();

	return ws;
}

std::wstring trenerovca::get_all_stat() noexcept
{
	std::wstring tmp;
	std::wstring ws;
	std::wifstream in("stat.txt");
	in.imbue(std::locale(".1251"));
	while (std::getline(in, tmp)) { ws += tmp + L"\r\n"; }
	in.close();
	return ws;
}

void trenerovca::povtor() noexcept
{
	++i;
	++stat[rep];
}
