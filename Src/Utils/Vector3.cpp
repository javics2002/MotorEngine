#include "Vector3.h"
#include "SimpleLerp.h"

#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>
#include <fmod.hpp>

using namespace me;

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

Vector3::Vector3(const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

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

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float f)
{
	return Vector3(SimpleLerp::Lerp(a.x, b.x, f), SimpleLerp::Lerp(a.y, b.y, f), SimpleLerp::Lerp(a.z, b.z, f));
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

float Vector3::dot(const Vector3& v)
{
	return (x * v.x + y * v.y + z * v.z);
}

Vector3 Vector3::cross(const Vector3& v)
{
	return Vector3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}

Vector3 Vector3::Up()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::Down()
{
	return Vector3(0, -1, 0);
}

Vector3 Vector3::Left()
{
	return Vector3 (-1, 0, 0);
}

Vector3 Vector3::Right()
{
	return Vector3 (1, 0, 0);
}

Vector3 Vector3::Back()
{
	return Vector3 (0, 0, -1);
}

Vector3 Vector3::Forward()
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

Ogre::Vector3f me::Vector3::v3ToOgreV3() const
{
	return Ogre::Vector3f(x, y, z);
}

btVector3 me::Vector3::v3ToBulletV3() const
{
	return btVector3(btScalar(x), btScalar(y), btScalar(z));
}

FMOD_VECTOR me::Vector3::v3ToFmodV3() const
{
	FMOD_VECTOR newVector;
	newVector.x = x; newVector.y = y; newVector.z = z;
	return newVector;
}

std::ostream& me::operator<<(std::ostream& os, const Vector3& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}
