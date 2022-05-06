#include "СalculatorLogic.h"

bool InButtonZone(const POINT& CursorePos, const RECT& ButtonZone)noexcept {
	return CursorePos.x >= ButtonZone.left && CursorePos.x <= ButtonZone.right && CursorePos.y >= ButtonZone.top && CursorePos.y <= ButtonZone.bottom;
}

double ModuleDouble(double& left, const double& right) {
	left = fabs(left);
	while (left - right >= 0 && right!=0) {
		left -= right;
	}
	return left;
}

inline void ArithmeticComIng(string& Task, string& TempTask, const string& Number, const char Symbol, bool& AfterOperation) noexcept {
	Task += Number + Symbol;
	AfterOperation = true;
	TempTask = Task;
}

void EnterStrForCom(string& Task, string& TempTask, string& Number, bool& AfterOperation, POINT& Cursore, vector<RECT>* ComCalculatorButtons, bool* ComCalsystem)noexcept {
	// %
	if (InButtonZone(Cursore, ComCalculatorButtons[0][0]))
		ArithmeticComIng(Task, TempTask, Number, '%', AfterOperation);
	// CE
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][1]))
		Task = TempTask;
	// C
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][2])) {
		Task.clear();
		TempTask.clear();
		Number = '0';
	}
	// DELETE
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][3])) {
		if (Number.size() > 0) {
			if (Number.find("pow") != FIND_FALSE_) {
				Number = '0';
			}
			else if (Number[Number.size() - 1] == ')') {
				Number.erase(Number.size() - 1, 1);
				Number.erase(0, Number.find('(') + 1);
			}
			else if (Number[0] == '-' && Number.size() == 2) {
				Number = '0';
			}
			else if (Number.size() == 1) {
				Number = '0';
			}
			else {
				Number.erase(Number.size() - 1, 1);
			}

		}
	}
	// 1/X
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][4]))
		Number = "1/(" + Number + ')';
	// x^2
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][5]))
		Number = "pow(" + Number + ",2)";
	// sqrt
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][6]))
		ArithmeticFuncEnter(Task, Number, "sqrt");
	// /
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][7]))
		ArithmeticComIng(Task, TempTask, Number, '/', AfterOperation);
	// *
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][8]))
		ArithmeticComIng(Task, TempTask, Number, '*', AfterOperation);
	// -
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][9]))
		ArithmeticComIng(Task, TempTask, Number, '-', AfterOperation);
	// +
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][10]))
		ArithmeticComIng(Task, TempTask, Number, '+', AfterOperation);
	// =
	else if (InButtonZone(Cursore, ComCalculatorButtons[0][11])) {
		Task += Number;
		// Логика для вычесления в 16 системе 
		if (ComCalsystem[0]) {
			string buff = Task;
			hextodec(buff);

			//Возможность считать после операции = 
			if (buff.rfind('=') != FIND_FALSE_) {
				buff = Сalculator(buff.substr(buff.rfind('=')+1));
			}
			else {
				buff = Сalculator(buff);
			}
			if (buff.find("inf") != FIND_FALSE_) {
				Number = "Деление на ноль невозможно";
				TempTask.clear();
				Task.clear();
				return;
			}
			if (buff.find("-nan(ind)") != FIND_FALSE_) {
				Number = "Неверный ввод";
				Task.clear();
				TempTask.clear();
				return;
			}
			dectohex(buff);
			Number = buff;
		}
		// Логика для вычесления в 10 системе 
		else if (ComCalsystem[1]) {

			//Возможность считать после операции = 
			if (Task.rfind('=') != FIND_FALSE_) {
				Number = Сalculator(Task.substr(Task.rfind('=') + 1));
			}
			else {
				Number = Сalculator(Task);
			}
			if (Number.find("inf") != FIND_FALSE_) {
				TempTask.clear();
				Number = "Деление на ноль невозможно";
				Task.clear();
				return;
			}
			if (Number.find("-nan(ind)") != FIND_FALSE_) {
				Number = "Неверный ввод";
				TempTask.clear();
				Task.clear();
				return;
			}
		}
		// Логика для вычесления в 2 системе 
		if (ComCalsystem[2]) {
			string buff = Task;
			bintodec(buff);

			//Возможность считать после операции = 
			if (buff.rfind('=') != FIND_FALSE_) {
				buff = Сalculator(buff.substr(buff.rfind('=') + 1));
			}
			else {
				buff = Сalculator(buff);
			}
			if (buff.find("inf") != FIND_FALSE_) {
				TempTask.clear();
				Number = "Деление на ноль невозможно";
				Task.clear();
				return;
			}
			if (buff.find("-nan(ind)") != FIND_FALSE_) {
				Number = "Неверный ввод";
				TempTask.clear();
				Task.clear();
				return;
			}
			dectobin(buff);
			Number = buff;
		}
		
		Task += '=';
	}
	// Уникальные кнопки для 10 и 16 системы исчесления
	if (!ComCalsystem[2]) {
		// 7
		if (InButtonZone(Cursore, ComCalculatorButtons[0][12]))
			AddSymb(Number, "7", AfterOperation);
		// 8
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][13]))
			AddSymb(Number, "8", AfterOperation);
		// 9
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][14]))
			AddSymb(Number, "9", AfterOperation);
		// 4
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][15]))
			AddSymb(Number, "4", AfterOperation);
		// 5
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][16]))
			AddSymb(Number, "5", AfterOperation);
		// 6
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][17]))
			AddSymb(Number, "6", AfterOperation);
		// 1
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][18]))
			AddSymb(Number, "1", AfterOperation);
		// 2
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][19]))
			AddSymb(Number, "2", AfterOperation);
		// 3
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][20]))
			AddSymb(Number, "3", AfterOperation);
		// +/-
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][21]) && Number[0] != '0') {
			if (Number.size() >= 1 && Number.find('-') != FIND_FALSE_) {
				Number.erase(Number.find('-'), 1);
			}
			else if (Number[0] != '0') {
				if (Number.find('(') != FIND_FALSE_)
					Number.insert(Number.find('(') + 1, "-");
				else
					Number.insert(0, "-");
			}
		}
		// 0
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][22])) {
			if (Number[0] != '0' || AfterOperation || Number.find('.')!= FIND_FALSE_)
				AddSymb(Number, "0", AfterOperation);
		}
		// .
		else if (InButtonZone(Cursore, ComCalculatorButtons[0][23]) && ComCalsystem[1]) {
			if (Number.find('.') == FIND_FALSE_)
				Number.insert(Number.size(), ".");
			else
				Number.erase(Number.find('.'), 1);
		}
		if (ComCalsystem[0]) {
			if (InButtonZone(Cursore, ComCalculatorButtons[0][24]))
				AddSymb(Number, "A", AfterOperation);
			else if (InButtonZone(Cursore, ComCalculatorButtons[0][25]))
				AddSymb(Number, "B", AfterOperation);
			else if (InButtonZone(Cursore, ComCalculatorButtons[0][26]))
				AddSymb(Number, "C", AfterOperation);
			else if (InButtonZone(Cursore, ComCalculatorButtons[0][27]))
				AddSymb(Number, "D", AfterOperation);
			else if (InButtonZone(Cursore, ComCalculatorButtons[0][28]))
				AddSymb(Number, "E", AfterOperation);
			else if (InButtonZone(Cursore, ComCalculatorButtons[0][29]))
				AddSymb(Number, "F", AfterOperation);
		}
	}
	else {
		if (ComCalsystem[2]) {//12 13 14
			if (InButtonZone(Cursore, ComCalculatorButtons[2][12]))
				AddSymb(Number, "1", AfterOperation);
			else if (InButtonZone(Cursore, ComCalculatorButtons[2][13]))
				AddSymb(Number, "0", AfterOperation);
			else if (InButtonZone(Cursore, ComCalculatorButtons[2][14])) {
				if (!Number.empty() && Number[0] != '-' && Number[0] != '0')
					Number.insert(0, "-");
				else
					Number.erase(0, 1);
			}
		}
	}
}

