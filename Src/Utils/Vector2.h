#pragma once

#ifndef __UTILS_VECTOR2
#define __UTILS_VECTOR2

#include "MotorEngine/MotorEngineAPI.h"
#include "SimpleLerp.h"

namespace me {
	/**
	Class Vector2: Holds two values, x and y. Most often used to represent UI coordinates.
	*/
	class __MOTORENGINE_API Vector2
	{
	public:
		float x, y;

		/**
		*  Construct  default Vector2
		*/
		Vector2();

		/**
		*  Construct a new Vector2 with given x, y components
		*  @param a Vector2 first element
		*  @param b Vector2 second element
		*/
		Vector2(float a, float b);

		/**
		*  Construct a new Vector2 with given another Vector2
		*  @param v new Vector2
		*/
		Vector2(const Vector2& v);

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
		Vector2 lerp(const Vector2 a, const Vector2 b, float f);

	};
}
#endif