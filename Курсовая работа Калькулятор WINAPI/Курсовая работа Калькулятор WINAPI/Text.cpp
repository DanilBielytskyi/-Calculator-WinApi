#include "СalculatorLogic.h"

Text::Text() {
	CalculatorType = "Обычный";
	Number = '0';

	// Заполняю структуры шрифта
	TaskOut = CreateFont(20, 8, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Times New Roman");

	NumberOut = CreateFont(30, 12, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Times New Roman");

	ErrorOut = CreateFont(20, 9, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Times New Roman");

	// Координаты вывода числа
	RTNumber.left = 4;
	RTNumber.top = 79;
	RTNumber.right = 300;
	RTNumber.bottom = 129;

	// Координаты вывода арифметической задачи
	RTTask.left = 4;
	RTTask.top = 50;
	RTTask.right = 300;
	RTTask.bottom = 95;
}

void Text::CalTextOut(HDC& memdc, HWND& hWnd) {
	GetDC(hWnd);

	//Вывод арифметической задачи
	SetBkMode(memdc, TRANSPARENT);
	SetTextColor(memdc, RGB(133, 133, 133));
	SelectObject(memdc, TaskOut);
	DrawText(memdc, Task.c_str(), Task.size(), &RTTask, DT_RIGHT);

	//Вывод ответа
	SetTextColor(memdc, RGB(255, 255, 255));

	//Уменьшаю шрифт чтобы поместить "Деление на ноль невозможно"
	if (Number == "Деление на ноль невозможно") {
		SelectObject(memdc, ErrorOut);
		DrawText(memdc, Number.c_str(), Number.size(), &RTNumber, DT_RIGHT);
	}
	else {
		SelectObject(memdc, NumberOut);
		DrawText(memdc, Number.c_str(), Number.size(), &RTNumber, DT_RIGHT);
	}
	ReleaseDC(hWnd, memdc);
}

void Text::CheckErrors(){
	if (Number == "Деление на ноль невозможно")
		Number = '0';
	else if (Number == "Неверный ввод")
		Number = '0';
}