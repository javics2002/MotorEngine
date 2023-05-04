#include "Light.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "Transform.h"

using namespace me;

Light::Light()
{
}

Light::~Light()
{
	renderManager().destroyLight(mName);
}

void Light::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	renderManager().createNewLight(mName, mTransform->getPosition(), mDirection, mColor);

	if (mSetAmbient)
		renderManager().setAmbientLight(mAmbientColor);
}

void Light::setName(std::string name)
{
	mName = name;
}

void Light::setLightType(LightType type)
{
	mType = type;
}

void Light::setDirection(Vector3 direction)
{
	mDirection = direction;
}

void me::Light::setColor(Vector3 color)
{
	mColor = color;
}

void me::Light::setAmbientColor(Vector3 color)
{
	mSetAmbient = true;
	mAmbientColor = color;
}