void AddSymb(string& str, const string& Symbol, bool& AfterOperation)noexcept {
	// Если операция и последний символ ) то ничего не пишем
	if (!str.empty() && (str[str.size() - 1] == ')' || str[str.size() - 1] == '|') && !AfterOperation)
		return;
	if ((str=="e" || str=="PI") && !AfterOperation)
		return;

	// Позволяет сразу заменить символ после операции 
	if (AfterOperation || str[0] == '0' && str.find('.') == FIND_FALSE_) {
		str = Symbol;
		AfterOperation = false;
	}
	else {
		str += Symbol;
	}
}

void ReplaceConst(string& str)noexcept {
	// Заменяю все PI на число
	while (str.find("PI") != FIND_FALSE_) {
		string buff = str;
		str.erase(str.find("PI"), 2);
		str.insert(buff.find("PI"), "3.1415");
	}
	int expmaybe = 0;
	// Заменяю все 'е' на число
	while (str.find("e", expmaybe) != FIND_FALSE_) {
		if (str.find("e", expmaybe) == str.find("exp")) {
			expmaybe = str.find("exp") + 1;
		}
		if (str.find("e", expmaybe) == FIND_FALSE_)
			break;

		string buff = str;
		str.erase(str.find("e", expmaybe), 1);
		str.insert(buff.find("e", expmaybe), "2.7182");
	}
}

void EnterComButtonZone(vector<RECT>* Buttons)noexcept {

	// В низ кнопок
	for (int j = 0, y = 183; j < 6; ++j, y += 51 + PIXEL * 3) {
		// Кнопок в право
		for (int i = 0, x = 4; i < 4; ++i, x += 76 + PIXEL * 2) {
			// Для 3 видов счесления
			for (int k = 0; k < 3; ++k) {
				if (j >= 2 && i == 3) {
					Buttons[k].push_back(RECT() = { x, y, x + 76, y + 51 });
					continue;
				}
				else if (j >= 2) {
					break;
				}
				Buttons[k].push_back(RECT() = { x, y, x + 76, y + 51 });
			}
		}
	}

	// Кнопки 1 2 3 4 5 6 7 8 9 0 +/-
	for (int j = 0, y = 291; j < 4; ++j, y += 51 + PIXEL * 3) {
		// Кнопок в право
		for (int i = 0, x = 4; i < 3; ++i, x += 76 + PIXEL * 2) {
			// Для 2 видов счесления (16,10)
			for (int k = 0; k < 2; ++k) {
				Buttons[k].push_back(RECT() = { x, y, x + 76, y + 51 });
			}
		}
	}


	// Кнопки для 16 систем исчесления A B C D E F
	for (int i = 0, x = 4; i < 6; ++i, x += 50 + PIXEL * 2) {
		Buttons[0].push_back(RECT() = { x, 144, x + 50, 144 + 37 });
	}
	// Записую в 2 калькулятор 1 0 и +/-
	Buttons[2].push_back(RECT() = { 4, 290, 237, 369 });
	Buttons[2].push_back(RECT() = { 4, 372, 237, 450 });
	Buttons[2].push_back(RECT() = { 4, 453, 118, 554 });
}

void EnterIngButtonZone(vector<RECT>* Buttons)noexcept {
	// В низ кнопок
	for (int j = 0, y = 194; j < 2; ++j, y += 37 + PIXEL * 2) {
		// Кнопок в право
		for (int i = 0, x = 4; i < 3; ++i, x += 61 + PIXEL * 2) {
			// Для 3 видов счесления
			for (int k = 0; k < 3; ++k) {
				Buttons[k].push_back(RECT() = { x, y, x + 60, y + 37 });
			}
		}
	}

	//Записую 2 кнопки удаления строки и символа 
	for (int k = 0; k < 3; ++k) {
		Buttons[k].push_back(RECT() = { 192, 194, 253, 270 });
		Buttons[k].push_back(RECT() = { 255, 194, 315, 270 });
	}

	// Записую места кнопок ОПЕРАЦИЙ в калькуляторе
	for (int j = 0, y = 272; j < 6; ++j, y += 37 + PIXEL * 2) {
		// Кнопок ОПЕРАЦИЙ в право
		for (int i = 0, x = 4; i < 5; ++i, x += 61 + PIXEL * 2) {
			// Для 3 видов счесления 
			for (int k = 0; k < 3; ++k) {
				// Кнопки чисел записывать не будем
				if (j >= 2 && (i == 0 || i == 4)) {
					Buttons[k].push_back(RECT() = { x, y, x + 60, y + 37 });
					continue;
				}
				else if (j >= 2) {
					break;
				}
				Buttons[k].push_back(RECT() = { x, y, x + 60, y + 37 });
			}
		}
	}

	// Записуем кнопки триганометрии
	for (int i = 0, x = 4; i < 8; ++i, x += 37 + PIXEL * 2)
		for (int j = 0; j < 3; ++j)
			Buttons[j].push_back(RECT() = { x, 162 ,x + 37, 191 });

	// Записую места кнопок ЦИФР в калькуляторе
	for (int j = 0, y = 350; j < 4; ++j, y += 37 + PIXEL * 2) {
		// Кнопок ЦИФР в право
		for (int i = 0, x = 66; i < 3; ++i, x += 61 + PIXEL * 2) {
			// Для 2 видов счесления (16 и 10) так как у 2 системы там только 1 и 0
			for (int k = 0; k < 2; ++k) {
				Buttons[k].push_back(RECT() = { x, y, x + 61, y + 37 });
			}
		}
	}

	// Кнопки для 16 систем исчесления A B C D E F
	for (int i = 0, x = 4; i < 6; ++i, x += 50 + PIXEL * 2) 
		Buttons[0].push_back(RECT() = { x, 123, x + 50, 123 + 37 });
	

	//Записую в 2 системе кнопки 0 и 1 И +/-
	Buttons[2].push_back(RECT() = { 66, 350, 253, 407 });
	Buttons[2].push_back(RECT() = { 66, 409, 253, 465 });
	Buttons[2].push_back(RECT() = { 66, 467, 158, 504 });
}

