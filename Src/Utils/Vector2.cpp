#include "Vector2.h"


template<typename T>
Vector2<T> Vector2<T>::operator+(const  Vector2<T>& s) {
	return Vector2<T>(x + v.x, y + v.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const  Vector2<T>& s) {
	return Vector2<T>(x - v.x, y - v.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const  T s) {
	return Vector2<T>(x * s, y * s);
}