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
		virtual Component* create(Parameters& params) = 0;
		virtual void destroy(Component* component) = 0;
	};

	class FactoryAnimator : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	class FactoryAudioListener : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	class FactoryAudioSource : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	class FactoryCamera : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	class FactoryCollider : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	class FactoryMeshRenderer : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	class FactoryParticleSystem : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	class FactoryRigidBody : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	class FactoryTransform : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};
}
#endif