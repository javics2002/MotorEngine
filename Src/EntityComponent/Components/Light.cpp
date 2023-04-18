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
	renderManager().createNewLight(mName, mTransform->getPosition(), mDirection);
}

void Light::update()
{
}
