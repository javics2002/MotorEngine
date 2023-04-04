#include "Vector4.h"
#include "Vector3.h"

#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <OgreColourValue.h>
#include <LinearMath/btQuaternion.h>

using namespace me;

float Vector4::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float a, float b, float c) {

	double cy = cos(c * Ogre::Math::PI / 180.0 / 2.0);
	double sy = sin(c * Ogre::Math::PI / 180.0 / 2.0);
	double cp = cos(b * Ogre::Math::PI / 180.0 / 2.0);
	double sp = sin(b * Ogre::Math::PI / 180.0 / 2.0);
	double cr = cos(a * Ogre::Math::PI / 180.0 / 2.0);
	double sr = sin(a * Ogre::Math::PI / 180.0 / 2.0);

	w = cy * cp * cr + sy * sp * sr;
	x = cy * cp * sr - sy * sp * cr;
	y = sy * cp * sr + cy * sp * cr;
	z = sy * cp * cr - cy * sp * sr;

	convertToZero(w);
	convertToZero(x);
	convertToZero(y);
	convertToZero(z);
}


void Vector4::convertToZero(float &value) {
	if (std::abs(value) < TOLERANCE) {
		value =  0;
	}
}

Vector4::Vector4(const Vector3& v_) {
	
	double cy = cos(v_.z * Ogre::Math::PI / 180.0 / 2.0);
	double sy = sin(v_.z * Ogre::Math::PI / 180.0 / 2.0);
	double cp = cos(v_.y * Ogre::Math::PI / 180.0 / 2.0);
	double sp = sin(v_.y * Ogre::Math::PI / 180.0 / 2.0);
	double cr = cos(v_.x * Ogre::Math::PI / 180.0 / 2.0);
	double sr = sin(v_.x * Ogre::Math::PI / 180.0 / 2.0);

	w = cy * cp * cr + sy * sp * sr;
	x = cy * cp * sr - sy * sp * cr;
	y = sy * cp * sr + cy * sp * cr;
	z = sy * cp * cr - cy * sp * sr;

	convertToZero(w);
	convertToZero(x);
	convertToZero(y);
	convertToZero(z);
	
}

Vector4::Vector4(float a, float b, float c, float d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

Vector4::Vector4(const Vector4 &v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

Vector4 Vector4::lerp(const Vector4& a, const Vector4& b, float f)
{
	return Vector4(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f), lerp(a.w, b.w, f));
}

void Vector4::operator=(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

void Vector4::operator=(const Vector4* v)
{
	x = v->x;
	y = v->y;
	z = v->z;
	w = v->w;
}

Ogre::Quaternion Vector4::v4ToOgreQuaternion() const {
	return Ogre::Quaternion(w, x, y, z);
}

btQuaternion Vector4::getRotationInBullet() const {
	return btQuaternion(x, y, z, w);
}

void Vector4::rotate(float degrees, Vector3 axis) {

	Ogre::Vector3f v = Ogre::Vector3f(x, y, z);
	v.normalise();

	const Ogre::Radian r = Ogre::Radian(degrees * (Ogre::Math::PI / 180.0));

	Ogre::Quaternion quat(r, axis.v3ToOgreV3());

	w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
	x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
	y = w * quat.y - x * quat.z + y * quat.w + z * quat.x;
	z = w * quat.z + x * quat.y - y * quat.x + z * quat.w;

	convertToZero(w);
	convertToZero(x);
	convertToZero(y);
	convertToZero(z);
}

Vector3 Vector4::toEuler() {
	double sinr_cosp = 2.0 * (w * x + y * z);
	double cosr_cosp = 1.0 - 2.0 * (x * x + y * y);
	double roll = std::atan2(sinr_cosp, cosr_cosp);

	double sinp = 2.0 * (w * y - z * x);
	double pitch = 0.0;
	if (std::abs(sinp) >= 1.0) {
		pitch = std::copysign(Ogre::Math::PI / 2.0, sinp);
	}
	else {
		pitch = std::asin(sinp);
	}
	
	double siny_cosp = 2.0 * (w * z + x * y);
	double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
	double yaw = std::atan2(siny_cosp, cosy_cosp);

	Vector3 angles;
	angles.z = roll * 180.0 / Ogre::Math::PI;
	angles.x = pitch * 180.0 / Ogre::Math::PI;
	angles.y = yaw * 180.0 / Ogre::Math::PI;
	return angles;
}

Ogre::ColourValue me::Vector4::v4toOgreColourValue() const
{
	return Ogre::ColourValue(x, y, z, w);
}

