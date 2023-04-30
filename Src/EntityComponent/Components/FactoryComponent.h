#pragma once

#ifndef __ENTITYCOMPONENT_FACTORYCOMPONENT
#define __ENTITYCOMPONENT_FACTORYCOMPONENT

#include "MotorEngine/MotorEngineAPI.h"
#include "EntityComponent/InfoScene.h"

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
		virtual Component* create(Parameters& params) = 0;
		virtual void destroy(Component* component) = 0;
	};

	
	//Creates and destroys Animator components
	class FactoryAnimator : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys AudioListener components
	class FactoryAudioListener : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys AudioSource components
	class FactoryAudioSource : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys Camera components
	class FactoryCamera : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys Collider components
	class FactoryCollider : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys MeshRenderer components
	class FactoryMeshRenderer : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys ParticleSystem components
	class FactoryParticleSystem : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys RigidBody components
	class FactoryRigidBody : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys Transform components
	class FactoryTransform : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys UISpriteRenderer components
	class FactoryUISpriteRenderer : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys UIText components
	class FactoryUIText : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys UITransform components
	class FactoryUITransform : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

	//Creates and destroys Light components
	class FactoryLight : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};

}
#endif