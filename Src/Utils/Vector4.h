#pragma once

#ifndef __UTILS_VECTOR4
#define __UTILS_VECTOR4

#include "MotorEngine/MotorEngineAPI.h"

namespace Ogre {
	template<int dism, typename T>
	class Vector;
	typedef Vector< 3, float > 	Vector3f;

	class Quaternion;
}

class btQuaternion;

namespace me {

	class Vector3;

	class __MOTORENGINE_API Vector4
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
		float lerp(float a, float b, float f);


	public:

		float x, y, z, w;


		Vector4();

		Vector4(float a, float b, float c);

		Vector4(const Vector3& v_);

		Vector4(float a, float b, float c, float d);

		Vector4(const Vector4& v);

		/**
		*  Returns the linear interpolation between "a" and "b" by a factor of "f"
		*
		*  @param a The starting vector to interpolate from
		*  @param b The ending vector to interpolate to
		*  @param f The interpolation factor, a value between 0 and 1
		*/
		Vector4 lerp(const Vector4& a, const Vector4& b, float f);

		void operator=(const Vector4& v);
		void operator=(const Vector4* v);

		/**
		Return the conversion Vector3 - Ogre::Quaternion
		*/
		Ogre::Quaternion v4ToOgreQuaternion();

		/**
		Returns the current Rotation in btQuaternion
		*/
		btQuaternion getRotationInBullet();

		/*
		Do the rotation in specify axis
		*/
		void rotate(float degrees, Vector3 axis);
	};
}

#endif
