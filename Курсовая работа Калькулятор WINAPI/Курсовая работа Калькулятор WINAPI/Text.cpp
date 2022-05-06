#include "�alculatorLogic.h"

Text::Text() {
	CalculatorType = "�������";
	Number = '0';

	// �������� ��������� ������
	TaskOut = CreateFont(20, 8, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Times New Roman");

	NumberOut = CreateFont(30, 12, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Times New Roman");

	ErrorOut = CreateFont(20, 9, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Times New Roman");

	// ���������� ������ �����
	RTNumber.left = 4;
	RTNumber.top = 79;
	RTNumber.right = 300;
	RTNumber.bottom = 129;

	// ���������� ������ �������������� ������
	RTTask.left = 4;
	RTTask.top = 50;
	RTTask.right = 300;
	RTTask.bottom = 95;
}

void Text::CalTextOut(HDC& memdc, HWND& hWnd) {
	GetDC(hWnd);

	//����� �������������� ������
	SetBkMode(memdc, TRANSPARENT);
	SetTextColor(memdc, RGB(133, 133, 133));
	SelectObject(memdc, TaskOut);
	DrawText(memdc, Task.c_str(), Task.size(), &RTTask, DT_RIGHT);

	//����� ������
	SetTextColor(memdc, RGB(255, 255, 255));

	//�������� ����� ����� ��������� "������� �� ���� ����������"
	if (Number == "������� �� ���� ����������") {
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
	if (Number == "������� �� ���� ����������")
		Number = '0';
	else if (Number == "�������� ����")
		Number = '0';
}