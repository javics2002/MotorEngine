#pragma once

#ifndef __UTILS_VECTOR4
#define __UTILS_VECTOR4


template< typename T = float>
class Vector4
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
	float lerp(float a, float b, float f);


public:

	T x, y, z, w;


	Vector4() {
		x = 1;
		y = 1;
		z = 1;
		w = 1;
	}

	Vector4(T a, T b, T c, T d) {
		x = a;
		y = b;
		z = c;
		w = d;
	}

	Vector4(const Vector4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}


	/**
	*  Returns the linear interpolation between "a" and "b" by a factor of "f"
	*
	*  @param a The starting vector to interpolate from
	*  @param b The ending vector to interpolate to
	*  @param f The interpolation factor, a value between 0 and 1
	*/
	Vector4<T> lerp(const Vector4<T>& a, const Vector4<T>& b, float f);
};

#endif
