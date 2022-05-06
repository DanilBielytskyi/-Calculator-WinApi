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

	//Проверка на коректность ввода данных
	void CheckErrors();

	//Выводит текст
	void CalTextOut(HDC& memdc, HWND& hWnd);
};

// Будет хранить 6 битмапов калькуляторов: инженерный (16,10,2) и обычный (16,10,2)
static vector<HBITMAP> BitmapContainer(6);

// Рекурсивно считаю факториал числа
int Factorial(int)noexcept;

// C 10 системы исчисления в 2
void dectobin(string&)noexcept;

// C 2 системы исчисления в 10
void bintodec(string&)noexcept;

// C 16 системы исчисления в 10
void hextodec(string&)noexcept;

// C 10 системы исчисления в 16
void dectohex(string&)noexcept;

// Функция которая рекурсивно вызывая себя вычесляет сначала скобки,
// также тут происходит выбор операций взависимости от уравнения пользователя
string Сalculator(string)noexcept;

// Заменяет е и PI 
void ReplaceConst(string&)noexcept;

// Убирает ноли в конце если не нужны для ответа
string CutStringNulls(string)noexcept;

// Заполняет массив false и записует в true переданный индекс
void ToFalse(bool*, const int&)noexcept;

// Ищет логическую пред последнюю скобку  
int CountBrackets(const string&)noexcept;

// Считает скобки с лево на право
int RCountBrackets(const string&)noexcept;

// Убирает ненужные операции 
bool TransactionExclusions(string&)noexcept;

// Логика для легкой арифметики 
string Calculate(string, const char&)noexcept;

// Заполняет обычный вектор зонами кнопок
void EnterComButtonZone(vector<RECT>*)noexcept;

// Заполняет инженерный вектор зонами кнопок
void EnterIngButtonZone(vector<RECT>*)noexcept;

// Добавляет числа в строку
void AddSymb(string&, const string&, bool&)noexcept;

// Предикат который проверяет был ли клик в переданой кнопке
bool InButtonZone(const POINT&, const RECT&)noexcept;

//Логика работы "log","ln", "sqrt", "cbrt" ,"pow"
string HardArithmetic(string&, const string&)noexcept;

//Удаляет часть операции и цифр, потом записует ответ операции
void PrepareToCalculate(string&, const char&)noexcept;

//Считает с лево на право сколько цифр в числе
int ReadNumberSymbols(const string&, const int&)noexcept;

//Считает с право на лево сколько цифр в числе
int rReadNumberSymbols(const string&, const int&)noexcept;

//Считает с право на лево сколько цифр в числе для pow
int rReadNumberSymbolsEx(const string&, const int&)noexcept;

// Записует в строку для решения функции
void ArithmeticFuncEnter(string&, string&, const string&)noexcept;

// Записует в строку для решения легкую арифметику
void ArithmeticEnter(string&, string&, bool&, const char&)noexcept;

//Логика работы + и - а также отрицательных чисел
void CalculateMP(string&, const int&, const int&, const int&)noexcept;

// Cокращение однотипного кода
inline void ArithmeticComIng(string&, string&, const string&, const char, bool&) noexcept;

// Заполнение задач для обычного калькулятора 
void EnterStrForCom(string&, string&, string&, bool&, POINT&, vector<RECT>*, bool*)noexcept;

// Заполнение задач для инженерного калькулятора 
void EnterStrForIng(HWND&, string&, string&, bool&, POINT&, vector<RECT>*, int&, bool*)noexcept;

// Обводит кнопку белой рамкой когда курсор в зоне кнопки
void FrameDrawingPaint(HDC&, const vector<RECT>*, const bool*, const POINT&, const HBRUSH&)noexcept;

// Обводит кнопку стандартной рамкой когда курсор вышел из зоны кнопки
void FrameDrawingMouseM(HWND&, HDC&, const vector<RECT>*, const bool*, const POINT&, const HBRUSH&)noexcept;