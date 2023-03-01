#include "Vector3.h"

using namespace me;

template<typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3& v)
{
	return Vector3<T>(x - v.x, y - v.y, z - v.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-=(const Vector3& v)
{
	return Vector3<T>(x - v.x, y - v.y, z - v.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3& v)
{
	return Vector3<T>(x + v.x, y + v.y, z + v.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator+=(const Vector3& v)
{
	return Vector3<T>(x + v.x, y + v.y, z + v.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*(const T& s)
{
	return Vector3<T>(x * s, y * s, z * s);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*=(const T& s)
{
	return Vector3<T>(x * s, y * s, z * s);
}

template<typename T>
inline  void Vector3<T>::operator=(const Vector3<T>& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

template<typename T>
void Vector3<T>::operator=(const Vector3<T>* v)
{
	x = v->x;
	y = v->y;
	z = v->z;
}

template<typename T>
inline bool Vector3<T>::operator==(const Vector3<T>& v)
{
	return (x == v.x && y == v.y && z == v.z);
}

template<typename T>
inline bool Vector3<T>::operator!=(const Vector3<T>& v)
{
	return (x != v.x || y != v.y || z != v.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::lerp(const Vector3<T>& a, const Vector3<T>& b, float f)
{
	return Vector3<T>(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f));
}

template<typename T>
inline T Vector3<T>::magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

template<typename T>
inline void Vector3<T>::normalize()
{
	// Calculate the magnitude of the vector
	T m = magnitude();

	// Divide the vector components by the magnitude to normalize the vector
	x = x / m;
	y = y / m;
	z = z / m;
}

template<typename T>
inline T Vector3<T>::dot(const Vector3<T>& v)
{
	return (x * v.x + y * v.y + z * v.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::cross(const Vector3<T>& v)
{
	return Vector3<T>((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

template<typename T>
inline Vector3<T> Vector3<T>::zero()
{
	return Vector3<T>(0, 0, 0);
}

template<typename T>
inline Vector3<T> Vector3<T>::up()
{
	return Vector3<T>(0, 1, 0);
}

template<typename T>
inline Vector3<T> Vector3<T>::down()
{
	return Vector3<T>(0, -1, 0);
}

template<typename T>
inline Vector3<T> Vector3<T>::left()
{
	return Vector3<T>(-1, 0, 0);
}

template<typename T>
inline Vector3<T> Vector3<T>::rigth()
{
	return Vector3<T>(1, 0, 0);
}

template<typename T>
inline Vector3<T> Vector3<T>::back()
{
	return Vector3<T>(0, 0, -1);
}

template<typename T>
inline Vector3<T> Vector3<T>::forward()
{
	return Vector3<T>(0, 0, 1);
}

template<typename T>
inline T Vector3<T>::distance(const Vector3<T>& v)
{
	return Vector3<T>(v.x - x, v.y - y, v.z - z).magnitude();
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
{
	os << "Vector3(" << v.x << ',' << v.y << ',' << v.z << ")";
	return os;
}

template<typename T>
inline T Vector3<T>::angle(const Vector3<T>& v)
{
	return acos(scalarProduct(v) / sqrt(magnitude() * v.magnitude())) * 180 / M_PI_CONST;
}

template<typename T>
Ogre::Vector3f me::Vector3<T>::v3ToOgreV3()
{
	return Ogre::Vector3f(x, y, z);
}

template<typename T>
btVector3 me::Vector3<T>::v3ToBulletV3()
{
	return btVector3(x, y, z);
}