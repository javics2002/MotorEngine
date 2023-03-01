#include "Vector4.h"



template< typename T>
float Vector4<T>::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

template<typename T>
Vector4<T> Vector4<T>::lerp(const Vector4<T>& a, const Vector4<T>& b, float f)
{
	return Vector4(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f), lerp(a.w, b.w, f));
}