void ToFalse(bool* array, const int& index_true)noexcept {
	for (int i = 0; i < 3; ++i) {
		array[i] = false;
		if (i == index_true)
			array[i] = true;
	}
}

int ReadNumberSymbols(const string& str, const int& index)noexcept {
	char numbers[5] = { '+','*', '/','-',',' };

	//Если перый символ минус то считаем что это часть числа
	int count = (str[index + 1] == '-') ? 1 : 0;

	for (int j = index + 1 + count; j < str.size(); ++j) {
		for (int i = 0; i < ARRAYSIZE(numbers); ++i) {
			if (str[j] == numbers[i])
				return count;
		}
		++count;
	}
	return count;
}

string Сalculator(string equation)noexcept {
	do {
		if (equation.find("(") == FIND_FALSE_ && equation.find(")") != FIND_FALSE_) {
			equation.erase(equation.find(")"), 1);
		}
		if (equation.find("-nan(ind)") != FIND_FALSE_ || equation.find("inf") != FIND_FALSE_) {
			return equation;
		}
		if (TransactionExclusions(equation)) {
			continue;
		}
		if (equation.find('(') != FIND_FALSE_)
		{
			string buff = equation;

			//Удаляю скобки 
			equation.erase(buff.find('('), CountBrackets(buff) - buff.find('('));

			//Удаляю скобки и рекурсивно вызываю функцию для ее вычесления
			equation.insert(buff.find('('), Сalculator(buff.substr(buff.find('(') + 1, CountBrackets(buff) - buff.find('(') - 1)));
			continue;
		}
		else if (equation.find('|') != FIND_FALSE_) {
			string buff = equation;

			//Удаляю |
			equation.erase(buff.find('|'), buff.find('|', buff.find('|') + 1) - buff.find('|') + 1);

			//Записую число по модулю
			double result = fabs(stod(Сalculator(buff.substr(buff.find('|') + 1, buff.find('|', buff.find('|') + 1) - buff.find('|') - 1))));

			//Записую ответ
			equation.insert(buff.find('|'), CutStringNulls(to_string(result)));

			continue;
		}
		else if (equation.rfind("!") != FIND_FALSE_) {
			string buff = equation;

			//Удаляю из строки
			equation.erase(buff.find('!'), ReadNumberSymbols(buff, buff.find('!')) + 1);

			//Записую число которое я потом буду возводить в факториал
			int num = stod(buff.substr(buff.find('!') + 1, ReadNumberSymbols(buff, buff.find('!'))));

			//Записую ответ
			equation.insert(buff.find('!'), to_string(Factorial(num)));
			continue;
		}
		else if (equation.rfind("log") != FIND_FALSE_ || equation.rfind("ln") != FIND_FALSE_ || equation.rfind("pow") != FIND_FALSE_ || equation.rfind("sqrt") != FIND_FALSE_ || equation.rfind("cbrt") != FIND_FALSE_ || equation.rfind("exp") != FIND_FALSE_ || equation.rfind("sin") != FIND_FALSE_ || equation.rfind("asin") != FIND_FALSE_ || equation.rfind("cos") != FIND_FALSE_ || equation.rfind("acos") != FIND_FALSE_ || equation.rfind("tg") != FIND_FALSE_ || equation.rfind("atg") != FIND_FALSE_ || equation.rfind("ctg") != FIND_FALSE_ || equation.rfind("actg") != FIND_FALSE_) {
			string buff = equation;

			//Записую в вектор индесы найденых операций
			vector<int> task = { int(equation.rfind("log")), int(equation.rfind("ln")), int(equation.rfind("sqrt")), int(equation.rfind("cbrt")),int(equation.rfind("pow")) ,int(equation.rfind("exp")),
			int(equation.rfind("sin")), int(equation.rfind("asin")) ,int(equation.rfind("cos")), int(equation.rfind("acos")), int(equation.rfind("tg")), int(equation.rfind("atg")),int(equation.rfind("ctg")),int(equation.rfind("actg")) };

			//Записую имена операций
			vector<string> task_str = { "log","ln", "sqrt", "cbrt" ,"pow","exp","sin","asin","cos","acos","tg","atg","ctg","actg" };

			int max = -1;
			int index = 0;

			//Ищу самую крайнюю операцию
			for (int i = 0; i < task.size(); ++i)
				if (task[i] > max) { max = task[i]; index = i; }


			// Из-за того что find находит в asin обычный sin  нужно делать проверку
			if (index >= 6) {
				for (int i = 6; i <= 12; i += 2) {
					// arc или нет
					if (index == i && task[index] - 1 == task[index + 1] && task[index] - 1 != -1) {
						++index;
						break;
					}
					// tg или artctg
					else if (index == i && task[index] - 2 == task[index + 3] && task[index] - 2 != -1) {
						index += 3;
						break;
					}
					// tg или ctg
					else if (index == i && task[index] - 1 == task[index + 2] && task[index] - 1 != -1) {
						index += 2;
						break;
					}
				}
			}

			//Вычисляю самую крайнюю опперацию
			HardArithmetic(equation, task_str[index]);
			continue;
		}
		else if (equation.find('*') != FIND_FALSE_ || equation.find('/') != FIND_FALSE_)
		{
			//Тут вычисляется "/"
			if (equation.find('*') > equation.find('/')) {
				PrepareToCalculate(equation, '/');
				continue;
			}
			//Тут вычисляется "*"
			else {
				PrepareToCalculate(equation, '*');
				continue;
			}
		}
		else if (equation.find('%') != FIND_FALSE_) {
			//Тут вычисляется "%"
			PrepareToCalculate(equation, '%');
			continue;
		}
		else if (equation.find('+') != FIND_FALSE_ || equation.find('-') != FIND_FALSE_)
		{
			int minus = equation.find('-');
			int plus = equation.find('+');
			int next_minus = equation.find('-', equation.find('-') + 1);

			//Если первый - нету больше операции + и - то конец
			if (minus == 0 && plus == NotFound && next_minus == NotFound)
				return equation;

			//Если будет ,-8 выйти
			if (equation.find(',') != FIND_FALSE_ && equation[equation.find(',') + 1] == '-')
				return equation;

			CalculateMP(equation, minus, plus, next_minus);
			continue;
		}
		return equation;
	} while (true);
	return equation;
}

