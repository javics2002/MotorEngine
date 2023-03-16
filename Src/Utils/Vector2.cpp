#include "Vector2.h"

Vector2 Vector2::operator+(const  Vector2& v) {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const  Vector2& v) {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const  float v) {
	return Vector2(x * v, y * v);
}