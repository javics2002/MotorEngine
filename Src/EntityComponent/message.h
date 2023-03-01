/**
This file contains de definitions of the differents types of data
that could be use by the MessagesCenter.
*/

#pragma once

#ifndef __EC_MESSAGE
#define __EC_MESSAGE

#include <cstdint>


namespace me {

	class Entity;

	/**
	Defines 32 bits float type.
	*/
	typedef float float32_t;
	static_assert(sizeof(float32_t) == sizeof(std::int32_t), "Tamaño de float32_t no es 32 bits");
	
	/**
	Defines the differents types of messages.
	*/
	enum class MessageType {
		COLLISION,
		DAMAGE,
		MOVE,
		// ...
		_PAUSE_START_,
		_PAUSE_OVER_,
		_ROUND_START_,
		_ROUND_OVER_,
		_GAME_START_,
		_GAME_OVER_
	};

	/**
	Defines human communication data type.
	*/
	struct ChatMessage {
		char message[256];
	};

	/**
	Defines collision data type.
	*/
	struct CollisionMessage {
		Entity* entity1;
		Entity* entity2;
	};

	/**
	Defines damage data type.
	*/
	struct DamageMessage {
		Entity* target;
		float damage;
	};

	/**
	Defines move data type.
	*/
	struct MoveMessage {
		Entity* entity;
		float x, y, z;
	};

	/**
	Defines the main message struct, using union inheritance.
	This defines the possible content of the message.

	Fact: 'union' data share the same portion of memory,
	that means that only one of those fields can be use at the same time.
	*/
	struct Message {
		MessageType type;
		union {
			CollisionMessage collision;
			DamageMessage damage;
			MoveMessage move;
			// ...
		};
	};

};

#endif