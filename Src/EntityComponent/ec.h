#pragma once
#ifndef __EC
#define __EC

#include <cassert>
#include <cstddef>
#include <memory>

#include "mpl.h"

namespace me {

	/**
	There must be define a file ./ec_defs.h with the list of the existing components.

	This include is valid from c++17, it won't compile with older versions. 
	If you are using an older version replace the #if #else and #endif.
	*/ 
	#if __has_include("./ec_defs.h") 
	#include "./ec_defs.h" 
	#else 
	#endif 
	 
	/**
	Defines a default component list.
	*/
	#ifndef  _CMPS_LIST_
	class ___DummyComponent____;
	#define _CMPS_LIST_ ___DummyComponent____
	#endif


	namespace ec {

		/**
		Defines the name reference of the class that must use this.
		*/
		class Entity;
		class Component;

		/**
		Creates the list of the declarated components.
		*/
		using ComponentsList = mpl::TypeList<_CMPS_LIST_>;

		/**
		Gets the position in the list of the suggested component.
		*/
		template<typename T>
		constexpr std::size_t cmpIdx = mpl::IndexOf<T, ComponentsList>();

		/**
		Gets the top index of the list of declarated components.
		*/
		constexpr std::size_t maxComponent = ComponentsList::size;

	};

};

#endif