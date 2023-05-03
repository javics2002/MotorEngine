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
		
		
		/**
		 * Set the name of the light.
		 * @param name A string identifier for the light.
		 */
		void setName(std::string name);
		/**
		 * Set the type of the light
		 * @param type The type of the light (directional, point, or spotlight).
		 */
		void setLightType(LightType type);
		/**
		 * Set the direction of the light (if applicable).
		 * @param direction The direction of the light.
		 */
		void setDirection(Vector3 direction);
		/**
		 * Set the color of the light.
		 * @param color The color of the light.
		 */
		void setColor(Vector3 color);
		/**
		 * Set the ambient color of the scene.
		 * @param color The ambient color of the scene.
		 */
		void setAmbientColor(Vector3 color);
	};
}
#endif