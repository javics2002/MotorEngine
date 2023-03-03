#pragma once

#ifndef __ENTITYCOMPONENT_MESHRENDERER
#define __ENTITYCOMPONENT_MESHRENDERER

#include "Component.h"
#include "Utils/Vector3.h"
#include <list>

namespace me {

	class Transform;

	/*
	*The MeshRenderer class represents a visual object in 3D space and can be attached to entities.
	*/
	class MeshRenderer : public Component
	{
	private:
	protected:
		std::string mName;
		std::string mMeshName;
		Transform* mTransform;
		bool mStaticObject = false;

	public:
		MeshRenderer(std::string name, std::string meshName);
		~MeshRenderer();

		void start() override;
		void update() override;
		void setStatic(bool stat);




		
	};
}
#endif