void PrepareToCalculate(string& str, const char& sign)noexcept {
	string buff = str;
	int LeftFromSymb, RightFromSymb, start, end;

	// Считаю числа справа и лева от операции 
	LeftFromSymb = rReadNumberSymbols(buff, str.find(sign));
	RightFromSymb = ReadNumberSymbols(buff, str.find(sign));

	start = str.find(sign) - LeftFromSymb;
	end = RightFromSymb + LeftFromSymb + 1;

	// Удаляю 2 числа и операцию и отдаю его на вычесление
	str.erase(start, end);
	str.insert(start, Calculate(buff.substr(start, end), sign));
}

string HardArithmetic(string& str, const string& Task)noexcept {
	int LCountNum, RCountNum;
	if (Task == "pow") {
		string buff = str;

		LCountNum = str.find(',', str.rfind("pow")) - str.rfind("pow") - 3;
		RCountNum = ReadNumberSymbols(str, str.find(',', str.rfind("pow")));

		str.erase(str.rfind("pow"), LCountNum + 3 + RCountNum + 1);

		int a = stod(buff.substr(buff.rfind("pow") + 3, LCountNum));
		int b = stod(buff.substr(buff.find(',', buff.rfind("pow")) + 1, RCountNum));

		double result = pow(a, b);
		str.insert(buff.rfind("pow"), CutStringNulls(to_string(result)));
	}
	else {
		string buff = str;

		//Считываю число
		RCountNum = ReadNumberSymbols(str, str.rfind(Task) + strlen(Task.c_str()) - 1);

		str.erase(str.rfind(Task), RCountNum + strlen(Task.c_str()));

		//Записую число
		double a = stod(buff.substr(buff.rfind(Task) + strlen(Task.c_str()), RCountNum));
		double result;

		// 1 из операций
		if (Task == "log")
			result = log10(a);
		else if (Task == "ln")
			result = log(a);
		else if (Task == "sqrt")
			result = sqrt(a);
		else if (Task == "exp")
			result = exp(a);
		else if (Task == "cbrt")
			result = cbrt(a);
		else if (Task == "exp")
			result = exp(a);
		else if (Task == "sin")
			result = sin(a);
		else if (Task == "asin")
			result = asin(a);
		else if (Task == "cos")
			result = cos(a);
		else if (Task == "acos")
			result = acos(a);
		else if (Task == "tg")
			result = tan(a);
		else if (Task == "atg")
			result = atan(a);
		else if (Task == "ctg")
			result = 1 / tan(a);
		else
			result = 1 / tan(a);


		str.insert(buff.rfind(Task), CutStringNulls(to_string(result)));
	}
	return str;
}

bool TransactionExclusions(string& equation)noexcept {
	//Минус на минус дает +
	if (equation.find("--") != FIND_FALSE_ && equation.find("--") != 0) {
		string buff = equation;
		equation.erase(equation.find("--"), 2);
		equation.insert(buff.find("--"), "+");
		return true;
	}

	//Минус на минус дает + но теперь мы его не пишем
	else if (equation.find("--") != FIND_FALSE_ && equation.find("--") == 0) {
		equation.erase(equation.find("--"), 2);
		return true;
	}

	if (equation.find("+-") != FIND_FALSE_) {
		equation.erase(equation.find("+-"), 1);
		return true;
	}
	return false;
}

void CalculateMP(string& equation, const int& minus, const int& plus, const int& next_minus)noexcept {
	string buff = equation;
	//Если 1 символ в строке - значит не будем его тут считать за операцию
	if (minus == 0) {

		//Если следуйщий минус после первого будет найдет и он будет меньше +
		if (next_minus != NotFound && plus > next_minus) {
			int a = equation.find('-', next_minus + 1);
			int b = equation.find('+', plus);

			int NextOpearion = (a > b) ? b : a;

			//Если следуйщей операции не будет 
			if (a == NotFound) {
				NextOpearion = b;
			}
			if (b == NotFound) {
				NextOpearion = a;
			}
			if (a == NotFound && b == NotFound) {
				NextOpearion = buff.size();
			}
			equation.erase(0, NextOpearion);
			equation.insert(0, Calculate(buff.substr(0, NextOpearion), '-'));
		}

		//Операция "-"
		else if (plus == NotFound) {
			int a = equation.find('-', next_minus + 1);

			int NextOpearion = a;

			if (a == NotFound) {
				NextOpearion = equation.size();
			}

			equation.erase(0, NextOpearion);
			equation.insert(0, Calculate(buff.substr(0, NextOpearion), '-'));
		}

		//Операция "+"
		else {
			int a = equation.find('-', next_minus);
			int b = equation.find('+', plus + 1);

			int NextOpearion = (a > b) ? b : a;

			//Если следуйщей операции не будет 
			if (a == NotFound) {
				NextOpearion = b;
			}
			if (b == NotFound) {
				NextOpearion = a;
			}
			if (a == NotFound && b == NotFound) {
				NextOpearion = buff.size();
			}
			equation.erase(0, NextOpearion);
			equation.insert(0, Calculate(buff.substr(0, NextOpearion), '+'));
		}
	}
	//Если 1 символ в строке не "-"
	else {

		//Если - будет меньше + то будет операция "-"
		if (minus != NotFound && plus > minus) {
			int a = equation.find('-', minus + 1);
			int b = equation.find('+', plus);

			int NextOpearion = (a > b) ? b : a;

			//Если следуйщей операции не будет 
			if (a == NotFound) {
				NextOpearion = b;
			}
			if (b == NotFound) {
				NextOpearion = a;
			}
			if (a == NotFound && b == NotFound) {
				NextOpearion = buff.size();
			}
			equation.erase(0, NextOpearion);
			equation.insert(0, Calculate(buff.substr(0, NextOpearion), '-'));
		}
		//Если "-"
		else if (plus == NotFound) {
			int a = equation.find('-', minus + 1);

			int NextOpearion = a;

			if (a == NotFound) {
				NextOpearion = equation.size();
			}

			equation.erase(0, NextOpearion);
			equation.insert(0, Calculate(buff.substr(0, NextOpearion), '-'));
		}
		//Операция "+"
		else {
			int a = equation.find('-', minus);
			int b = equation.find('+', plus + 1);

			int NextOpearion = (a > b) ? b : a;

			//Если следуйщей операции не будет 
			if (a == NotFound) {
				NextOpearion = b;
			}
			if (b == NotFound) {
				NextOpearion = a;
			}
			if (a == NotFound && b == NotFound) {
				NextOpearion = buff.size();
			}
			equation.erase(0, NextOpearion);
			equation.insert(0, Calculate(buff.substr(0, NextOpearion), '+'));
		}
	}
}

