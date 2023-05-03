#pragma once

#ifndef __UTILS_VECTOR4
#define __UTILS_VECTOR4

#include "MotorEngine/MotorEngineAPI.h"

namespace Ogre {
	template<int dism, typename T>
	class Vector;
	typedef Vector< 3, float > 	Vector3f;

	class Quaternion;
	class ColourValue;
}

class btQuaternion;

namespace me {

	class Vector3;

	class __MOTORENGINE_API Vector4
	{

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

		/**
		*  Sets the left vector's values to equal the right one's.
		*  @param v Other vector.
		*/
		void operator=(const Vector4& v);

		/**
		*  Sets the left vector's values to equal the right one's.
		*  @param v Other vector.
		*/
		void operator=(const Vector4* v);

		/**
		@return Conversion Vector3 - Ogre::Quaternion
		*/
		Ogre::Quaternion v4ToOgreQuaternion() const;

		/**
		@return Current Rotation in btQuaternion
		*/
		btQuaternion getRotationInBullet() const;

		/*
		Rotate on a given axis.
		@param degrees Rotation in degrees.
		@param axis Axis to rotate on. Simple values like (0, 1, 0) are recommended.
		*/
		void rotate(float degrees, Vector3 axis);

		/*
		* Transform quaternion rotation to Euler angles in degrees 
		*/
		Vector3 toEuler();

		/**
		Transform vector4 representing colour in RGBA 
		*/
		Ogre::ColourValue v4toOgreColourValue() const;
	};
}

#endif
