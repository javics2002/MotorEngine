#pragma once
#ifndef __ENTITYCOMPONENT_LIGHT
#define __ENTITYCOMPONENT_LIGHT

#include "Component.h"
#include "Utils/Vector3.h"
#include <string>

namespace me {
	class Transform;

	enum LightType { LIGHTTYPE_DIRECTIONAL, LIGHTTYPE_POINT, LIGHTTYPE_SPOT };

	/**
	A light source that lits objects in the scene.
	It can be a directional, point or spotlight.
	You can also set the scene ambient light through 
	this component
	*/
	class __MOTORENGINE_API Light : public Component
	{
		std::string mName;
		LightType mType;
		Vector3 mDirection;
		Transform* mTransform;
		Vector3 mColor;

		bool mSetAmbient = false;
		Vector3 mAmbientColor;

	public:
		Light();
		~Light();

		void start() override;

		inline void setName(std::string name) {
			mName = name;
		}

		inline void setLightType(LightType type) {
			mType = type;
		}

		inline void setDirection(Vector3 direction) {
			mDirection = direction;
		}

		inline void setColor(Vector3 color) {
			mColor = color;
		}

		inline void setAmbientColor(Vector3 color) {
			mSetAmbient = true;
			mAmbientColor = color;
		}
	};
}
#endif