#pragma once
#ifndef __PHYSICS_ENUM
#define __PHYSICS_ENUM

namespace me {
	enum Shapes {
		SHAPES_SPHERE,
		SHAPES_BOX,
		SHAPES_CYLINDER,
		SHAPES_CAPSULE
	};

	enum MovementType {
		MOVEMENT_TYPE_DYNAMIC,
		MOVEMENT_TYPE_STATIC,
		MOVEMENT_TYPE_KINEMATIC
	};
}

#endif