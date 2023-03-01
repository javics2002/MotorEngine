#pragma once

#ifndef UTILS_VECTOR3;
#define UTILS_VECTOR3;

#include <ostream>
#include <math.h>
#include <cmath>

template<typename T = float>
class Vector3
{

private:

	/**
	* Returns the linear interpolation between "a" and "b" by a factor of "f"
	*
	* @param a The starting value of the interpolation
	* @param b The ending value of the interpolation
	* @param f The factor by which to interpolate between "a" and "b"
	* @return The linear interpolation between "a" and "b" by a factor of "f"
	*/
	float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	const float M_PI_CONST = 3.141592653589793238462;

public:
	T x, y, z;


	Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(T a, T b, T c) {
		x = a;
		y = b;
		z = c;
	}

	Vector3(const Vector3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	/**
	* Returns the difference between this vector and another vector
	*
	* @param v The other vector to subtract from this vector
	* @return The difference between this vector and the other vector
	*/
	Vector3<T> operator-(const Vector3& v);


	/**
	* Returns the difference between this vector and another vector
	*
	* @param v The other vector to subtract from this vector
	* @return The difference between this vector and the other vector
	*/
	Vector3<T> operator-=(const Vector3& v);


	/**
	* Returns the sum of this vector and another vector
	*
	* @param v The other vector to add to this vector
	* @return The sum of this vector and the other vector
	*/
	Vector3<T> operator+(const Vector3& v);


	/**
	* Returns the sum of this vector and another vector
	*
	* @param v The other vector to add to this vector
	* @return The sum of this vector and the other vector
	*/
	Vector3<T> operator+=(const Vector3& v);


	/**
	* Returns the product of this vector and a scalar
	*
	* @param s The scalar to multiply this vector by
	* @return The product of this vector and the scalar
	*/
	Vector3<T> operator*(const T& s);


	/**
	* Returns the product of this vector and a scalar
	*
	* @param s The scalar to multiply this vector by
	* @return The product of this vector and the scalar
	*/
	Vector3<T> operator*=(const T& s);



	/**
	*  Check if this vector is equal to another vector "v"
	*
	*  @param v The other vector to check equality with
	*  @return True if the two vectors are equal, false otherwise
	*/
	void operator=(const Vector3<T>& v);


	/**
	*  Check if this vector is equal to another vector "v"
	*
	*  @param v The other vector to check equality with
	*  @return True if the two vectors are equal, false otherwise
	*/
	void operator=(const Vector3<T>* v);


	/**
	*  Check if this vector is equal to another vector "v"
	*
	*  @param v The other vector to check equality with
	*  @return True if the two vectors are equal, false otherwise
	*/
	bool operator==(const Vector3<T>& v);


	/**
	*  Check if this vector is not equal to another vector "v"
	*
	*  @param v The other vector to check inequality with
	*  @return True if the two vectors are not equal, false otherwise
	*/
	bool operator!=(const Vector3<T>& v);



	/**
	*  Returns the linear interpolation between "a" and "b" by a factor of "f"
	*
	*  @param a The starting vector to interpolate from
	*  @param b The ending vector to interpolate to
	*  @param f The interpolation factor, a value between 0 and 1
	*/
	Vector3<T> lerp(const Vector3<T>& a, const Vector3<T>& b, float f);


	/**
	*  Calculate the magnitude (length) of the vector
	*
	*  @return The magnitude of the vector
	*/
	T magnitude();


	/**
	*  Normalize the vector to have a magnitude of 1
	*/
	void normalize();



	/**
	*  Calculate the dot product between this vector and another vector "v"
	*
	*  @param v The other vector to calculate the dot product with
	*  @return The dot product of the two vectors
	*/
	T dot(const Vector3<T>& v);


	/**
	*  Calculate the cross product between this vector and another vector "v"
	*
	*  @param v The other vector to calculate the cross product with
	*  @return The cross product of the two vectors
	*/
	Vector3<T> cross(const Vector3<T>& v);
	



	/**
	*  Returns a zero vector
	*/
	Vector3<T> zero();


	/**
	*  Returns a unit vector pointing upwards along the y-axis
	*/
	Vector3<T> up();


	/**
	*  Returns a unit vector pointing downwards along the y-axis
	*/
	Vector3<T> down();


	/**
	*  Returns a unit vector pointing to the left along the x-axis
	*/
	Vector3<T> left();


	/**
	*  Returns a unit vector pointing to the right along the x-axis
	*/
	Vector3<T> rigth();

	/**
	*  Returns a unit vector pointing backwards along the z-axis
	*/
	Vector3<T> back();


	/**
	*  Returns a unit vector pointing forwards along the z-axis
	*/
	Vector3<T> forward();


	/**
	*  Returns the distance between this vector and another vector "v"
	*
	*  @param v The other vector
	*  @return The distance between the two vectors
	*/
	T distance(const Vector3<T>& v);


	/**
	*  Returns the angle between this vector and another vector "v"
	*
	*  @param v The other vector
	*  @return The angle between the two vectors in degrees
	*/
	T angle(const Vector3<T>& v);



	/**
	*  Returns a formatted string representation of the vector
	*
	*  @param os The output stream to write to
	*  @param v The vector to format
	*  @return The output stream with the formatted string
	*/
	friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& v);

	
};

#endif