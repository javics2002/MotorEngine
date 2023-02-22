#include "Vector3.h"

/**
* Returns the difference between this vector and another vector
*
* @param v The other vector to subtract from this vector
* @return The difference between this vector and the other vector
*/
template<typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3& v)
{
	return Vector3<T>(x - v.x, y - v.y, z - v.z);
}

/**
* Returns the sum of this vector and another vector
*
* @param v The other vector to add to this vector
* @return The sum of this vector and the other vector
*/
template<typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3& v)
{
	return Vector3<T>(x + v.x, y + v.y, z + v.z);
}

/**
* Returns the product of this vector and a scalar
*
* @param s The scalar to multiply this vector by
* @return The product of this vector and the scalar
*/
template<typename T>
inline Vector3<T> Vector3<T>::operator*(const T& s)
{
	return Vector3<T>(x * s, y * s, z * s);
}


/**
*  Returns the linear interpolation between "a" and "b" by a factor of "f"
*
*  @param a The starting vector to interpolate from
*  @param b The ending vector to interpolate to
*  @param f The interpolation factor, a value between 0 and 1
*/
template<typename T>
inline Vector3<T> Vector3<T>::lerp(const Vector3<T>& a, const Vector3<T>& b, float f)
{
	return Vector3<T>(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f));
}


/**
*  Calculate the magnitude (length) of the vector
*
*  @return The magnitude of the vector
*/
template<typename T>
inline T Vector3<T>::magnitude()
{
	return sqrt(x * x + y * y + z * z);
}


/**
*  Normalize the vector to have a magnitude of 1
*/
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


/**
*  Calculate the dot product between this vector and another vector "v"
*
*  @param v The other vector to calculate the dot product with
*  @return The dot product of the two vectors
*/
template<typename T>
inline T Vector3<T>::dot(const Vector3<T>& v)
{
	return (x * v.x + y * v.y + z * v.z);
}


/**
*  Calculate the cross product between this vector and another vector "v"
*
*  @param v The other vector to calculate the cross product with
*  @return The cross product of the two vectors
*/
template<typename T>
inline Vector3<T> Vector3<T>::cross(const Vector3<T>& v)
{
	return Vector3<T>((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}


/**
*  Check if this vector is equal to another vector "v"
*
*  @param v The other vector to check equality with
*  @return True if the two vectors are equal, false otherwise
*/
template<typename T>
inline bool Vector3<T>::operator==(const Vector3<T>& v)
{
	return (x == v.x && y == v.y && z == v.z);
}


/**
*  Check if this vector is not equal to another vector "v"
*
*  @param v The other vector to check inequality with
*  @return True if the two vectors are not equal, false otherwise
*/
template<typename T>
inline bool Vector3<T>::operator!=(const Vector3<T>& v)
{
	return (x != v.x || y != v.y || z != v.z);
}


/**
*  Returns the linear interpolation between "a" and "b" by a factor of "f"
*
*  @param a
*  @param b
*/
template<typename T>
inline Vector3<T> Vector3<T>::zero()
{
	return Vector3<T>(0, 0, 0);
}

/**
*  Returns a unit vector pointing upwards along the y-axis
*/
template<typename T>
inline Vector3<T> Vector3<T>::up()
{
	return Vector3<T>(0, 1, 0);
}

/**
*  Returns a unit vector pointing downwards along the y-axis
*/
template<typename T>
inline Vector3<T> Vector3<T>::down()
{
	return Vector3<T>(0, -1, 0);
}

/**
*  Returns a unit vector pointing to the left along the x-axis
*/
template<typename T>
inline Vector3<T> Vector3<T>::left()
{
	return Vector3<T>(-1, 0, 0);
}

/**
*  Returns a unit vector pointing to the right along the x-axis
*/
template<typename T>
inline Vector3<T> Vector3<T>::rigth()
{
	return Vector3<T>(1, 0, 0);
}

/**
*  Returns a unit vector pointing backwards along the z-axis
*/
template<typename T>
inline Vector3<T> Vector3<T>::back()
{
	return Vector3<T>(0, 0, -1);
}

/**
*  Returns a unit vector pointing forwards along the z-axis
*/
template<typename T>
inline Vector3<T> Vector3<T>::forward()
{
	return Vector3<T>(0, 0, 1);
}

/**
*  Returns the distance between this vector and another vector "v"
*
*  @param v The other vector
*  @return The distance between the two vectors
*/
template<typename T>
inline T Vector3<T>::distance(const Vector3<T>& v)
{
	return Vector3<T>(v.x - x, v.y - y, v.z - z).magnitude();
}

/**
*  Returns a formatted string representation of the vector
*
*  @param os The output stream to write to
*  @param v The vector to format
*  @return The output stream with the formatted string
*/
template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
{
	os << "Vector3(" << v.x << ',' << v.y << ',' << v.z << ")";
	return os;
}


/**
*  Returns the angle between this vector and another vector "v"
*
*  @param v The other vector
*  @return The angle between the two vectors in degrees
*/
template<typename T>
inline T Vector3<T>::angle(const Vector3<T>& v)
{
	return acos(scalarProduct(v) / sqrt(magnitude() * v.magnitude())) * 180 / M_PI_CONST;
}