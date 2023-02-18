//TODO Pasar a cpp!!!
#pragma once

#ifndef __UTILS_VECTOR2
#define __UTILS_VECTOR2

/**
*	Class Vector2 for represent the UI
*/

template<typename T = float>

class Vector2
{

private:

	float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

public:

	T x , y;

	/**
	*  Construct  default Vector2
	*/
	Vector2() { 
		x = 0;
		y = 0;
	}

	/**
	*  Construct a new Vector2 with given x, y components
	*  @param a Vector2 first element
	*  @param b Vector2 second element
	*/
	Vector2(T a, T b) {
		x = a;
		y = b;
	}

	/**
	*  Construct a new Vector2 with given another Vector2
	*  @param v new Vector2
	*/
	Vector2(const Vector2<T>& v) {
		x = v.x;
		y = v.y;
	}

	/**
	*  Return the sum of two Vector2
	*  @param v Vector2
	*/
	Vector2<T> operator+(const Vector2<T> v) {
		return Vector2<T>(x + v.x, y + v.y);
	}

	/**
	*  Return the difference of two Vector2
	*  @param v Vector2
	*/
	Vector2<T> operator-(const Vector2<T> v) {
		return Vector2<T>(x - v.x, y - v.y);
	}

	/**
	*  Return a  Vector2 scale
	*  @param s scale factor
	*/
	Vector2<T> operator*(const T s) {
		return Vector2<T>(x * s, y * s);
	}

	/**
	*  Returns a new Vector2 interpolating between the two given Vector2 based on the scalar value "f".
	*  @param a first Vector2
	*  @param b second Vector2
	*  @param f interpolation factor
	*/
	Vector2<T> lerp(const Vector2<T> a, const Vector2<T> b, float f) {
		return Vector2<T>( lerp(a.x, b.x, f), lerp(a.y, b.y, f));
	}

};

#endif