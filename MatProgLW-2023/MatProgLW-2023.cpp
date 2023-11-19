#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//Симплекс метод
void SimplexMethod(double basis[4]);

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double basis[4] = { 0, 0, 0, 0 };            //базисные переменные
	SimplexMethod(basis);
	system("pause");
	return 0;
}

//Симплекс метод
void SimplexMethod(double basis[4])
{
	//Заполнение массивов исходных функций
	//double func_coef[4] = { 1, 1, -2, 1 };       //исходная функция
	//double limit1_coef[5] = { 1, -1, 0, 1, 10 }; //первое ограничение
	//double limit2_coef[5] = { -1, 3, 1, 0, 5 };  //второе ограничение
	//double diff_symplex[5] = { 0, 0, 0, 0, 0 };  //симлекс разности

	double func_coef[4] =	 { 1, -3, 4, -7 };       //исходная функция
	double limit1_coef[5] =	 { 1, 1, 3, 1, 10 }; //первое ограничение
	double limit2_coef[5] =	 { -2, -5, 1, 0, 5 };  //второе ограничение
	double diff_symplex[5] = { 0, 0, 0, 0, 0 };  //симлекс разности


	//Определение переменных метода
	double x = -10000;				     //базисные переменные
	double y = -10000;
	int j = 0;                                   //счетчик
	int basis_index1 = 0;                        //номера базисных переменных
	int basis_index2 = 0;                        //
	int choice = 0;
	int check = 1;
	double max_diff_symplex = -1000;             //максимальная симплекс разности
	double min_diff_symplex = 1000;              //минимальная симплекс разности
	double hostitem = 0;                         //ведущий элемент
	double host_column_item = 0;                 //элемент ведущего столбца
	int hostcolumn_index = 0;                    //номер ведущего столбца
	int hostline_index = 0;                      //номер ведущей строки
	int n = 4;                                   //Число переменных
	int m = 2;                                   //Число ограничений

	cout << "Определяем число свободных переменных как n - m, то есть число переменных - число ограничений. Оно равно " << n - m << endl;
	cout << "Число базисных переменных, которое равняется числу ограничений, равно " << m << endl;

	//Определяем базисные переменные
	for (j = 0; j < 4; j++)
	{
		if (limit2_coef[j] == 0 && limit1_coef[j] != 0)
		{
			//поиск значения базвой переменнной
			x = limit1_coef[4] / limit1_coef[j];
			basis[j] = x;
			basis_index1 = j;
			cout << "Найдена базисная переменная: x" << j + 1 << " = " << basis[j] << endl;
		}

		if (limit1_coef[j] == 0 && limit2_coef[j] != 0)
		{
			//поиск значения базвой переменнной
			x = limit2_coef[4] / limit2_coef[j];
			basis[j] = x;
			basis_index2 = j;
			cout << "Найдена базисная переменная: x" << j + 1 << " = " << basis[j] << endl;
		}
	}
	x = -10000;

	cout << "Симплекс таблица\n" << endl;
	cout << setw(26) << 0 << setw(10) << func_coef[0] << setw(10) << func_coef[1] << setw(10) << func_coef[2] << setw(10) << func_coef[3] << endl;
	cout << setw(10) << func_coef[basis_index2] << setw(5) << "x" << basis_index2 + 1 << setw(10) << basis[basis_index2] << setw(10) << limit1_coef[0] << setw(10) << limit1_coef[1] << setw(10) << limit1_coef[2] << setw(10) << limit1_coef[3] << endl;
	cout << setw(10) << func_coef[basis_index1] << setw(5) << "x" << basis_index1 + 1 << setw(10) << basis[basis_index1] << setw(10) << limit2_coef[0] << setw(10) << limit2_coef[1] << setw(10) << limit2_coef[2] << setw(10) << limit2_coef[3] << endl;

	//подсчет симплекс разности
	diff_symplex[0] = 0 - basis[basis_index1] * func_coef[basis_index1] - basis[basis_index2] * func_coef[basis_index2];
	cout << setw(22) << "Симплекс разности" << setw(4) << diff_symplex[0];

	for (j = 0; j < 4; j++)
	{
		diff_symplex[j + 1] = func_coef[j] - limit1_coef[j] * func_coef[basis_index1] - limit2_coef[j] * func_coef[basis_index2];
		cout << setw(10) << diff_symplex[j + 1];
	}

	cout << "\n\nВыберете вариант поиска:\n1) Поиск максимума функции;\n2) Поиск минимума функции;" << endl;
	cin >> choice;

	//По выбору пользователя осуществляется поиск максимума или минимума функции
	while (check > 0)
	{
		check = 0;
		//поиск симплекс разности для расчета максимума
		if (choice == 1)
		{
			max_diff_symplex = 0;

			//поиск max симлекс разности
			for (j = 1; j < 5; j++)
			{
				if (diff_symplex[j] > max_diff_symplex)
				{
					max_diff_symplex = diff_symplex[j];
					hostcolumn_index = j;
				}
			}

		}
		//поиск симплекс разности для расчета минимума
		else
		{
			min_diff_symplex = 1000;

			//поиск min симлекс разности
			for (j = 1; j < 5; j++)
			{

				if (min_diff_symplex > diff_symplex[j])
				{
					min_diff_symplex = diff_symplex[j];
					hostcolumn_index = j;
				}
			}

		}

		//определение ведущей строки
		if (basis[basis_index2] / limit1_coef[hostcolumn_index - 1] > 0 && limit1_coef[hostcolumn_index - 1] != 0)
			x = basis[basis_index2] / limit1_coef[hostcolumn_index - 1];

		if (basis[basis_index1] / limit2_coef[hostcolumn_index - 1] > 0 && limit2_coef[hostcolumn_index - 1] != 0)
			y = basis[basis_index1] / limit2_coef[hostcolumn_index - 1];

		if ((x > y && y > 0) || x < 0)
		{
			hostline_index = 2;
			hostitem = limit2_coef[hostcolumn_index - 1];
		}
		if ((x < y && x >0) || y < 0)
		{
			hostline_index = 1;
			hostitem = limit1_coef[hostcolumn_index - 1];
		}

		//определение ведущего элемента и пересчет коэффициентов ведущей строки
		if (hostline_index == 1)
		{
			//добавление нового базового элемента
			basis[hostcolumn_index - 1] = basis[basis_index1] / hostitem;

			//обновление ведущей строки
			for (j = 0; j < 4; j++)
				limit1_coef[j] = limit1_coef[j] / hostitem;

			host_column_item = limit2_coef[hostcolumn_index - 1];

			//пересчёт второй строки симплекс таблицы
			basis[basis_index2] = basis[hostcolumn_index - 1] * (-limit2_coef[hostcolumn_index - 1]) + basis[basis_index2];

			for (j = 0; j < 4; j++)
				limit2_coef[j] = limit1_coef[j] * (-host_column_item) + limit2_coef[j];

			//пересчёт строки симплекс разности и запоминание элемента ведущего столбца
			host_column_item = diff_symplex[hostcolumn_index];

			diff_symplex[0] = basis[hostcolumn_index - 1] * (-host_column_item) + diff_symplex[0];

			for (j = 0; j < 4; j++)
				diff_symplex[j + 1] = limit1_coef[j] * (-host_column_item) + diff_symplex[j + 1];

			//удаление старого базисного элемента из массива
			basis[basis_index1] = 0;
			basis_index1 = hostcolumn_index - 1;

			cout << setw(26) << 0 << setw(10) << func_coef[0] << setw(10) << func_coef[1] << setw(10) << func_coef[2] << setw(10) << func_coef[3] << endl;
			cout << setw(10) << func_coef[basis_index2] << setw(5) << "x" << basis_index2 + 1 << setw(10) << basis[basis_index2] << setw(10) << limit1_coef[0] << setw(10) << limit1_coef[1] << setw(10) << limit1_coef[2] << setw(10) << limit1_coef[3] << endl;
			cout << setw(10) << func_coef[basis_index1] << setw(5) << "x" << basis_index1 + 1 << setw(10) << basis[basis_index1] << setw(10) << limit2_coef[0] << setw(10) << limit2_coef[1] << setw(10) << limit2_coef[2] << setw(10) << limit2_coef[3] << endl;
			cout << setw(17) << "Симплекс разности" << setw(9);

			//проверка на последующую итерацию
			if (choice == 1)
			{
				for (j = 0; j < 5; j++)
				{
					cout << diff_symplex[j] << setw(10);
					if (diff_symplex[j] > 0)
						check++;
				}
				cout << "\n\n\n";
			}
			else
			{
				for (j = 0; j < 5; j++)
				{
					cout << diff_symplex[j] << setw(10);
					if (diff_symplex[j] < 0)
						check++;
				}
				cout << "\n\n\n";
			}


		}
		if (hostline_index == 2)
		{
			//добавление нового базового элемента
			basis[hostcolumn_index - 1] = basis[basis_index2] / limit2_coef[hostcolumn_index - 1];

			//обновление ведущей строки
			for (j = 0; j < 4; j++)
				limit2_coef[j] = limit2_coef[j] / hostitem;

			host_column_item = limit1_coef[hostcolumn_index - 1];

			//пересчёт первой строки симплекс таблицы
			basis[basis_index1] = basis[hostcolumn_index - 1] * (-host_column_item) + basis[basis_index1];

			for (j = 0; j < 4; j++)
				limit1_coef[j] = limit2_coef[j] * (-host_column_item) + limit1_coef[j];

			//пересчёт строки симплекс разности и запоминание элемента ведущего столбца
			host_column_item = diff_symplex[hostcolumn_index];

			diff_symplex[0] = basis[hostcolumn_index - 1] * (-host_column_item) + diff_symplex[0];

			for (j = 0; j < 4; j++)
				diff_symplex[j + 1] = limit2_coef[j] * (-host_column_item) + diff_symplex[j + 1];

			//удаление старого базисного элемента из массива
			basis[basis_index2] = 0;
			basis_index2 = hostcolumn_index - 1;

			cout << setw(26) << 0 << setw(10) << func_coef[0] << setw(10) << func_coef[1] << setw(10) << func_coef[2] << setw(10) << func_coef[3] << endl;
			cout << setw(10) << func_coef[basis_index2] << setw(5) << "x" << basis_index2 + 1 << setw(10) << basis[basis_index2] << setw(10) << limit1_coef[0] << setw(10) << limit1_coef[1] << setw(10) << limit1_coef[2] << setw(10) << limit1_coef[3] << endl;
			cout << setw(10) << func_coef[basis_index1] << setw(5) << "x" << basis_index1 + 1 << setw(10) << basis[basis_index1] << setw(10) << limit2_coef[0] << setw(10) << limit2_coef[1] << setw(10) << limit2_coef[2] << setw(10) << limit2_coef[3] << endl;
			cout << setw(17) << "Симплекс разности" << setw(9);

			for (j = 0; j < 5; j++)
				cout << diff_symplex[j] << setw(10);
			cout << "\n\n\n";

			//проверка на последующую итерацию
			if (choice == 1)
			{
				for (j = 1; j < 5; j++)
					if (diff_symplex[j] > 0)
						check++;

				cout << endl << endl;
			}
			else
			{
				for (j = 1; j < 5; j++)
					if (diff_symplex[j] < 0)
						check++;
				cout << endl << endl;
			}
		}
	}

	//вывод результата работы метода в виде значения функции и точки, в которой оно достигается
	cout << "Для исходной функции" << endl;
	if (choice == 1)
	{
		cout << "Максимум функции = " << -diff_symplex[0] << endl;
		cout << "В точке ( ";
		for (j = 0; j < 4; j++)
		{
			if (j != 3)
				cout << basis[j] << ", ";
			else
				cout << basis[j] << " ";
		}
		cout << ")" << endl;
	}
	if (choice == 2)
	{
		cout << "Минимум функции = " << -diff_symplex[0] << endl;
		cout << "В точке ( ";
		for (j = 0; j < 4; j++)
		{
			if (j != 3)
				cout << basis[j] << ", ";
			else
				cout << basis[j] << " ";
		}
		cout << ")" << endl;
	}
}