string Calculate(string str, const char& sign)noexcept {
	string temp = str;
	string result;
	bool first_null = false, second_null = false;

	//Если 1 символ был - то удаляем его и запоминаем что он был - 
	if (temp[0] == '-') {
		first_null = true;
		temp.erase(0, 1);
	}

	//Если символ операции не - то смотри на 2 число 
	if (temp[temp.find(sign) + 1] == '-') {
		second_null = true;
		temp.erase(temp.find(sign) + 1, 1);
	}

	//Если 2 минуса то получим +
	if (first_null && second_null) {
		first_null = second_null = false;
	}

	//Записую числа 
	double a = stod(temp.substr(0, temp.find(sign)));
	double b = stod(temp.substr(temp.find(sign) + 1, temp.size()));

	//Если число поступило как - то тут возвращаем ему -
	if (first_null)
		a *= -1;
	if (second_null)
		b *= -1;

	//Выбор арифметической операции
	switch (sign) {
	case '+':
		result = CutStringNulls(to_string(a + b));
		break;
	case '-':
		result = CutStringNulls(to_string(a - b));
		break;
	case '*':
		result = CutStringNulls(to_string(a * b));
		break;
	case '/':
		result = CutStringNulls(to_string(a / b));
		break;
	case '%':
		result = CutStringNulls(to_string(ModuleDouble(a , b)));
		break;
	}

	return result;
}

void bintodec(string& str)noexcept
{
	string nam;
	string temp = str;
	int new_symb = 0;
	int counter;
	temp += '+';
	for (int i = 0, counter = 0; i < temp.size(); ++i) {
		if (temp[i] == '0' || temp[i] == '1') {
			nam.push_back(temp[i]);
			++counter;
		}

		//Если число было считано то конвертируем его в 10
		else if (temp[i] != '0' && temp[i] != '1' && !nam.empty() || i + 1 == temp.size() && !nam.empty()) {

			int result = 0, pow = 1;

			for (int j = nam.length() - 1; j >= 0; --j, pow <<= 1)
				result += (nam[j] - '0') * pow;

			str.erase(new_symb, counter);
			str.insert(new_symb, to_string(result));
			new_symb = to_string(result).size() + 1 + new_symb;
			counter = 0;
			nam.clear();
		}
		// Если символ
		else {
			++new_symb;
		}
	}
}

void dectobin(string& str)noexcept
{
	string result;
	int num = fabs(stoi(str));
	// Цикл со сдвигом вправо на 1 бит
	for (; num != 0; num >>= 1)
		result.insert(0, (num & 1) ? "1" : "0");
	if (str[0] == '-' )
		str = '-' + result;
	else 
		str = result;
}

void hextodec(string& str)noexcept {
	string nam;
	string temp = str;
	int new_symb = 0;
	int counter;
	temp += '+';
	for (int i = 0, counter = 0; i < temp.size(); ++i) {

		//Считаем количество цифр в числе
		if (int(temp[i]) <= int('9') && int(temp[i]) >= int('0') || int(temp[i]) <= int('F') && int(temp[i]) >= int('A')) {
			nam.push_back(temp[i]);
			++counter;
		}

		// Если символ в не диапозона 1...9 и A...B и строка не пустая или если символ последний
		else if (((int(temp[i]) > int('9') || int(temp[i]) < int('0')) && (int(temp[i]) > int('F') || int(temp[i]) < int('A'))) && !nam.empty() || i + 1 == temp.size() && !nam.empty()) {

			double result_num = 0, temp_num = 0;

			//Конвертирую число в 10 систему
			while (!nam.empty()) {
				if (int(nam[0]) <= int('F') && int(nam[0]) >= int('A')) {
					temp_num = double(nam[0]) - 55.0;
				}
				else {
					temp_num = stod(nam.substr(0, 1));
				}
				result_num += temp_num * pow(16, nam.size() - 1);
				nam.erase(0, 1);
			}

			//Удаляю число в 16 и записую в 10
			str.erase(new_symb, counter);
			str.insert(new_symb, CutStringNulls(to_string(result_num)));
			new_symb = CutStringNulls(to_string(result_num)).size() + 1 + new_symb;
			counter = 0;
			nam.clear();
		}
		else {
			++new_symb;
		}
	}
}

void dectohex(string& str)noexcept {
	bool first_null = false;
	if (str[0] == '-') {
		first_null = true;
		str.erase(0, 1);
	}
	int num = stoi(str);
	string temp;
	do {
		int temp_num = num % 16;
		switch (temp_num) {
		case int('A') - 55:
			temp += 'A';
			break;
		case int('B') - 55:
			temp += 'B';
			break;
		case int('C') - 55:
			temp += 'C';
			break;
		case int('D') - 55:
			temp += 'D';
			break;
		case int('E') - 55:
			temp += 'E';
			break;
		case int('F') - 55:
			temp += 'F';
			break;
		default:
			temp += to_string(num % 16).substr(0, str.size());

		}

		num /= 16;
		if (num < 16 && num != 0)
			continue;

		else if (num == 0)
			break;

	} while (true);
	std::reverse(temp.begin(), temp.end());
	if (first_null&& temp[0]!='0')
		temp.insert(0, "-");
	str = temp;
}

