#include"resource.h"
#include"СalculatorLogic.h"

using namespace std;

static HINSTANCE hInst; 
LPCTSTR szWindowClass = "Danylo Bielytskyi";
LPCTSTR szTitle = "Калькулятор";

// Прототипы функций для работы с окном
ATOM MyRegisterClass(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);

// Основная программа
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	
	// Регистрация окна
	MyRegisterClass(hInstance);
	// Создание окна
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл оброботки сообщений 
	while (GetMessage(& msg, NULL, 0, 0))
	{
		TranslateMessage(& msg);
		DispatchMessage(& msg);
	}
	return msg.wParam;
}

// Регистрация окна
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW ; //стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; //віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; // Дескриптор программы
	wcex.hIcon = NULL; // Иконка
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // Курсор
	wcex.hbrBackground = CreateSolidBrush(RGB(31, 31, 31)); // Установка фона
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //Определение меню
	wcex.lpszClassName = szWindowClass; // Имя класса
	wcex.hIconSm = NULL;
	return RegisterClassEx(& wcex); //регистрация класса окна
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //Сохраняет дескриптор окна в переменной hInst
	hWnd = CreateWindow(szWindowClass, // ім’я класу вікна
		szTitle, // Название программы
		WS_SYSMENU, // стиль окна
		700, // Расположение по Х
		300, // Расположение по Y
		336, // Размер по Х
		567, // Размер по Y
		NULL, // Дескриптор родительского окна
		NULL, // Дескриптор меню окна
		hInstance, // Дескриптор програмы
		NULL); // Параметры создания
	if (!hWnd) 
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow); //Показать окно
	UpdateWindow(hWnd); //Обновить окно
	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static Text text;
	static HDC hdc, memBit;
	static RECT rt = { 0 };
	static HBRUSH WhiteBrush, GrayBrush;
	static POINT Cursore;

	static bool IngCalsystem[3], ComCalsystem[3];
	static bool AfterOperation, last_braket;

	static vector<RECT> ComCalculatorButtons[3], IngCalculatorButtons[3];
	static int brakets;
	switch (message)
	{
	//Попадаем сюда при первом запуске окна
	case WM_CREATE: 

		// Начальное инициализирование переменных
		ComCalsystem[1] = true;
		brakets = 0;

		SetClassLong(hWnd, GCL_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));

		// Загружаю битмапы калькуляторов
		BitmapContainer[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		BitmapContainer[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		BitmapContainer[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		BitmapContainer[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		BitmapContainer[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		BitmapContainer[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));

		memBit = CreateCompatibleDC(hdc);

		// Заполнение зон кнопок
		EnterIngButtonZone(IngCalculatorButtons);
		EnterComButtonZone(ComCalculatorButtons);

		// Cоздаю кисти для рамки
		WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		GrayBrush = CreateSolidBrush(RGB(19, 19, 19));

	// При нажатии на кнопку попадаем сюда
	case WM_LBUTTONDOWN: {

		Cursore.x = LOWORD(lParam);
		Cursore.y = HIWORD(lParam);

		text.CheckErrors();

		// Заполняет строку Task уравнением 
		if (text.CalculatorType == "Инженерный")
			EnterStrForIng(hWnd, text.Task, text.Number, AfterOperation, Cursore, IngCalculatorButtons, brakets, IngCalsystem);
		else
			EnterStrForCom(text.Task, text.TempTask, text.Number, AfterOperation, Cursore, ComCalculatorButtons, ComCalsystem);
		
		//Обновляем все что више кнопок
		RECT TEMP = { text.RTTask.left,text.RTTask.top,text.RTNumber.right,text.RTNumber.bottom };
		InvalidateRect(hWnd, &TEMP, TRUE);
		break;
	}
	case WM_MOUSEMOVE: 
		Cursore.x = LOWORD(lParam);
		Cursore.y = HIWORD(lParam);
		hdc = GetDC(hWnd);

		// Обводит кнопку стандартной рамкой когда курсор вышел из зоны кнопки
		if (text.CalculatorType == "Инженерный")
			FrameDrawingMouseM(hWnd, hdc, IngCalculatorButtons,IngCalsystem, Cursore, GrayBrush);
		else 
			FrameDrawingMouseM(hWnd, hdc, ComCalculatorButtons, ComCalsystem, Cursore, GrayBrush);

		ReleaseDC(hWnd, hdc);

		break;
	// Перерисовка окна
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);

		//Выбор битмапа калькулятора
		if (ComCalsystem[0])
			SelectObject(memBit, BitmapContainer[3]);
		else if (ComCalsystem[1])
			SelectObject(memBit, BitmapContainer[4]);
		else if (ComCalsystem[2])
			SelectObject(memBit, BitmapContainer[5]);
		else if (IngCalsystem[0])
			SelectObject(memBit, BitmapContainer[0]);
		else if (IngCalsystem[1])
			SelectObject(memBit, BitmapContainer[1]);
		else if (IngCalsystem[2])
			SelectObject(memBit, BitmapContainer[2]);

		HDC memdc;

		GetClientRect(hWnd,&rt);

		// Двойная буферизация которая предотвращает мигание приложения
		auto hbuff = BeginBufferedPaint(hdc, &rt, BPBF_COMPATIBLEBITMAP, NULL, &memdc);

		//Отрисовую выбранный калькулятор
		BitBlt(memdc, 0, 0, 320, 509, memBit, 0, 0, SRCCOPY);
		
		text.CalTextOut(memdc, hWnd);

		// Обводит кнопку белой рамкой когда курсор наведен на кнопку
		if (text.CalculatorType == "Инженерный")
			FrameDrawingPaint(memdc, IngCalculatorButtons, IngCalsystem, Cursore, WhiteBrush);
		else
			FrameDrawingPaint(memdc, ComCalculatorButtons, ComCalsystem, Cursore, WhiteBrush);

		//Закончить отрисовку 
		EndBufferedPaint(hbuff, TRUE);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_ENGINEERING:
			text.CalculatorType = "Инженерный";
			for (int i = 0; i < ARRAYSIZE(IngCalsystem); ++i) {
				if (ComCalsystem[i]) {
					IngCalsystem[i] = true;
					ComCalsystem[i] = false;
				}
			}
			break;
		case ID_COMMON:
			text.CalculatorType = "Обычный";
			for (int i = 0; i < ARRAYSIZE(IngCalsystem); ++i) {
				if (IngCalsystem[i]) {
					ComCalsystem[i] = true;
					IngCalsystem[i] = false;
				}
			}
			break;
		case ID_HEX:
			if (text.CalculatorType == "Инженерный")
				ToFalse(IngCalsystem, 0);
			else
				ToFalse(ComCalsystem, 0);
			break;
		case ID_DEC:
			if (text.CalculatorType == "Инженерный")
				ToFalse(IngCalsystem, 1);
			else
				ToFalse(ComCalsystem, 1);
			break;
		case ID_BIN:
			if (text.CalculatorType == "Инженерный")
				ToFalse(IngCalsystem, 2);
			else
				ToFalse(ComCalsystem, 2);
			break;
		case ID_AUTHOR:
			MessageBox(hWnd, (LPSTR)"Программа была разработана студентом Харьковского Национального Университета Радио Электроники (ХНУРЭ) из группы КИУКИ 19-7 Белицким Данилом Николаевичем", (LPCSTR)"Автор программы", MB_OK);
			break;
		case ID_ABOUT_PROGRAME:
			MessageBox(hWnd, (LPSTR)"Программа была разработана 01.05.2021 на языке С++ в Visual Studio 19, используемые библиотеки для написание программы были такие: windows.h, string, vector и algorithm.", (LPCSTR)"Про программу", MB_OK);
			break;
		case ID_INSTRUCTION:
			MessageBox(hWnd, (LPSTR)"1. Пользователю позволенно выбрать 1 из видов двух видов калькуляторов, такие как Инженерный и Обычный\n2. Есть возможность выбрать 1 из трех систем исчисления (16, 10, 2)\n3. Чтобы использовать Калькулятор вам нужно нажимать на нужные вам кнопки, почти все были взяты из Windows Калькулятор", (LPCSTR)"Инструкция", MB_OK);
			break;
		}
		text.Task.clear();
		text.Number = '0';
		InvalidateRect(hWnd, NULL, TRUE);
		break;

		// Закрытие окна
	case WM_DESTROY:

		// Чищу память 
		for(auto&Bitmap:BitmapContainer)
			DeleteObject(Bitmap);

		DeleteObject(WhiteBrush);
		DeleteObject(GrayBrush);
		DeleteObject(text.TaskOut);
		PostQuitMessage(0);
		break;

	default:
		// Обработка сообщений которые не обрабатываются
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}