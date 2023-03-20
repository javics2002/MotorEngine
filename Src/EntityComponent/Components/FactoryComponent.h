#pragma once

#include <string>
#include <list>
#include <unordered_map>


namespace me {
	class Component;

	class FactoryComponent
	{
	protected:
		typedef std::unordered_map<std::string, std::string>& Parameters;

		/*
		Checks if a parameter is especified in the Parameters map and returns its value if its found.
		Otherwise sets it to defaultValue.
		@params parameter String representing the name of the parameter.
		@params defaultValue Value returned in case parameter is not specified.
		@returns The value of the parameter.
		*/
		static float value(Parameters params, std::string parameter, float defaultValue = 0.0f);
		static int value(Parameters params, std::string parameter, int defaultValue = 0);
		static bool value(Parameters params, std::string parameter, bool defaultValue);
		static std::string value(Parameters params, std::string parameter, std::string defaultValue = "");

	public:

		virtual me::Component* create(Parameters params) = 0;

	};

	class FactoryAnimator : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};

	class FactoryAudioListener : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};

	class FactoryAudioSource : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};

	class FactoryCamera : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};

	class FactoryCollider : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};

	class FactoryMeshRenderer : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};

	class FactoryParticleSystem : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};

	class FactoryRigidBody : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};

	class FactoryTransform : public FactoryComponent {

	public:

		me::Component* create(Parameters params);

	};
}