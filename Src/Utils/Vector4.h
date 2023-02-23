#pragma once

#ifndef UTILS_VECTOR3;
#define UTILS_VECTOR3;


template< typename T = float>
class Vector4
{

private:

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

	Vector4<T> lerp(const Vector4<T>& a, const Vector4<T>& b, float f);
};

#endif
