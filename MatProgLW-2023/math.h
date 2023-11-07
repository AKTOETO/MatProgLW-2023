#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template<class Ty>
struct vec3
{
	Ty x;
	Ty y;
	Ty z;

	constexpr double len()
	{
		return(sqrt(x * x + y * y + z * z));
	}

	constexpr vec3<Ty> normalize()
	{
		return (len() > 0 ? *this / len() : vec3<Ty>{ 0,0,0 });
	}

	template<class Ty>
	constexpr friend ostream& operator<<(ostream& out, const vec3<Ty>& vec)
	{
		return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	}

	template<class Ty>
	constexpr friend vec3<Ty> operator-(const vec3<Ty>& vec, const vec3<Ty>& vec2)
	{
		return { vec.x - vec2.x, vec.y - vec2.y, vec.z - vec2.z };
	}

	template<class Ty>
	constexpr friend vec3<Ty> operator+(const vec3<Ty>& vec, const vec3<Ty>& vec2)
	{
		return { vec2.x + vec.x, vec2.y + vec.y, vec2.z + vec.z };
	}

	template<class Ty>
	constexpr friend vec3<Ty> operator*(const Ty& num, const vec3<Ty>& vec)
	{
		return { vec.x * num, vec.y * num, vec.z * num };
	}

	template<class Ty>
	constexpr friend vec3<Ty> operator*(const vec3<Ty>& vec, const Ty& num)
	{
		return { vec.x * num, vec.y * num, vec.z * num };
	}

	template<class Ty>
	constexpr friend vec3<Ty> operator*(const vec3<Ty>& vec, const vec3<Ty>& vec2)
	{
		return { vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z };
	}

	template<class Ty>
	constexpr friend vec3<Ty> operator/(const vec3<Ty>& vec, const Ty& num)
	{
		return { vec.x / num, vec.y / num, vec.z / num };
	}

	template<class Ty>
	constexpr friend vec3<Ty> operator/(const Ty& num, const vec3<Ty>& vec)
	{
		return { num / vec.x, num / vec.y , num / vec.z };
	}
};

using vec3d = vec3<double>;

template<class Ty>
class matr
{
protected:
	vector<vector<Ty>> m_matr;

public:
	matr(int x = 3, int y = 3)
	{
		m_matr.resize(x, vector<Ty>(y, 0));
	}

	matr(const vector<vector<Ty>>& mt)
	{
		m_matr = mt;
	}

	vector<Ty> operator[](int& num) { return m_matr[num]; }

	friend matr<Ty>& operator*(matr<Ty>& mt, Ty num)
	{
		for (vector<Ty>& vec : mt.m_matr)
			for (Ty& el : vec)el *= num;
		return mt;
	}

	friend matr<Ty>& operator*(Ty num, matr<Ty>& mt)
	{
		return mt*num;
	}

	// умножение вектора на матрицу
	friend vec3<Ty> operator*(const vec3<Ty>& vec, matr<Ty>& mt)
	{
		vector<Ty> vect = { vec.x, vec.y, vec.z };
		vector<Ty> out(3, 0);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				out[i] += vect[j] * mt[i][j];
			}
		}

		return vec3<Ty>{out[0], out[1], out[2]};
	}

	// умножение вектора на матрицу
	friend vec3<Ty> operator*(matr<Ty>& mt, const vec3<Ty>& vec)
	{		
		return vec*mt;
	}
};


#endif // !MATH_H
