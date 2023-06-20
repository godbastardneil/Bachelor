// Win32Project1.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "trenerovca.h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

trenerovca tren; // ����� ������������
bool tren_start = false; // �������� �� ������������
bool s = true; // ������� ��� ���
BOOL ss = false;

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Statistica(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Trenerovka(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Name(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���������� ��� �����.

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	
    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // ���� ��������� ���������:
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return (int) msg.wParam;
}

//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 540, 530, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) { return FALSE; }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   HWND hStat = CreateWindowW(L"static", L"����������� �����", WS_CHILD | WS_VISIBLE,
	   10, 10, 500, 410, hWnd, (HMENU)id_hStat_1, hInstance, nullptr);
   std::wstring ws = L"\t����������� ����� ������������ �� ���� ��������� z = a + b*i, ��� i - ������ �������, � ����� a - �������������� �����, b - ������ �����.";
   ws += L" ������������ ����� ����� ������������� ��� ��������� �����������.";
   ws += L"\n\t��� ��� ����� ������������ ��� ����������� �����, ����� ������� ������������� � ��������� �� -15 �� 15.";
   ws += L"\n\t����� ���������� ������� � ���� �����, ���������� � ������������ � ���, ����� ����� ������������ ����� �������� � ���.";
   ws += L" � ��� ����� ����������� �������� ��������� � ���� ������� ��������������� ��������, ��������� ���� ������ ��� ������, ���������� �������, �� ��� ��� ��������� ����� ��������������� ������� �������� � ����������.";
   ws += L" ���� �������� ��� ������������� ������. � ������ ������, ��� ������������� ����������� ���������� �����, � ������������ � ��� �������� ������ ��� �����.";
   ws += L"\n\t��������� ���������� ������ ��������� �������� � �������� �������.";
   SetWindowTextW(hStat, ws.c_str());

   HWND hBtn_1 = CreateWindowW(L"button", L"�����", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   10, 430, 100, 30, hWnd, (HMENU)id_hBtn_Sum, hInstance, nullptr);
   HWND hBtn_2 = CreateWindowW(L"button", L"��������", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   110, 430, 100, 30, hWnd, (HMENU)id_hBtn_Min, hInstance, nullptr);
   HWND hBtn_3 = CreateWindowW(L"button", L"���������", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   210, 430, 100, 30, hWnd, (HMENU)id_hBtn_Umn, hInstance, nullptr);
   HWND hBtn_4 = CreateWindowW(L"button", L"�������", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   310, 430, 100, 30, hWnd, (HMENU)id_hBtn_Del, hInstance, nullptr);
   HWND hBtn_5 = CreateWindowW(L"button", L"��������", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   410, 430, 100, 30, hWnd, (HMENU)id_hBtn_Rand, hInstance, nullptr);
   
   return TRUE;
}

