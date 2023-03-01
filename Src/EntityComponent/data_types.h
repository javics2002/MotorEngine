/**
This file contains de definitions of the differents types of data
that could be use by the MessagesCenter.
*/

#pragma once

#ifndef __EC_DATA_TYPES
#define __EC_DATA_TYPES

#include <cstdint>


namespace me {

	class Entity;

	/**
	Defines 32 bits float type.
	*/
	typedef float float32_t;
	static_assert(sizeof(float32_t) == sizeof(std::int32_t), "Tamaño de float32_t no es 32 bits");

	/**
	Defines collision data type.
	*/
	struct Collision {
		Entity* origin;
		Entity* affected;
	};

	/**
	Defines position data type.
	*/
	struct State {
		float32_t posX;
		float32_t posY;
		float32_t velX;
		float32_t velY;
	};

	/**
	Defines score data type.
	*/
	struct Score {
		uint8_t value;
	};

	/**
	Defines human communication data type.
	*/
	struct Chat {
		char message[256];
	};

};

#endif