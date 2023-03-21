#include "Vector4.h"

#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <LinearMath/btQuaternion.h>

float Vector4::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

Vector4::Vector4()
{
	x = 1;
	y = 1;
	z = 1;
	w = 1;
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

Ogre::Quaternion Vector4::v4ToQuaternion() {

	Ogre::Vector3f xAxis(x,y,z);
	Ogre::Vector3f yAxis(w, z, -y);
	Ogre::Vector3f zAxis = xAxis.crossProduct(yAxis);

	Ogre::Quaternion quat;
	quat.FromAxes(xAxis, yAxis, zAxis);

	return quat;
}

btQuaternion Vector4::getRotationInBullet() {
	return btQuaternion(x, y, z, w);
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

