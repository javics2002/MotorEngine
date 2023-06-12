#pragma once

#ifndef __ENTITYCOMPONENT_FACTORYCOMPONENT
#define __ENTITYCOMPONENT_FACTORYCOMPONENT

#include "MotorEngine/MotorEngineAPI.h"
#include "MotorEngine/InfoScene.h"

namespace me {
	class Component;

	/**
	A FactoryComponent is responsible of creating and destroying a specific type 
	of component.
	*/
	class __MOTORENGINE_API FactoryComponent
	{
	protected:
		/*
		Checks if a parameter is especified in the Parameters map and returns its value if its found.
		Otherwise sets it to defaultValue.
		@params parameter String representing the name of the parameter.
		@params defaultValue Value returned in case parameter is not specified.
		@returns The value of the parameter.
		*/
		static float Value(Parameters& params, const ParameterName& parameter, float defaultValue = 0.0f);
		static int Value(Parameters& params, const ParameterName& parameter, int defaultValue = 0);
		static bool Value(Parameters& params, const ParameterName& parameter, bool defaultValue);
		static std::string Value(Parameters& params, const ParameterName& parameter, std::string defaultValue = "");

	public:
		/**
		Creates a component using the parameters specified in params.
		If a parameter is not included in params it will have its default value.
		@params Parameters to configure the components in pairs of 
			<std::string parameterName, std::string parameterValue>
		@returns Pointer to the component created or nullptr in case component could not be created
		*/
		virtual Component* create(Parameters& params) = 0;

		/**
		Calls the destructor of the component.
		*/
		virtual void destroy(Component* component) = 0;
	};

}
#endif