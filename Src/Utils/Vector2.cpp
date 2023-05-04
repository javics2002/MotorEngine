#include "Vector2.h"

using namespace me;

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float a, float b) {
	x = a;
	y = b;
}

Vector2::Vector2(const Vector2& v) {
	x = v.x;
	y = v.y;
}

Vector2 Vector2::operator+(const  Vector2& v) {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const  Vector2& v) {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const  float v) {
	return Vector2(x * v, y * v);
}

Vector2 Vector2::lerp(const Vector2 a, const Vector2 b, float f)
{
	return Vector2(SimpleLerp::Lerp(a.x, b.x, f), SimpleLerp::Lerp(a.y, b.y, f));
}
