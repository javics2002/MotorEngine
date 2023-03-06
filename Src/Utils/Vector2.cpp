#include "Vector2.h"


template<typename T>
Vector2<T> Vector2<T>::operator+(const  Vector2<T>& v) {
	return Vector2<T>(x + v.x, y + v.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const  Vector2<T>& v) {
	return Vector2<T>(x - v.x, y - v.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const  T v) {
	return Vector2<T>(x * v, y * v);
}