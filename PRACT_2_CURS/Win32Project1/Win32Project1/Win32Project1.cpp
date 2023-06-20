// Win32Project1.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "trenerovca.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

trenerovca tren; // класс тестирования
bool tren_start = false; // началось ли тестирование
bool s = true; // пропуск или нет
BOOL ss = false;

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	
    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // Цикл основного сообщения:
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

//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
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

//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 540, 530, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) { return FALSE; }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   HWND hStat = CreateWindowW(L"static", L"Статический текст", WS_CHILD | WS_VISIBLE,
	   10, 10, 500, 410, hWnd, (HMENU)id_hStat_1, hInstance, nullptr);
   std::wstring ws = L"\tКомплексное число представляет из себя выражение z = a + b*i, где i - мнимая единица, и числа a - действительная часть, b - мнимая часть.";
   ws += L" Вещественные числа можно рассматривать как случайных комплексных.";
   ws += L"\n\tДля вас будут сгенерировно два комплексных часта, части которых сгенерированы в диапазоне от -15 до 15.";
   ws += L"\n\tОтвет необходимо вводить в поля ввода, подписаные в соответствии с тем, какую часть комплексного числа вводится в них.";
   ws += L" У вас будет возможность получить подсказку в виде формулы соответствующей операции, повторить ввод ответа при ошибки, пропустить задание, но все эти действиия будут соответствующим образом записаны в статистику.";
   ws += L" Поля исчезают при подтверждении ответа. В случаи ошибки, вам предоставится возможность повторного ввода, в соответствии с чем появится кнопка для этого.";
   ws += L"\n\tСлучайная тренировка выдает случайную операцию в качестве задания.";
   SetWindowTextW(hStat, ws.c_str());

   HWND hBtn_1 = CreateWindowW(L"button", L"Сумма", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   10, 430, 100, 30, hWnd, (HMENU)id_hBtn_Sum, hInstance, nullptr);
   HWND hBtn_2 = CreateWindowW(L"button", L"Разность", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   110, 430, 100, 30, hWnd, (HMENU)id_hBtn_Min, hInstance, nullptr);
   HWND hBtn_3 = CreateWindowW(L"button", L"Умножение", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   210, 430, 100, 30, hWnd, (HMENU)id_hBtn_Umn, hInstance, nullptr);
   HWND hBtn_4 = CreateWindowW(L"button", L"Деление", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   310, 430, 100, 30, hWnd, (HMENU)id_hBtn_Del, hInstance, nullptr);
   HWND hBtn_5 = CreateWindowW(L"button", L"Случайно", WS_CHILD | WS_VISIBLE | WS_BORDER,
	   410, 430, 100, 30, hWnd, (HMENU)id_hBtn_Rand, hInstance, nullptr);
   
   return TRUE;
}