int Factorial(int N)noexcept {
	if (N < 0)
		return 0;
	if (N == 0)
		return 1;
	else
		return N * Factorial(N - 1);
}

int rReadNumberSymbolsEx(const string& str, const int& index)noexcept {
	char numbers[1] = { 'w' };
	int count = 0;
	for (int j = index - 1; j >= 0; --j) {
		for (int i = 0; i < ARRAYSIZE(numbers); ++i) {

			//Если сейчас символ на - и следуйщий будет еще 1 знак 
			if (j - 1 >= 0 && str[j] == '-' && str[j - 1] == 'w') {
				return ++count;
			}
			//Если знак значит число подсчитано
			else if (str[j] == numbers[i])
				return count;
		}
		++count;
	}
	return count;
}

int rReadNumberSymbols(const string& str, const int& index)noexcept {
	char numbers[7] = { '+','*', '-', '/',',','%', '=' };
	int count = 0;
	for (int j = index - 1; j >= 0; --j) {
		for (int i = 0; i < ARRAYSIZE(numbers); ++i) {
			//Если сейчас символ на - и следуйщий будет еще 1 знак 
			if (j - 1 >= 0 && str[j] == '-' && (str[j - 1] == '+' || str[j - 1] == '*' || str[j - 1] == '-' || str[j - 1] == '/' || str[j - 1] == ',' || str[j - 1] == '%'|| str[j - 1] == '=')) {
				return ++count;
			}

			//Если 1 символ минус
			else if (j == 0 && str[j] == '-') {
				return ++count;
			}
			//Если знак значит число подсчитано
			else if (str[j] == numbers[i])
				return count;
		}
		++count;
	}
	return count;
}

string CutStringNulls(string str)noexcept {
	if (str.find(".000000") != FIND_FALSE_)
		str.erase(str.find('.'), 7);

	return str;
}

int CountBrackets(const string& str)noexcept {
	int equal = 0;
	int index_first = 0, index_second = 0;
	do {

		index_first = str.find('(', index_first);
		index_second = str.find(')', index_second);

		// Если встретили "(" раньше чем ")" ищем следующий "("
		if (str.find('(', index_first) < str.find(')', index_second) && str.find('(', index_first) != -1) {
			++index_first;
			++equal;
		}
		else {
			++index_second;
			--equal;
		}

	} while (equal != 0);
	
	//Возвращаем последнюю ")" для коректного вычесления скобок
	return str.find(')', index_second - 2) + 1;
}

void FrameDrawingPaint(HDC& hdc, const vector<RECT>* ButtonZone, const bool* CalculatorSystem, const POINT& Cursore, const HBRUSH& Brush)noexcept {
	int index = 0;

	//Выбираем 1 из 3 видовс исчесления
	for (int i = 0; i < 3; ++i)
		if (CalculatorSystem[i])
			index = i;

	//Рисуем рамки вокруг кнопок, пользы ноль зато как выглядит!
	for (const auto& el : ButtonZone[index]) {
		if (PtInRect(&el, Cursore)) {
			FrameRect(hdc, &el, Brush);
			break;
		}
	}

}

int RCountBrackets(const string& str)noexcept {
	int equal = 0;
	int minus = 0;
	int index_first = str.size(),temp_index = str.size(), index_second = str.size();
	do {
		if (str.rfind(')', index_first) != FIND_FALSE_)
			index_first = str.rfind(')', index_first);
		else
			index_first = 0;

		//Ищу скобки
		index_second = str.rfind('(', index_second);

		// Если правосторонним поиском ")" стоит раньше чем "("
		if (str.rfind('(', index_second) < str.rfind(')', index_first) && str.rfind(')', index_first)!= FIND_FALSE_) {
			--index_first;
			++equal;
		}
		else {
			--index_second;
			--equal;
		}

	} while (equal != 0);
	return str.rfind('(', ++index_second);
}

void FrameDrawingMouseM(HWND& hWnd, HDC& hdc, const vector<RECT>* ButtonZone, const bool* CalculatorSystem, const POINT& Cursore, const HBRUSH& Brush)noexcept {
	int index = 0;
	for (int i = 0; i < 3; ++i)
		if (CalculatorSystem[i])
			index = i;

	// Если функция FrameDrawingPaint рисует белую рамку, то эта ее удаляет
	for (const auto& el : ButtonZone[index]) {
		if (PtInRect(&el, Cursore)) {
			InvalidateRect(hWnd, &el, 0);
		}
		else {
			FrameRect(hdc, &el, Brush);
		}
	}
}

void ArithmeticEnter(string& Task, string& Number, bool& AfterOperation, const char& arithmetic)noexcept {
	// Если после скобки то записуем только знак
	if (!Task.empty() && (Task[Task.size() - 1] == ')' || Task[Task.size() - 1] == '|')) {
		Task += arithmetic;
	}
	else {
		Task += Number + arithmetic;
		AfterOperation = true;
	}
}

void ArithmeticFuncEnter(string& Task, string& Number, const string& FunctionName)noexcept {
	// Если после скобки то записуем только знак
	if (!Task.empty() && Task[Task.size() - 1] == ')') {
		Task.insert(RCountBrackets(Task), FunctionName);
	}
	else {
		Number = FunctionName + "(" + Number + ')';
	}
}

