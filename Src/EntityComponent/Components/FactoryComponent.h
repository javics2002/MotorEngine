#pragma once

#ifndef __ENTITYCOMPONENT_FACTORYCOMPONENT
#define __ENTITYCOMPONENT_FACTORYCOMPONENT

#include "MotorEngine/MotorEngineAPI.h"
#include "EntityComponent/InfoScene.h"

namespace me {
	class Component;

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
		static float value(Parameters& params, const ParameterName& parameter, float defaultValue = 0.0f);
		static int value(Parameters& params, const ParameterName& parameter, int defaultValue = 0);
		static bool value(Parameters& params, const ParameterName& parameter, bool defaultValue);
		static std::string value(Parameters& params, const ParameterName& parameter, std::string defaultValue = "");

	public:
		virtual me::Component* create(Parameters& params) = 0;
	};

	class FactoryAnimator : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};

	class FactoryAudioListener : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};

	class FactoryAudioSource : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};

	class FactoryCamera : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};

	class FactoryCollider : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};

	class FactoryMeshRenderer : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};

	class FactoryParticleSystem : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};

	class FactoryRigidBody : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};

	class FactoryTransform : public FactoryComponent {
	public:
		me::Component* create(Parameters& params);
	};
}
#endif