//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
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
            case IDM_ABOUT: // открыть окно информации о программе
                DialogBoxW(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

			case IDM_STAT: // вывести из текстового файла
				DialogBoxW(hInst, MAKEINTRESOURCE(IDD_STATBOX), hWnd, Statistica);
				break;

			case id_hBtn_Sum: // сумма
			case id_hBtn_Min: // сумма
			case id_hBtn_Umn: // умножение
			case id_hBtn_Del: // деление
			case id_hBtn_Rand: // случайные задания
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

// Обработчик сообщений для окна "О программе".
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
			EndDialog(hDlg, LOWORD(wParam)); // закрыть окно статистики
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
	case WM_INITDIALOG: // вывести первое задание в IDC_QUEST
		SetDlgItemTextW(hDlg, IDC_QUEST, (LPCWSTR)tren.create_ex().c_str());
		SetDlgItemTextW(hDlg, IDC_EX, (LPCWSTR)tren.get_i().c_str()); // номер задания

		return (INT_PTR)TRUE;
		break;

	case WM_COMMAND:
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDC_ANSWER: // подтвердить введенный ответ, и отправить его на проверку, вывести результат в IDC_STATUS
			s = false;
			ans_a = GetDlgItemInt(hDlg, IDC_A, &ss, true); // получение пользовательского вещественной части
			ans_b = GetDlgItemInt(hDlg, IDC_B, &ss, true); // получение пользовательского мниной части

			ShowWindow(HWND(lParam), SW_HIDE); // скрыть кнопку подтверждения ответа

			ShowWindow(GetDlgItem(hDlg, IDC_HINT), SW_HIDE); // скруть кнопку подсказки

			ShowWindow(GetDlgItem(hDlg, IDC_A), SW_HIDE); // скрыть поле ввода действительной части
			ShowWindow(GetDlgItem(hDlg, IDC_B), SW_HIDE); // скрыть поле ввода мнимой части
			ShowWindow(GetDlgItem(hDlg, IDC_DEISTV), SW_HIDE); // скрыть поле действительной части
			ShowWindow(GetDlgItem(hDlg, IDC_MNIM), SW_HIDE); // скрыть поле мнимой части

			ShowWindow(GetDlgItem(hDlg, IDC_REPIT), SW_HIDE); // скрыть кнопку повтора
			ShowWindow(GetDlgItem(hDlg, IDC_HINT_STAT), SW_HIDE); // скрыть поле подсказки

			// отправить строки на проверку и потом вывести статус решения
			ShowWindow(GetDlgItem(hDlg, IDC_STATUS), SW_SHOW); // сделать видимым поле статуса

			if (tren.check_ans(false, ans_a, ans_b)) // вывести статус решения
			{
				SetDlgItemTextW(hDlg, IDC_STATUS, L"Правильно");
			}
			else
			{
				SetDlgItemTextW(hDlg, IDC_STATUS, L"Неправильно");
				ShowWindow(GetDlgItem(hDlg, IDC_REPIT), SW_SHOW); // сделать видимым кнопку повтора
			}
			
			return (INT_PTR)TRUE;
			break;

		case IDC_HINT: // получить подсказку
			ShowWindow(HWND(lParam), SW_HIDE); // скрыть кнопку подсказки

			ShowWindow(GetDlgItem(hDlg, IDC_HINT_STAT), SW_SHOW); // сделать поле подсказки видимой

			SetDlgItemTextW(hDlg, IDC_HINT_STAT, (LPCWSTR)tren.get_hint().c_str()); // вывести подсказку

			return (INT_PTR)TRUE;
			break;

		case IDC_NEXT: // перейти на следующий, сделать эдиторы невидимыми, кнопку ответ - видимой, вывести следующее задание
			ShowWindow(GetDlgItem(hDlg, IDC_STATUS), SW_HIDE); // скрыть поле статуса
			ShowWindow(GetDlgItem(hDlg, IDC_HINT_STAT), SW_HIDE); // скрыть поле подсказки
			ShowWindow(GetDlgItem(hDlg, IDC_REPIT), SW_HIDE); // скрыть кнопку повтора

			SetDlgItemTextW(hDlg, IDC_A, L"");
			SetDlgItemTextW(hDlg, IDC_B, L"");
			ShowWindow(GetDlgItem(hDlg, IDC_A), SW_SHOW); // сделать видимым поле ввода действительной части
			ShowWindow(GetDlgItem(hDlg, IDC_B), SW_SHOW); // сделать видимым поле ввода мнимой части
			ShowWindow(GetDlgItem(hDlg, IDC_DEISTV), SW_SHOW); // скрыть поле действительной части
			ShowWindow(GetDlgItem(hDlg, IDC_MNIM), SW_SHOW); // скрыть поле мнимой части

			ShowWindow(GetDlgItem(hDlg, IDC_ANSWER), SW_SHOW); // сделать видимым кнопку подтверждения ответа
			ShowWindow(GetDlgItem(hDlg, IDC_HINT), SW_SHOW); // сделать видимым кнопку подсказки

			SetDlgItemTextW(hDlg, IDC_QUEST, (LPCWSTR)tren.create_ex().c_str()); // вывести новое задание
			SetDlgItemTextW(hDlg, IDC_EX, (LPCWSTR)tren.get_i().c_str()); // номер задания

			if (s) { tren.check_ans(true); }
			s = true;

			return (INT_PTR)TRUE;
			break;

		case IDC_REPIT: // повторить решение
			ShowWindow(HWND(lParam), SW_HIDE); // скрыть кнопку повтора
			
			ShowWindow(GetDlgItem(hDlg, IDC_STATUS), SW_HIDE); // скрыть поле статуса

			ShowWindow(GetDlgItem(hDlg, IDC_A), SW_SHOW); // сделать видимым поле ввода действительной части
			ShowWindow(GetDlgItem(hDlg, IDC_B), SW_SHOW); // сделать видимым поле ввода мнимой части
			ShowWindow(GetDlgItem(hDlg, IDC_DEISTV), SW_SHOW); // скрыть поле действительной части
			ShowWindow(GetDlgItem(hDlg, IDC_MNIM), SW_SHOW); // скрыть поле мнимой части

			ShowWindow(GetDlgItem(hDlg, IDC_ANSWER), SW_SHOW); // сделать видимым кнопку подтверждения ответа
			ShowWindow(GetDlgItem(hDlg, IDC_HINT), SW_SHOW); // сделать видимым кнопку подсказки

			tren.povtor(); // повтор
			SetDlgItemTextW(hDlg, IDC_EX, (LPCWSTR)tren.get_i().c_str()); // номер задания
			s = true;

			return (INT_PTR)TRUE;
			break;

		case IDOK:
		case IDM_EXIT: // завершение, вывод в статистику, открытие окна результата, просто окно статистики, но только для одного пользователя
			tren_start = true;

			EndDialog(hDlg, LOWORD(wParam)); // закрыть окно тестирования
			DialogBoxW(hInst, MAKEINTRESOURCE(IDD_STATBOX), hDlg, Statistica); // вывод статистики

			return (INT_PTR)TRUE;
			break;

		}
		break;
	}
	return (INT_PTR)FALSE;
}