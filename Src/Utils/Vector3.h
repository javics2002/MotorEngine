#pragma once

#ifndef UTILS_VECTOR3;
#define UTILS_VECTOR3;

#include <ostream>
#include <math.h>
#include <cmath>

template<typename T = float>
class Vector3
{

private:

	/**
	* Returns the linear interpolation between "a" and "b" by a factor of "f"
	*
	* @param a The starting value of the interpolation
	* @param b The ending value of the interpolation
	* @param f The factor by which to interpolate between "a" and "b"
	* @return The linear interpolation between "a" and "b" by a factor of "f"
	*/
	float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	const float M_PI_CONST = 3.141592653589793238462;

public:
	T x, y, z;


	Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(T a, T b, T c) {
		x = a;
		y = b;
		z = c;
	}

	Vector3(const Vector3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}


	Vector3<T> operator-(const Vector3& v);
	Vector3<T> operator+(const Vector3& v);
	Vector3<T> operator*(const T& s);

	bool operator==(const Vector3<T>& v);
	bool operator!=(const Vector3<T>& v);

	Vector3<T> lerp(const Vector3<T>& a, const Vector3<T>& b, float f);

	T magnitude();
	void normalize();

	T dot(const Vector3<T>& v);
	Vector3<T> cross(const Vector3<T>& v);

	Vector3<T> zero();
	Vector3<T> up();
	Vector3<T> down();
	Vector3<T> left();
	Vector3<T> rigth();
	Vector3<T> back();
	Vector3<T> forward();

	T distance(const Vector3<T>& v);
	T angle(const Vector3<T>& v);


	friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& v);

	
};

#endif