//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT: // ������� ���� ���������� � ���������
                DialogBoxW(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

			case IDM_STAT: // ������� �� ���������� �����
				DialogBoxW(hInst, MAKEINTRESOURCE(IDD_STATBOX), hWnd, Statistica);
				break;

			case id_hBtn_Sum: // �����
			case id_hBtn_Min: // �����
			case id_hBtn_Umn: // ���������
			case id_hBtn_Del: // �������
			case id_hBtn_Rand: // ��������� �������
				tren.set_ex(wmId);
				DialogBoxW(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Name);
				DialogBoxW(hInst, MAKEINTRESOURCE(IDD_TRENER), hWnd, Trenerovka);
				break;

            default:
                return DefWindowProcW(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDM_EXIT)
        {
            EndDialog(hDlg, LOWORD(wParam));
        }
		return (INT_PTR)TRUE;
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Statistica(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		if (tren_start)
		{
			SetWindowTextW(GetDlgItem(hDlg, IDC_E_STAT), tren.get_stat(s).c_str());
			tren_start = false;
		}
		else
		{
			SetWindowTextW(GetDlgItem(hDlg, IDC_E_STAT), tren.get_all_stat().c_str());
		}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDM_EXIT)
		{
			EndDialog(hDlg, LOWORD(wParam)); // ������� ���� ����������
		}
		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Name(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	wchar_t ws[100];
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDM_EXIT)
		{
			GetDlgItemTextW(hDlg, IDC_NAME, ws, 100);
			std::wstring wss(ws);
			if (wss.size() > 0) { tren.set_name(wss); }
			EndDialog(hDlg, LOWORD(wParam));
		}
		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Trenerovka(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	int ans_a;
	int ans_b;
	switch (message)
	{
	case WM_INITDIALOG: // ������� ������ ������� � IDC_QUEST
		SetDlgItemTextW(hDlg, IDC_QUEST, (LPCWSTR)tren.create_ex().c_str());
		SetDlgItemTextW(hDlg, IDC_EX, (LPCWSTR)tren.get_i().c_str()); // ����� �������

		return (INT_PTR)TRUE;
		break;

	case WM_COMMAND:
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDC_ANSWER: // ����������� ��������� �����, � ��������� ��� �� ��������, ������� ��������� � IDC_STATUS
			s = false;
			ans_a = GetDlgItemInt(hDlg, IDC_A, &ss, true); // ��������� ����������������� ������������ �����
			ans_b = GetDlgItemInt(hDlg, IDC_B, &ss, true); // ��������� ����������������� ������ �����

			ShowWindow(HWND(lParam), SW_HIDE); // ������ ������ ������������� ������

			ShowWindow(GetDlgItem(hDlg, IDC_HINT), SW_HIDE); // ������ ������ ���������

			ShowWindow(GetDlgItem(hDlg, IDC_A), SW_HIDE); // ������ ���� ����� �������������� �����
			ShowWindow(GetDlgItem(hDlg, IDC_B), SW_HIDE); // ������ ���� ����� ������ �����
			ShowWindow(GetDlgItem(hDlg, IDC_DEISTV), SW_HIDE); // ������ ���� �������������� �����
			ShowWindow(GetDlgItem(hDlg, IDC_MNIM), SW_HIDE); // ������ ���� ������ �����

			ShowWindow(GetDlgItem(hDlg, IDC_REPIT), SW_HIDE); // ������ ������ �������
			ShowWindow(GetDlgItem(hDlg, IDC_HINT_STAT), SW_HIDE); // ������ ���� ���������

			// ��������� ������ �� �������� � ����� ������� ������ �������
			ShowWindow(GetDlgItem(hDlg, IDC_STATUS), SW_SHOW); // ������� ������� ���� �������

			if (tren.check_ans(false, ans_a, ans_b)) // ������� ������ �������
			{
				SetDlgItemTextW(hDlg, IDC_STATUS, L"���������");
			}
			else
			{
				SetDlgItemTextW(hDlg, IDC_STATUS, L"�����������");
				ShowWindow(GetDlgItem(hDlg, IDC_REPIT), SW_SHOW); // ������� ������� ������ �������
			}
			
			return (INT_PTR)TRUE;
			break;

		case IDC_HINT: // �������� ���������
			ShowWindow(HWND(lParam), SW_HIDE); // ������ ������ ���������

			ShowWindow(GetDlgItem(hDlg, IDC_HINT_STAT), SW_SHOW); // ������� ���� ��������� �������

			SetDlgItemTextW(hDlg, IDC_HINT_STAT, (LPCWSTR)tren.get_hint().c_str()); // ������� ���������

			return (INT_PTR)TRUE;
			break;

		case IDC_NEXT: // ������� �� ���������, ������� ������� ����������, ������ ����� - �������, ������� ��������� �������
			ShowWindow(GetDlgItem(hDlg, IDC_STATUS), SW_HIDE); // ������ ���� �������
			ShowWindow(GetDlgItem(hDlg, IDC_HINT_STAT), SW_HIDE); // ������ ���� ���������
			ShowWindow(GetDlgItem(hDlg, IDC_REPIT), SW_HIDE); // ������ ������ �������

			SetDlgItemTextW(hDlg, IDC_A, L"");
			SetDlgItemTextW(hDlg, IDC_B, L"");
			ShowWindow(GetDlgItem(hDlg, IDC_A), SW_SHOW); // ������� ������� ���� ����� �������������� �����
			ShowWindow(GetDlgItem(hDlg, IDC_B), SW_SHOW); // ������� ������� ���� ����� ������ �����
			ShowWindow(GetDlgItem(hDlg, IDC_DEISTV), SW_SHOW); // ������ ���� �������������� �����
			ShowWindow(GetDlgItem(hDlg, IDC_MNIM), SW_SHOW); // ������ ���� ������ �����

			ShowWindow(GetDlgItem(hDlg, IDC_ANSWER), SW_SHOW); // ������� ������� ������ ������������� ������
			ShowWindow(GetDlgItem(hDlg, IDC_HINT), SW_SHOW); // ������� ������� ������ ���������

			SetDlgItemTextW(hDlg, IDC_QUEST, (LPCWSTR)tren.create_ex().c_str()); // ������� ����� �������
			SetDlgItemTextW(hDlg, IDC_EX, (LPCWSTR)tren.get_i().c_str()); // ����� �������

			if (s) { tren.check_ans(true); }
			s = true;

			return (INT_PTR)TRUE;
			break;

		case IDC_REPIT: // ��������� �������
			ShowWindow(HWND(lParam), SW_HIDE); // ������ ������ �������
			
			ShowWindow(GetDlgItem(hDlg, IDC_STATUS), SW_HIDE); // ������ ���� �������

			ShowWindow(GetDlgItem(hDlg, IDC_A), SW_SHOW); // ������� ������� ���� ����� �������������� �����
			ShowWindow(GetDlgItem(hDlg, IDC_B), SW_SHOW); // ������� ������� ���� ����� ������ �����
			ShowWindow(GetDlgItem(hDlg, IDC_DEISTV), SW_SHOW); // ������ ���� �������������� �����
			ShowWindow(GetDlgItem(hDlg, IDC_MNIM), SW_SHOW); // ������ ���� ������ �����

			ShowWindow(GetDlgItem(hDlg, IDC_ANSWER), SW_SHOW); // ������� ������� ������ ������������� ������
			ShowWindow(GetDlgItem(hDlg, IDC_HINT), SW_SHOW); // ������� ������� ������ ���������

			tren.povtor(); // ������
			SetDlgItemTextW(hDlg, IDC_EX, (LPCWSTR)tren.get_i().c_str()); // ����� �������
			s = true;

			return (INT_PTR)TRUE;
			break;

		case IDOK:
		case IDM_EXIT: // ����������, ����� � ����������, �������� ���� ����������, ������ ���� ����������, �� ������ ��� ������ ������������
			tren_start = true;

			EndDialog(hDlg, LOWORD(wParam)); // ������� ���� ������������
			DialogBoxW(hInst, MAKEINTRESOURCE(IDD_STATBOX), hDlg, Statistica); // ����� ����������

			return (INT_PTR)TRUE;
			break;

		}
		break;
	}
	return (INT_PTR)FALSE;
}