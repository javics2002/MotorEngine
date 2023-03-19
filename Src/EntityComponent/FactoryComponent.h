#pragma once

#include <string>
#include <list>

#include "Component.h"

class FactoryComponent
{

protected:

	void parseParams(const std::string& params);

	std::list<std::string> mParams;

public:

	virtual me::Component* create(const std::string& params) = 0;

};

class FactoryAnimator : public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

class FactoryAudioListener : public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

class FactoryAudioSource: public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

class FactoryCamera : public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

class FactoryCollider : public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

class FactoryMeshRenderer : public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

class FactoryParticleSystem : public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

class FactoryRigidBody : public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

class FactoryTransform : public FactoryComponent {

public:

	me::Component* create(const std::string& params);

};

