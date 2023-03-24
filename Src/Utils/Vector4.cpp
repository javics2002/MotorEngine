#include "Vector4.h"
#include "Vector3.h"

#include <OgreQuaternion.h>
#include <OgreVector3.h>
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

	Ogre::Vector3f* v = new Ogre::Vector3f(a, b, c);
	v->normalise();

	Ogre::Quaternion quat(v);

	x = quat.x;
	y = quat.y;
	z = quat.z;
	w = quat.w;

	delete v;
}

Vector4::Vector4(const Vector3& v_) {
	
	Ogre::Vector3f *v = new Ogre::Vector3f(v_.x, v_.y, v_.z);
	v->normalise();

	Ogre::Quaternion quat(v);
	
	x = quat.x;
	y = quat.y;
	z = quat.z;
	w = quat.w;

	delete v;
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

Ogre::Quaternion Vector4::v4ToOgreQuaternion() {
	return Ogre::Quaternion(x, y, z, w);
}

btQuaternion Vector4::getRotationInBullet() {
	return btQuaternion(x, y, z);
}

void Vector4::rotate(float degrees, Vector3 axis) {

	Ogre::Vector3f v = Ogre::Vector3f(x, y, z);
	v.normalise();

	const Ogre::Radian r = Ogre::Radian(degrees);

	Ogre::Quaternion quat(r, axis.v3ToOgreV3());

	x += quat.x;
	y += quat.y;
	z += quat.z;
	w += quat.w;
}

