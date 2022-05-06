#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <uxtheme.h>
#pragma comment (lib, "uxtheme.lib")
using namespace std;

#define FIND_FALSE_ string::npos
#define NotFound -1
#define PIXEL 1

struct Text {
	string Task, TempTask, Number, CalculatorType;
	HFONT TaskOut, ErrorOut, NumberOut;
	RECT RTTask, RTNumber;
	Text();

	//�������� �� ����������� ����� ������
	void CheckErrors();

	//������� �����
	void CalTextOut(HDC& memdc, HWND& hWnd);
};

// ����� ������� 6 �������� �������������: ���������� (16,10,2) � ������� (16,10,2)
static vector<HBITMAP> BitmapContainer(6);

// ���������� ������ ��������� �����
int Factorial(int)noexcept;

// C 10 ������� ���������� � 2
void dectobin(string&)noexcept;

// C 2 ������� ���������� � 10
void bintodec(string&)noexcept;

// C 16 ������� ���������� � 10
void hextodec(string&)noexcept;

// C 10 ������� ���������� � 16
void dectohex(string&)noexcept;

// ������� ������� ���������� ������� ���� ��������� ������� ������,
// ����� ��� ���������� ����� �������� ������������ �� ��������� ������������
string �alculator(string)noexcept;

// �������� � � PI 
void ReplaceConst(string&)noexcept;

// ������� ���� � ����� ���� �� ����� ��� ������
string CutStringNulls(string)noexcept;

// ��������� ������ false � �������� � true ���������� ������
void ToFalse(bool*, const int&)noexcept;

// ���� ���������� ���� ��������� ������  
int CountBrackets(const string&)noexcept;

// ������� ������ � ���� �� �����
int RCountBrackets(const string&)noexcept;

// ������� �������� �������� 
bool TransactionExclusions(string&)noexcept;

// ������ ��� ������ ���������� 
string Calculate(string, const char&)noexcept;

// ��������� ������� ������ ������ ������
void EnterComButtonZone(vector<RECT>*)noexcept;

// ��������� ���������� ������ ������ ������
void EnterIngButtonZone(vector<RECT>*)noexcept;

// ��������� ����� � ������
void AddSymb(string&, const string&, bool&)noexcept;

// �������� ������� ��������� ��� �� ���� � ��������� ������
bool InButtonZone(const POINT&, const RECT&)noexcept;

//������ ������ "log","ln", "sqrt", "cbrt" ,"pow"
string HardArithmetic(string&, const string&)noexcept;

//������� ����� �������� � ����, ����� �������� ����� ��������
void PrepareToCalculate(string&, const char&)noexcept;

//������� � ���� �� ����� ������� ���� � �����
int ReadNumberSymbols(const string&, const int&)noexcept;

//������� � ����� �� ���� ������� ���� � �����
int rReadNumberSymbols(const string&, const int&)noexcept;

//������� � ����� �� ���� ������� ���� � ����� ��� pow
int rReadNumberSymbolsEx(const string&, const int&)noexcept;

// �������� � ������ ��� ������� �������
void ArithmeticFuncEnter(string&, string&, const string&)noexcept;

// �������� � ������ ��� ������� ������ ����������
void ArithmeticEnter(string&, string&, bool&, const char&)noexcept;

//������ ������ + � - � ����� ������������� �����
void CalculateMP(string&, const int&, const int&, const int&)noexcept;

// C��������� ����������� ����
inline void ArithmeticComIng(string&, string&, const string&, const char, bool&) noexcept;

// ���������� ����� ��� �������� ������������ 
void EnterStrForCom(string&, string&, string&, bool&, POINT&, vector<RECT>*, bool*)noexcept;

// ���������� ����� ��� ����������� ������������ 
void EnterStrForIng(HWND&, string&, string&, bool&, POINT&, vector<RECT>*, int&, bool*)noexcept;

// ������� ������ ����� ������ ����� ������ � ���� ������
void FrameDrawingPaint(HDC&, const vector<RECT>*, const bool*, const POINT&, const HBRUSH&)noexcept;

// ������� ������ ����������� ������ ����� ������ ����� �� ���� ������
void FrameDrawingMouseM(HWND&, HDC&, const vector<RECT>*, const bool*, const POINT&, const HBRUSH&)noexcept;