void EnterStrForIng(HWND& hWnd, string& Task, string& Number, bool& AfterOperation, POINT& Cursore, vector<RECT>* IngCalculatorButtons, int& brakets, bool* IngCalsystem)noexcept {

	// 2^x
	if (InButtonZone(Cursore, IngCalculatorButtons[0][0])) {

		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(RCountBrackets(Task), "pow(2,");
			Task.insert(Task.rfind(')') + 1, ")");
		}
		else {
			Number = "pow(2," + Number + ')';
		}
	}
	// 10^x
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][1]))
	{
		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(RCountBrackets(Task), "pow(10,");
			Task.insert(Task.rfind(')') + 1, ")");
		}
		else {
			Number = "pow(10," + Number + ')';
		}
	}
	// e^x
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][2])) {
		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(RCountBrackets(Task), "pow(e,");
			Task.insert(Task.rfind(')') + 1, ")");
		}
		else {
			Number = "pow(e," + Number + ')';
		}
	}
	// x^2
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][3])) {
		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(RCountBrackets(Task), "pow(");
			Task.insert(Task.rfind(')') + 1, ",2)");
		}
		else {
			Number = "pow(" + Number + ",2)";
		}
	}
	// p
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][4]))
		Number = "PI";
	// e
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][5]))
		Number = "e";
	// C
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][6])) {
		AfterOperation = false;
		Task.clear();
		brakets = 0;
		Number = '0';
	}
	// DELETE
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][7])) {
		if (Number.size() > 0) {
			if (Number.find("pow") != FIND_FALSE_) {
				Number = '0';
			}
			// Удаляет полность набранную функцию
			else if (Number[Number.size() - 1] == ')') {
				Number.erase(Number.size() - 1, 1);
				Number.erase(0, Number.find('(') + 1);
			}
			// Удаляет полность набранную функцию
			else if (Number[Number.size() - 1] == '|') {
				Number.erase(Number.size() - 1, 1);
				Number.erase(0, Number.find('|') + 1);
			}
			// Если в строке остался 1 число
			else if (Number[0] == '-' && Number.size() == 2) {
				Number = '0';
			}
			else if (Number.size() == 1) {
				Number = '0';
			}
			// Удаляет последний символ
			else {
				Number.erase(Number.size() - 1, 1);
			}

		}
	}
	// X^3
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][8])) {
		// Если наш х вся скобка то записуем в ее начало
		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(RCountBrackets(Task), "pow(");
			Task.insert(Task.rfind(')') + 1, ",3)");
		}
		else {
			Number = "pow(" + Number + ",3)";
		}
	}
	// 1/X
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][9])) {
		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(RCountBrackets(Task), "1/");
		}
		else {
			Number = "1/(" + Number + ')';
		}
	}
	// |
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][10])) {
		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(RCountBrackets(Task), "|");
			Task += '|';
			AfterOperation = true;
		}
		else {
			if (Number.find('|') == FIND_FALSE_) {
				Number = '|' + Number + '|';
			}
			else {
				Number.erase(Number.find('|'), 1);
				Number.erase(Number.find('|'), 1);
			}
		}

	}
	// exp
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][11]))
		ArithmeticFuncEnter(Task, Number, "exp");
	// mod
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][12]))
		ArithmeticEnter(Task, Number, AfterOperation, '%');
	// x^y
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][13])) {
		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(Task.rfind(')') + 1, "^");
		}
		else {
			Task += Number + '^';
			AfterOperation = true;
		}
	}
	// (
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][14])) {
		if (!Number.empty() && Number[Number.size() - 1] == ')') {
			Task += Number;
			AfterOperation = true;
		}
		if (Task.empty() || Task[Task.size() - 1] != ')')
			Task += '(';
		else
			Task += "*(";

		++brakets;
	}
	// )
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][15])) {
		if (brakets > 0) {
			if (Task[Task.size() - 1] == ')') {
				Task += ')';
			}
			else {
				Task += Number + ')';
			}
			--brakets;
			AfterOperation = true;
		}
	}
	// !
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][16])) {
		if (!Task.empty() && Task[Task.size() - 1] == ')') {
			Task.insert(RCountBrackets(Task), "!");
		}
		else {
			if (Number.find('!') == FIND_FALSE_) {
				Number.insert(0, "!");
			}
			else {
				Number.erase(Number.find('!'), 1);
			}
		}
	}
	// /
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][17]))
		ArithmeticEnter(Task, Number, AfterOperation, '/');
	// sqrt
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][18]))
		ArithmeticFuncEnter(Task, Number, "sqrt");
	// *
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][19]))
		ArithmeticEnter(Task, Number, AfterOperation, '*');
	// cbrt
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][20]))
		ArithmeticFuncEnter(Task, Number, "cbrt");
	// -
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][21]))
		ArithmeticEnter(Task, Number, AfterOperation, '-');
	// log
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][22]))
		ArithmeticFuncEnter(Task, Number, "log");
	// +
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][23]))
		ArithmeticEnter(Task, Number, AfterOperation, '+');
	// ln
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][24]))
		ArithmeticFuncEnter(Task, Number, "ln");
	// = 
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][25])) {

		//Логика для добавления цифре в конец если это требуется
		if (!Task.empty() && Task[Task.size() - 1] != ')'  && Task[Task.size() - 1] != '|' || Task.empty() && !Number.empty()) {
			Task += Number;
		}

		// Если пользователь не дозакрывал скобки то нужно сделать это за него
		while (brakets != 0) {
			Task += ')';
			--brakets;
		}

		//Логика для работы x^y
		while (Task.rfind('^') != FIND_FALSE_) {
			// Если х скобка то записуем операцию перед ее началом
			if (Task[Task.rfind('^') - 1] == ')') {
				Task.insert(RCountBrackets(Task.substr(Task.find("=") + 1, Task.rfind('^'))), "pow(");
			}
			else {
				int a = Task.rfind('^') - rReadNumberSymbols(Task, Task.rfind('^'));
				Task.insert(Task.rfind('^') - rReadNumberSymbols(Task, Task.rfind('^')), "pow(");
			}
			// Если у скобка то записуем операцию после ее конца
			if (Task[Task.rfind('^') + 1] == '(') {
				Task.insert(CountBrackets(Task.substr(Task.rfind('^'), Task.size())) + Task.rfind('^'), ")");
			}
			else {
				Task.insert(Task.rfind('^') + ReadNumberSymbols(Task, Task.rfind('^')) + 1, ")");
			}
			string buff = Task;
			Task.erase(Task.rfind('^'), 1);
			Task.insert(buff.rfind('^'), ",");
		}

		//Инженерный калькулятор в 16 системе счесления
		if (IngCalsystem[0]) {
			string buff = Task;
			hextodec(buff);
			ReplaceConst(buff);

			// Вычиляет после 2 равно, удобно
			if (buff.rfind('=') != FIND_FALSE_) {
				buff = Сalculator(buff.substr(buff.rfind('=') + 1));
			}
			else {
				buff = Сalculator(buff);
			}
			//Если во время вычелений вышло /0
			if (buff.find("inf") != FIND_FALSE_) {
				Number = "Деление на ноль невозможно";
				Task.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				return;
			}
			if (buff.find("-nan(ind)") != FIND_FALSE_) {
				Number = "Неверный ввод";
				Task.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				return;
			}
			dectohex(buff);
			Number = buff;
			if (Number.empty())
				Number = "Ответ меньше 1(";
			Task += '=';
		}

		//Инженерный калькулятор в 10 системе счесления
		else if (IngCalsystem[1]) {
			string buff = Task;
			ReplaceConst(buff);

			// Вычиляет после 2 равно, удобно
			if (buff.rfind('=') != FIND_FALSE_) {
				Number = Сalculator(buff.substr(buff.rfind('=') + 1));
			}
			else {
				Number = Сalculator(buff);
			}
			//Если во время вычелений вышло /0
			if (Number.find("inf") != FIND_FALSE_) {
				Number = "Деление на ноль невозможно";
				Task.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				return;
			}
			if (Number.find("-nan(ind)") != FIND_FALSE_) {
				Number = "Неверный ввод";
				Task.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				return;
			}
			Task += '=';
		}

		//Инженерный калькулятор в 2 системе счесления
		else if (IngCalsystem[2]) {
			string buff = Task;
			bintodec(buff);
			ReplaceConst(buff);

			// Вычиляет после 2 равно, удобно
			if (buff.rfind('=') != FIND_FALSE_) {
				buff = Сalculator(buff.substr(buff.rfind('=') + 1));
			}
			else {
				buff = Сalculator(buff);
			}
			//Если во время вычелений вышло /0
			if (buff.find("inf") != FIND_FALSE_) {
				Number = "Деление на ноль невозможно";
				Task.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				return;
			}
			if (buff.find("-nan(ind)") != FIND_FALSE_ || buff.find("-inf") != FIND_FALSE_) {
				Number = "Неверный ввод";
				Task.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				return;
			}
			dectobin(buff);
			Number = buff;
			if (Number.empty())
				Number = "Ответ меньше 1(";
			Task += '=';
		}

		AfterOperation = true;
	}

	// sin
	if (InButtonZone(Cursore, IngCalculatorButtons[0][26]))
		ArithmeticFuncEnter(Task, Number, "sin");
	// asin
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][27]))
		ArithmeticFuncEnter(Task, Number, "asin");
	// cos
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][28]))
		ArithmeticFuncEnter(Task, Number, "cos");
	// acos
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][29]))
		ArithmeticFuncEnter(Task, Number, "acos");
	// tg
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][30]))
		ArithmeticFuncEnter(Task, Number, "tg");
	// atg
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][31]))
		ArithmeticFuncEnter(Task, Number, "atg");
	// ctg
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][32]))
		ArithmeticFuncEnter(Task, Number, "ctg");
	// actg
	else if (InButtonZone(Cursore, IngCalculatorButtons[0][33]))
		ArithmeticFuncEnter(Task, Number, "actg");

	// Уникальные кнопки для 10 и 16 системы
	if (!IngCalsystem[2]) {
		// 7
		if (InButtonZone(Cursore, IngCalculatorButtons[0][34]))
			AddSymb(Number, "7", AfterOperation);
		// 8
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][35]))
			AddSymb(Number, "8", AfterOperation);
		// 9
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][36]))
			AddSymb(Number, "9", AfterOperation);
		// 4
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][37]))
			AddSymb(Number, "4", AfterOperation);
		// 5
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][38]))
			AddSymb(Number, "5", AfterOperation);
		// 6
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][39]))
			AddSymb(Number, "6", AfterOperation);
		// 1
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][40]))
			AddSymb(Number, "1", AfterOperation);
		// 2
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][41]))
			AddSymb(Number, "2", AfterOperation);
		// 3
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][42]))
			AddSymb(Number, "3", AfterOperation);
		// +/-
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][43])) {
			if (Number.size() >= 1 && Number.find('-') != FIND_FALSE_) {
				Number.erase(Number.find('-'), 1);
			}
			else if (Number[0] != '0') {
				if (Number.find('(')!=FIND_FALSE_) 
					Number.insert(Number.find('(') + 1, "-");
				else if (Number.find('|') != FIND_FALSE_) 
					Number.insert(Number.find('|') + 1, "-");
				else 
					Number.insert(0, "-");
			}
		}
		// 0
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][44])) {
			if (AfterOperation) {
				Number = '0';
				AfterOperation = false;
			}
			else if (Number[0] != '0' || AfterOperation || Number.find('.') != FIND_FALSE_)
				Number += '0';
		}
		// .
		else if (InButtonZone(Cursore, IngCalculatorButtons[0][45]) && !IngCalsystem[0]) {
			if (Number.find('.') == FIND_FALSE_ ) {
				Number.insert(Number.size(), ".");
			}
			else {
				Number.erase(Number.find('.'), 1);
			}
		}
		// Уникальные Кнопки 16-ричной системы исчесления
		if (IngCalsystem[0]) {
			if (InButtonZone(Cursore, IngCalculatorButtons[0][46]))
				AddSymb(Number, "A", AfterOperation);
			else if (InButtonZone(Cursore, IngCalculatorButtons[0][47]))
				AddSymb(Number, "B", AfterOperation);
			else if (InButtonZone(Cursore, IngCalculatorButtons[0][48]))
				AddSymb(Number, "C", AfterOperation);
			else if (InButtonZone(Cursore, IngCalculatorButtons[0][49]))
				AddSymb(Number, "D", AfterOperation);
			else if (InButtonZone(Cursore, IngCalculatorButtons[0][50]))
				AddSymb(Number, "E", AfterOperation);
			else if (InButtonZone(Cursore, IngCalculatorButtons[0][51]))
				AddSymb(Number, "F", AfterOperation);
		}
	}

	// Уникальные кнопки для 2 системы
	if (IngCalsystem[2]) {
		// 1
		if (InButtonZone(Cursore, IngCalculatorButtons[2][34]))
			AddSymb(Number, "1", AfterOperation);
		// 0
		else if (InButtonZone(Cursore, IngCalculatorButtons[2][35]))
			AddSymb(Number, "0", AfterOperation);
		// +/-
		else if (InButtonZone(Cursore, IngCalculatorButtons[2][36])) {
			if (Number.size() >= 1 && Number.find('-') != FIND_FALSE_)
				Number.erase(Number.find('-'), 1);
			else if (Number[0] != '0')
				Number.insert(0, "-");
		}
	}
}