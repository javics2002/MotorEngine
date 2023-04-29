#include "Vector3.h"

#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>
#include <fmod.hpp>
#define MY_PI 3.14159265358979323846

using namespace me;

 Vector3 Vector3::operator-(const Vector3& v)
{
	return Vector3 (x - v.x, y - v.y, z - v.z);
}

 Vector3 Vector3::operator-=(const Vector3& v)
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

 Vector3 Vector3::operator+(const Vector3& v)
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator+=(const Vector3& v)
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

 Vector3 Vector3::operator*(const float& s)
{
	return Vector3 (x * s, y * s, z * s);
}

 Vector3 Vector3::operator*(const Vector3& other)
 {
	 return Vector3(x * other.x, y * other.y, z * other.z);
 }

 Vector3 Vector3::operator*=(const float & s)
{
	return Vector3(x * s, y * s, z * s);
}

 Vector3 me::Vector3::operator/(const Vector3& other)
 {
	 return Vector3(x / other.x, y / other.y, z / other.z);
 }

 Vector3 me::Vector3::operator/(const float& s)
 {
	 return Vector3(x / s, y / s, z / s);
 }

 void Vector3::operator=(const Vector3 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::operator=(const Vector3 * v)
{
	x = v->x;
	y = v->y;
	z = v->z;
}

bool Vector3::operator==(const Vector3 & v)
{
	return (x == v.x && y == v.y && z == v.z);
}

void Vector3::operator=(const btVector3& v)
{
	x = v.x();
	y = v.y();
	z = v.z();
}

bool Vector3::operator!=(const Vector3& v)
{
	return (x != v.x || y != v.y || z != v.z);
}

Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, float f)
{
	return Vector3(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f));
}

float Vector3::magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalize()
{
	// Calculate the magnitude of the vector
	float m = magnitude();

	// Divide the vector components by the magnitude to normalize the vector
	return Vector3(x / m, y / m, z / m);
}

Vector3 me::Vector3::translate(Vector3 startPoint, Vector3 direction)
{
	Vector3 newStartPoint = startPoint + direction;
	Vector3 newEndPoint = Vector3(x + direction.x, y + direction.y, z + direction.z);
	return Vector3(newEndPoint.x - newStartPoint.x, newEndPoint.y - newStartPoint.y, newEndPoint.z - newStartPoint.z);
}

Vector3 me::Vector3::Rx(float degrees)
{
	float radians = degrees * MY_PI / 180.0;
	float cosAngle = cos(radians);
	float sinAngle = sin(radians);

	float newX = x;
	float newY = y * cosAngle - z * sinAngle;
	float newZ = y * sinAngle + z * cosAngle;

	return Vector3(newX, newY, newZ);
}

Vector3 me::Vector3::Ry(float degrees)
{
	float radians = degrees * MY_PI / 180.0;
	float cosAngle = cos(radians);
	float sinAngle = sin(radians);

	float newX = x * cosAngle + z * sinAngle;
	float newY = y;
	float newZ = -x * sinAngle + z * cosAngle;

	return Vector3(newX, newY, newZ);
}

Vector3 me::Vector3::Rz(float degrees)
{
	float radians = degrees * MY_PI / 180.0;
	float cosAngle = cos(radians);
	float sinAngle = sin(radians);

	float newX = x * cosAngle - y * sinAngle;
	float newY = x * sinAngle + y * cosAngle;
	float newZ = z;

	return Vector3(newX, newY, newZ);
}

float Vector3::dot(const Vector3& v)
{
	return (x * v.x + y * v.y + z * v.z);
}

Vector3 Vector3::cross(const Vector3& v)
{
	return Vector3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

Vector3 Vector3::zero()
{
	return Vector3(0, 0, 0);
}

Vector3 Vector3::up()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::down()
{
	return Vector3(0, -1, 0);
}

Vector3 Vector3::left()
{
	return Vector3 (-1, 0, 0);
}

Vector3 Vector3::right()
{
	return Vector3 (1, 0, 0);
}

Vector3 Vector3::back()
{
	return Vector3 (0, 0, -1);
}

Vector3 Vector3::forward()
{
	return Vector3 (0, 0, 1);
}

float Vector3::distance(const Vector3 & v)
{
	return Vector3 (v.x - x, v.y - y, v.z - z).magnitude();
}

std::ostream& operator<<(std::ostream& os, const Vector3 & v)
{
	os << "Vector3(" << v.x << ',' << v.y << ',' << v.z << ")";
	return os;
}

float Vector3::angle(const Vector3 & v)
{
	return 20.f; //acos((v) / sqrt(magnitude() * v.magnitude())) * 180 / M_PI_CONST;
}

Ogre::Vector3f me::Vector3::v3ToOgreV3() const
{
	return Ogre::Vector3f(x, y, z);
}

btVector3 me::Vector3::v3ToBulletV3() const
{
	return btVector3(btScalar(x), btScalar(y), btScalar(z));
}

FMOD_VECTOR* me::Vector3::v3ToFmodV3() const
{
	FMOD_VECTOR* newVector = new FMOD_VECTOR ();
	newVector->x = x; newVector->y = y; newVector->z = z;
	return newVector;
}

float Vector3::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

std::ostream& me::operator<<(std::ostream& os, const Vector3& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}
