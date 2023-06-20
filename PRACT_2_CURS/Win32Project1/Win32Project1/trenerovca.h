#pragma once

#include <random>
#include <fstream>
#include <ctime>
#include "Resource.h"
#include "complex.h"

#define qest 0		// ���������� �������
#define prav 1		// ���������� ����������
#define prav_proz 2		// ���������� ������������
#define neprav 3		// ������� ����������
#define neprav_proz 4		// ������� ������������
#define otnoh 5		// ��������� ���������� � ������������

#define psir 6		// ����� ����������
#define npsir 7		// ����� ������������

#define spsrsir 8		// ������� ����� ����������
#define snpsrsir 9		// ������� ����� ������������


#define c_hint 10		// ���������� ���������
#define phint 11		// ���������� ���������� � ����������
#define nphint 12		// ���������� ������������ � ����������

#define sk 13		// ���������� ���������
#define rep 14		// ���������� ��������

class trenerovca
{
private:
	std::wstring name; // ��� �����������
	complex fir; // ������ ���������
	complex sec; // ������ ���������
	complex rez; // ���������
	uint8_t i; // ����� �������
	bool hint; // ���� ������������ ��������� ��� ���
	int ex; // ��� ����������
	int e; // ��� ��������� �������
	float *stat; // �������������� ����������, ��������� �����, ��� ��� � �������
	float ps; // ������� ����� ����������
	float nps; // ������� ����� ������������
	float c_ps; // ���������� ����� ���������� �������
	float c_nps; // ���������� ����� ���������� �������

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

	inline void set_name(const std::wstring n) noexcept { name = n; } // ���������� ���������
	inline void set_hint(const bool h) noexcept { hint = h; } // ���������� ���������
	inline void set_ex(const int E) noexcept { ex = E; } // ���������� ��� �������

	std::wstring get_i() noexcept { return std::to_wstring(i); } // �������� ����� �������
	std::wstring get_hint() noexcept; // �������� ���������

	std::wstring create_ex() noexcept; // �������� �������
	
	/*��������*/
	void checker(const bool check) noexcept;
	bool check_ans(const bool skip, int a = 0, int b = 0) noexcept;

	void dodel_stat(const bool skip) noexcept; // ����������� ���������� - ������, ������� ������������ �� ������ �������
	void re() noexcept; // �������� ����������

	std::wstring get_stat(const bool skip) noexcept; // �������� ���������� �� ����������
	std::wstring get_all_stat() noexcept; // �������� ��� ����������
	
	void povtor() noexcept; // ������
};