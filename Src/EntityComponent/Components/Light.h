#pragma once
#ifndef __ENTITYCOMPONENT_LIGHT
#define __ENTITYCOMPONENT_LIGHT

#include "Component.h"
#include "Utils/Vector3.h"

namespace me {
	class Transform;

	enum LightType { LIGHTTYPE_DIRECTIONAL, LIGHTTYPE_POINT, LIGHTTYPE_SPOT };

	/**
	A light source that lits objects in the scene.
	It can be a directional, point or spotlight
	*/
	class __MOTORENGINE_API Light : public Component
	{
		LightType mType;
		Vector3 mDirection;
		Transform* mTransform;

	public:
		Light();
		~Light();

		void start() override;
		void update() override;

		inline void setLightType(LightType type) {
			mType = type;
		}

		inline void setDirection(Vector3 direction) {
			mDirection = direction;
		}
	};
}
#endif