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
	return (4 * vec.x * vec.x + 2 * vec.y * vec.y + 2 * vec.z * vec.z + vec.x * vec.z + 2 * vec.x * vec.y - 6 * vec.x - 8 * vec.z);
}

double der_x1(vec3d vec)
{
	return (func(vec + vec3d{ 1,0,0 }) - func(vec - vec3d{ 1,0,0 })) / 2;
}

double der_x2(vec3d vec)
{
	return (func(vec + vec3d{ 0,1,0 }) - func(vec - vec3d{ 0,1,0 })) / 2;
}

double der_x3(vec3d vec)
{
	return (func(vec + vec3d{ 0,0,1 }) - func(vec - vec3d{ 0,0,1 })) / 2;
}

vec3d grad(vec3d vec)
{
	return{ der_x1(vec), der_x2(vec), der_x3(vec) };
}

void grad_step(vec3d x0)
{
	double eps = 0.001;
	int count = 0;
	double step = 0.5;

	double curf = func(x0);
	double newf = 0;

	cout << " >> Градиентный спуск с дроблением шага:\n";
	cout << setw(10) << left << "Итерация"
		<< setw(10) << left << "x"
		<< setw(10) << left << "y"
		<< setw(10) << left << "z"
		<< setw(16) << left << "||gradf(x)||"
		<< setw(12) << left << "f(prev)"
		<< setw(12) << left << "f(now)"
		<< setw(12) << left << "step"
		<< endl;

	while (grad(x0).len() > eps)
	{
		curf = func(x0);

		x0 = x0 - step * grad(x0).normalize();

		newf = func(x0);

		if (curf < newf)step *= 0.5;

		cout << setw(10) << left << ++count
			<< setw(10) << left << setprecision(4)<<fixed << x0.x
			<< setw(10) << left << setprecision(4)<<fixed << x0.y
			<< setw(10) << left << setprecision(4)<<fixed << x0.z
			<< setw(16) << left << defaultfloat << grad(x0).len()
			<< setw(12) << left << curf
			<< setw(12) << left << newf
			<< setw(12) << left << step
			<< endl;
	}

	cout << "\nПолученная точка экстремума: " << x0 << endl;
	cout << "Количество итераций: " << count << endl;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	grad_step({ 0,0,0 });
}
