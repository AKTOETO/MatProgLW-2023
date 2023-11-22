#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template<class Ty>
struct vec3
{
	Ty x;
	Ty y;
	Ty z;

	double len()
	{
		return(sqrt(x * x + y * y + z * z));
	}

	vec3<Ty> normalize()
	{
		return (len() > 0 ? *this / len() : vec3<Ty>{ 0,0,0 });
	}

	template<class Ty>
	friend ostream& operator<<(ostream& out, const vec3<Ty>& vec)
	{
		return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	}

	template<class Ty>
	friend vec3<Ty> operator-(const vec3<Ty>& vec, const vec3<Ty>& vec2)
	{
		return { vec.x - vec2.x, vec.y - vec2.y, vec.z - vec2.z };
	}

	template<class Ty>
	friend vec3<Ty> operator+(const vec3<Ty>& vec, const vec3<Ty>& vec2)
	{
		return { vec2.x + vec.x, vec2.y + vec.y, vec2.z + vec.z };
	}

	template<class Ty>
	friend vec3<Ty> operator*(const Ty& num, const vec3<Ty>& vec)
	{
		return { vec.x * num, vec.y * num, vec.z * num };
	}

	template<class Ty>
	friend vec3<Ty> operator*(const vec3<Ty>& vec, const Ty& num)
	{
		return { vec.x * num, vec.y * num, vec.z * num };
	}

	template<class Ty>
	friend vec3<Ty> operator/(const vec3<Ty>& vec, const Ty& num)
	{
		return { vec.x / num, vec.y / num, vec.z / num };
	}

	template<class Ty>
	friend vec3<Ty> operator/(const Ty& num, const vec3<Ty>& vec)
	{
		return { num / vec.x, num / vec.y , num / vec.z };
	}
};

using vec3d = vec3<double>;

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
	// return 8 * vec.x + vec.z + 2 * vec.y - 6;
	return (func(vec + vec3d{ 1,0,0 }) - func(vec - vec3d{ 1,0,0 })) / 2;
}

// производная по второй переменной
double der_x2(vec3d vec)
{
	// return 4 * vec.y + 2 * vec.x;
	return (func(vec + vec3d{ 0,1,0 }) - func(vec - vec3d{ 0,1,0 })) / 2;
}

// производная по третей переменной
double der_x3(vec3d vec)
{
	// return 4 * vec.z + vec.x - 8;
	return (func(vec + vec3d{ 0,0,1 }) - func(vec - vec3d{ 0,0,1 })) / 2;
}

// расчет вектора градиента
vec3d grad(vec3d vec)
{
	return{ der_x1(vec), der_x2(vec), der_x3(vec) };
}

// печать шапки таблицы
void print_table_header()
{
	cout << " >> Градиентный спуск с оптимизацией по шагу:\n";
	cout << setw(10) << left << "Итерация"
		<< setw(10) << left << "x"
		<< setw(10) << left << "y"
		<< setw(10) << left << "z"
		<< setw(16) << left << "||gradf(x)||"
		<< setw(12) << left << "step"
		<< endl;
}

// печать строки таблицы
void print_table_string(
	int count,
	vec3d x0,
	double step
)
{
	cout << setw(10) << left << ++count
		<< setw(10) << left << setprecision(4) << fixed << x0.x
		<< setw(10) << left << setprecision(4) << fixed << x0.y
		<< setw(10) << left << setprecision(4) << fixed << x0.z
		<< setw(16) << left << defaultfloat << grad(x0).len()
		<< setw(12) << left << step
		<< endl;
}

// расчет шага для текущей функции наискорейшим методом 
double argmin_f(const vec3d& vec)
{
	// антиградиент функции
	auto anti_gr = (-1.)*grad(vec).normalize();

	// в f подставляем x-t*grad заместо x f(x-t*grad) 
	// и упрощаем полученное выражение.
	// результат дифферинцируем по t, приравниваем к 0, 
	// выводим t(типо так: t = ..., t будет равна дроби)

	double numerator =
		6 * vec.x * anti_gr.x + 4 * vec.y * anti_gr.y - vec.x * anti_gr.y - 
		anti_gr.x * vec.y - 5 * anti_gr.x + 2 * vec.z * anti_gr.z + 
		vec.y * anti_gr.z + vec.z * anti_gr.y - 6 * anti_gr.z;

	double denumerator =
		-6 * anti_gr.x * anti_gr.x - 4 * anti_gr.y * anti_gr.y +
		2 * anti_gr.x * anti_gr.y - 2 * anti_gr.z * anti_gr.z +
		2 * anti_gr.x * anti_gr.z;

	return numerator / denumerator;
}

void find_extr(vec3d x0)
{
	double eps = 0.001;
	int count = 0;
	double step = 1;

	print_table_header();

	while (grad(x0).len() > eps)
	{
		step = argmin_f(x0);
		x0 = x0 - step * grad(x0).normalize();

		print_table_string(count++, x0, step);
	}

	cout << "\nПолученная точка экстремума: " << x0 << endl;
	cout << "Количество итераций: " << count << endl;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	find_extr({ 0,0,0 });
}
