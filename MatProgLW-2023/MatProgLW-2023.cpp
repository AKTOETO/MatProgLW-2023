#include <iomanip>
#include "math.h"

double func(vec3d vec)
{
	return (
		-3 * vec.x * vec.x - 2 * vec.y * vec.y + vec.x * vec.y +
		5 * vec.x - vec.z * vec.z - vec.y * vec.z + 6 * vec.z
		);
}

// производная по первой переменной
double der_x1(vec3d vec)
{
	return -6 * vec.x + vec.y + 5;
	//return (func(vec + vec3d{ 1,0,0 }) - func(vec - vec3d{ 1,0,0 })) / 2;
}

// производная по второй переменной
double der_x2(vec3d vec)
{
	return -4 * vec.y + vec.x - vec.z;
	//return (func(vec + vec3d{ 0,1,0 }) - func(vec - vec3d{ 0,1,0 })) / 2;
}

// производная по третей переменной
double der_x3(vec3d vec)
{
	return -2 * vec.z - vec.y + 6;
	//return (func(vec + vec3d{ 0,0,1 }) - func(vec - vec3d{ 0,0,1 })) / 2;
}

// расчет вектора градиента
vec3d grad(vec3d vec)
{
	return vec3d({ der_x1(vec), der_x2(vec), der_x3(vec) });
}

// печать шапки таблицы
void print_table_header()
{
	cout << " >> Метод сопряженных градиентов:\n";
	cout << setw(10) << left << "Итерация"
		<< setw(10) << left << "x"
		<< setw(10) << left << "y"
		<< setw(10) << left << "z"
		<< setw(16) << left << "||gradf(x)||"
		<< endl;
}

// печать строки таблицы
void print_table_string(
	int count,
	vec3d x0,
	double step = -1
)
{
	cout << setw(10) << left << ++count
		<< setw(10) << left << setprecision(4) << fixed << x0.x
		<< setw(10) << left << setprecision(4) << fixed << x0.y
		<< setw(10) << left << setprecision(4) << fixed << x0.z
		<< setw(16) << left << defaultfloat << grad(x0).len();
	if (step != -1)
		cout << setw(12) << left << step;

	cout << endl;

}

// расчет шага для текущей функции наискорейшим методом 
double argmin_f(const vec3d& vec, const vec3d& gr)
{
	// в f подставляем x-t*grad заместо x f(x-t*grad) 
	// и упрощаем полученное выражение.
	// результат дифферинцируем по t, приравниваем к 0, 
	// выводим t(типо так: t = ..., t будет равна дроби)

	double numerator =
		6 * vec.x * gr.x + 4 * vec.y * gr.y - vec.x * gr.y -
		gr.x * vec.y - 5 * gr.x + 2 * vec.z * gr.z +
		vec.y * gr.z + vec.z * gr.y - 6 * gr.z;

	double denumerator =
		-6 * gr.x * gr.x - 4 * gr.y * gr.y +
		2 * gr.x * gr.y - 2 * gr.z * gr.z +
		2 * gr.x * gr.z;

	return numerator / denumerator;
}

void find_extr(vec3d x0)
{
	double eps = 0.001;
	int count = 0;
	vec3d xprev = x0;
	vec3d pk = grad(x0);
	double step = argmin_f(x0, pk);

	print_table_header();

	while (grad(x0).len() > eps)
	{
		xprev = x0;

		x0 = x0 + step * pk;
		pk = grad(x0) + (pow(grad(x0).len(), 2) / pow(grad(xprev).len(), 2)) * pk;
		step = argmin_f(x0, pk);

		print_table_string(count++, x0);
	}

	cout << "\nПолученная точка экстремума: " << x0 << endl;
	cout << "Количество итераций: " << count << endl;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	find_extr({ 0,0,3 });
}
