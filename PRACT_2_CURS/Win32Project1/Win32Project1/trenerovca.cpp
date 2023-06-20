#include "stdafx.h"
#include "trenerovca.h"

std::wstring trenerovca::get_hint() noexcept
{
	std::wstring ws;
	hint = true;
	if (e == id_hBtn_Sum) // ����� ���������
	{
		ws = L"(a + b*i) + (c + d*i) = (a + c) + (b + d)*i";
	}
	else if (e == id_hBtn_Min)
	{
		ws = L"(a + b*i) - (c + d*i) = (a - c) + (b - d)*i";
	}
	else if (e == id_hBtn_Umn)
	{
		ws = L"(a + b*i) * (c + d*i) = (a*c � b*d) + (a*d + b*c)*i";
	}
	else { ws = L"(a + b*i) / (c + d*i) = ((a*c � b*d) + ((b*c - a*d))*i) / (c*c + d*d)"; }
	return ws;
}

std::wstring trenerovca::create_ex() noexcept
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(-15, 15);
	fir.set_a(dist(mt));	fir.set_b(dist(mt)); // ����� �������
	sec.set_a(dist(mt));	sec.set_b(dist(mt));
	std::wstring ws = L"(" + (fir.to_String()) + L")"; // �������� ������ �������, ������� ������� �� �����
	
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
	if (check) // �������� �������� ������
	{
		++ps; // ��������� ����� ���������� �������
		if (nps > stat[npsir]) { stat[npsir] = nps; } // �������� ��������� ����� ������������ �������
		if (nps != 0) { ++c_nps; nps = 0; }
		++stat[prav]; // �������� ����� ���������� �����
	}
	else
	{
		++nps; // ��������� ����� ������������ �������
		if (ps > stat[psir]) { stat[psir] = ps; ++c_ps; } // �������� ��������� ����� ������������ �������
		if (ps != 0) { ++c_ps; ps = 0;}
		++stat[neprav]; // �������� ����� ������������ �����
	}
}
bool trenerovca::check_ans(const bool skip, int a, int b) noexcept
{
	bool check;
	if (skip) // �������� �� �������
	{
		++stat[sk]; // ������ ������ ��������
		check = false; // ������� ��������� �������
	}
	else { check = ((a == rez.get_a()) && (b = rez.get_b())); }

	checker(check); // ������ ����������
	if (hint) // ���� �� ���������� ��� ���
	{
		++stat[c_hint]; // �������� ����� ���������
		if (check)
		{
			++stat[phint]; // �������� ����� ���������� ���������� � ����������
		}
		else
		{
			++stat[nphint]; // �������� ����� ���������� ������������ � ����������
		}
	}
	return check;
}

void trenerovca::dodel_stat(const bool skip) noexcept
{
	if (skip) { --i; }
	if (i < int(stat[sk])) { --stat[sk]; }
	if (i < int(stat[rep])) { --stat[rep]; }
	stat[qest] = i; // ������ ���������� �������
	if (ps > stat[psir]) { stat[psir] = ps; ++c_ps; } // �������� ��������� ����� ������������ �������
	if (nps > stat[npsir]) { stat[npsir] = nps; ++c_nps; } // �������� ��������� ����� ������������ �������
	if (stat[neprav] != 0)
	{
		stat[neprav_proz] = ((stat[neprav] / i) * 100); // ������� ������������
		stat[otnoh] = stat[prav] / stat[neprav]; // ��������� ���������� � ������������
		stat[snpsrsir] = stat[neprav] / c_nps; // ������� ����� ������������ �������
	}
	else
	{
		stat[neprav_proz] = 0; // ������� ������������
		stat[otnoh] = 0; // ��������� ���������� � ������������
		stat[snpsrsir] = 0; // ������� ����� ������������ �������
	}

	if (stat[prav] != 0)
	{
		stat[prav_proz] = ((stat[prav] / i) * 100); // ������� ����������
		stat[spsrsir] = stat[prav] / c_ps; // ������� ����� ���������� �������
	}
	else
	{
		stat[prav_proz] = 0; // ������� ����������
		stat[spsrsir] = 0; // ������� ����� ���������� �������
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
	ws += L"���: " + name;
	ws += L"\r\n����: " + std::wstring(wt);
	ws += L"\r\n����������: ";
	if (ex == id_hBtn_Sum)
	{
		ws += L"�����";
	}
	else if (ex == id_hBtn_Min)
	{
		ws += L"��������";
	}
	else if (ex == id_hBtn_Umn)
	{
		ws += L"���������";
	}
	else if (ex == id_hBtn_Del)
	{
		ws += L"�������";
	}
	else { ws += L"C�������"; }

	ws += L"\r\n\n���������� ��������: " + std::to_wstring(int(stat[qest]));
	ws += L"\r\n���������� ���������� �������: " + std::to_wstring(int(stat[prav]));
	ws += L"\r\n������� ���������� �������: " + std::to_wstring(int(stat[prav_proz]));
	ws += L"\r\n���������� ������������ �������: " + std::to_wstring(int(stat[neprav]));
	ws += L"\r\n������� ������������ �������: " + std::to_wstring(int(stat[neprav_proz]));
	ws += L"\r\n��������� ���������� � ������������: " + std::to_wstring(stat[otnoh]);
	
	ws += L"\r\n\n����� ���������� �������: " + std::to_wstring(int(stat[psir]));
	ws += L"\r\n����� ������������ �������: " + std::to_wstring(int(stat[npsir]));
	ws += L"\r\n������� ����� ������������: " + std::to_wstring(int(stat[snpsrsir]));
	ws += L"\r\n������� ����� ����������: " + std::to_wstring(int(stat[spsrsir]));

	ws += L"\r\n\n���������� ���������: " + std::to_wstring(int(stat[c_hint]));
	ws += L"\r\n���������� ���������� � ����������: " + std::to_wstring(int(stat[phint]));
	ws += L"\r\n���������� ������������ � ����������: " + std::to_wstring(int(stat[nphint]));

	ws += L"\r\n\n���������� ���������: " + std::to_wstring(int(stat[sk]));
	ws += L"\r\n���������� ��������: " + std::to_wstring(int(stat[rep]));

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
