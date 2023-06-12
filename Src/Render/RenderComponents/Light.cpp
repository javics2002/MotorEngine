#include "Light.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Transform.h"

using namespace me;

Component* me::FactoryLight::create(Parameters& params)
{
    Light* light = new Light();

    light->setName(Value(params, "name", std::string("Light")));
    light->setDirection(Vector3(Value(params, "direction_x", 0.0f),
        Value(params, "direction_y", -1.0f), Value(params, "direction_z", 0.0f)));
    light->setLightType((LightType)Value(params, "type", 0));
    light->setColor(Vector3(Value(params, "color_r", 1.0f),
        Value(params, "color_g", 1.0f), Value(params, "color_b", 1.0f)));

    if (params.count("ambientcolor_r"))
        light->setAmbientColor(Vector3(Value(params, "ambientcolor_r", 1.0f),
            Value(params, "ambientcolor_g", 1.0f), Value(params, "ambientcolor_b", 1.0f)));

    return light;
}

void me::FactoryLight::destroy(Component* component)
{
    delete component;
}

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
