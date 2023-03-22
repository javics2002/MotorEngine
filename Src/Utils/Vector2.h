//TODO Pasar a cpp!!!
#pragma once

#ifndef __UTILS_VECTOR2
#define __UTILS_VECTOR2

#include "MotorEngine/MotorEngineAPI.h"

/**
*	Class Vector2 for represent the UI
*/

class __MOTORENGINE_API Vector2
{

private:

	float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

public:

	float x , y;

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
	Vector2(float a, float b) {
		x = a;
		y = b;
	}

	/**
	*  Construct a new Vector2 with given another Vector2
	*  @param v new Vector2
	*/
	Vector2(const Vector2& v) {
		x = v.x;
		y = v.y;
	}

	/**
	*  Return the sum of two Vector2
	*  @param v Vector2
	*/
	Vector2 operator+(const Vector2& v);

	/**
	*  Return the difference of two Vector2
	*  @param v Vector2
	*/
	Vector2 operator-(const Vector2& v);

	/**
	*  Return a  Vector2 scale
	*  @param s scale factor
	*/
	Vector2 operator*(const float s);

	/**
	*  Returns a new Vector2 interpolating between the two given Vector2 based on the scalar value "f".
	*  @param a first Vector2
	*  @param b second Vector2
	*  @param f interpolation factor
	*/
	inline Vector2 lerp(const Vector2 a, const Vector2 b, float f) {
		return Vector2( lerp(a.x, b.x, f), lerp(a.y, b.y, f));
	}

};

#endif