#pragma once

#ifndef __ENTITYCOMPONENT_MESHRENDERER
#define __ENTITYCOMPONENT_MESHRENDERER

#include "Component.h"
#include <Vector3.h>
#include <list>

namespace me {

	/*
	*The Transform class represents a position, rotation, and scale in 3D space and can be attached to entities.
	*/
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		void update() override;


	private:

		
	};
}
#endif


