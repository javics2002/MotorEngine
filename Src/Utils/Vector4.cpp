#include "Vector4.h"


float Vector4::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

Vector4 Vector4::lerp(const Vector4& a, const Vector4& b, float f)
{
	return Vector4(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f), lerp(a.w, b.w, f));
}

