/**
This file contains several definitions related to entities and components.
The type list of components, a variable to access the index of a suggested type component 
and a constant the defines the total number of components types.
*/

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
	#if __has_include("ec_defs.h") 
	#include "ec_defs.h" 
	#else 
	#endif 
	 
	/**
	Defines a default component list consisting of a single dummy component.
	*/
	#ifndef  _CMPS_LIST_
	class ___DummyComponent____;
	#define _CMPS_LIST_ ___DummyComponent____
	#endif


	/**
	Defines the name reference of the class that must use this.
	*/
	class Entity;
	class Component;

	/**
	Creates the list of the declarated components.
	*/
	using ComponentsList = TypeList<_CMPS_LIST_>;

	/**
	The cmpIdx template variable is used to get the index 
	of a component type in the ComponentsList.
	*/
	/*template<typename T>
	constexpr std::size_t cmpIdx = IndexOf<T, ComponentsList>();*/

	/**
	The maxComponent constant is defined as the size of the ComponentsList,
	representing the total number of component types defined.
	*/
	constexpr std::size_t maxComponent = ComponentsList::size;

};

#endif