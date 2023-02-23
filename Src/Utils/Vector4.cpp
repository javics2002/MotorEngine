#include "Vector4.h"



/**
* Returns the linear interpolation between "a" and "b" by a factor of "f"
*
* @param a The starting value of the interpolation
* @param b The ending value of the interpolation
* @param f The factor by which to interpolate between "a" and "b"
* @return The linear interpolation between "a" and "b" by a factor of "f"
*/
template< typename T>
float Vector4<T>::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

/**
*  Returns the linear interpolation between "a" and "b" by a factor of "f"
*
*  @param a The starting vector to interpolate from
*  @param b The ending vector to interpolate to
*  @param f The interpolation factor, a value between 0 and 1
*/
template<typename T>
Vector4<T> Vector4<T>::lerp(const Vector4<T>& a, const Vector4<T>& b, float f)
{
	return Vector4(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f), lerp(a.w, b.w, f));
}

