#include "Camera.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Transform.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"


using namespace me;


me::Component* me::FactoryCamera::create(Parameters& params)
{
    Camera* camera = new Camera();

    std::string name = Value(params, "name", std::string("Main"));
    camera->setName(name);
    camera->setNearDistance(Value(params, "neardistance", 1.f));
    camera->setFarDistance(Value(params, "fardistance", 1000));
    camera->setAutoRadio(Value(params, "autoratio", false));
    camera->setZOrder(Value(params, "zorder", 0));
    camera->setBackgroundColour(Vector4(Value(params, "backgroundcolor_r", .0f), Value(params, "backgroundcolor_g", .0f),
        Value(params, "backgroundcolor_b", .0f), Value(params, "backgroundcolor_a", 1.0f)));
    camera->setLookAt(Vector3(Value(params, "lookat_x", .0f), Value(params, "lookat_y", .0f), Value(params, "lookat_z", .0f)));

    if (!camera->createCamera()) {
		errorManager().throwMotorEngineError("Camera Factory Error", "A camera with that name already exists.");
        delete camera;
        return nullptr;
    }

    camera->setViewportDimension(Value(params, "viewport_left", 0.0f), Value(params, "viewport_top", 0.0f), 
		Value(params, "viewport_width", 1.0f), Value(params, "viewport_height", 1.0f));
    camera->setViewportOverlayEnabled(Value(params, "overlayenable", true));

    return camera;
}

void me::FactoryCamera::destroy(Component* component)
{
    delete component;
}


Camera::Camera()
{
	mNearDistance = 1;
}

Camera::~Camera()
{
	mTransform = nullptr;
	renderManager().destroyCamera(mName);
}

void Camera::setName(std::string name)
{
	mName = name;
}

std::string Camera::getName() const
{
	return mName;
}

void Camera::setNearDistance(float nearDistance)
{
	if (nearDistance > 0)
		mNearDistance = nearDistance;
	else { // throw exception before ogre
		errorManager().throwMotorEngineError("Camera error", "nearDistance can't be negative or 0, check value: " + std::to_string(nearDistance));
		sceneManager().quit();
		return;
	}
}

void Camera::setFarDistance(float farDistance)
{
	if (farDistance >= 0)
		mFarDistance = farDistance;
	else { // throw exception before ogre
			errorManager().throwMotorEngineError("Camera error", "farDistance can't be negative, check value: " + std::to_string(farDistance));
			sceneManager().quit();
			return;
	}
}

void Camera::setAutoRadio(bool autoRatio)
{
	mAutoRatio = autoRatio;
}

void me::Camera::setZOrder(int zOrder)
{
	mZOrder = zOrder;
}

void me::Camera::setLookAt(Vector3 lookAt)
{
	mLookAt = lookAt;
}

void me::Camera::setBackgroundColour(Vector4 colour)
{
	mBackgroundColour = colour;
}

void Camera::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	if (!mTransform) {
		errorManager().throwMotorEngineError("Camera error", "An entity doesn't have transform component");
		sceneManager().quit();
        return;
	}
	renderManager().setCameraInfo(mName, mTransform->getPosition(), mLookAt);
}

bool Camera::createCamera()
{
	return renderManager().createCamera(mName, mNearDistance, mFarDistance, mAutoRatio, mZOrder, mBackgroundColour);
}

void Camera::update(const double& dt)
{
	if (!mStaticObject)
		renderManager().setCameraInfo(mName, mTransform->getPosition(), mLookAt);
}

void Camera::setStatic(bool stat)
{
	mStaticObject = stat;
}

void Camera::setViewportDimension(float left, float top, float width, float height)
{
	renderManager().setViewportDimension(mName, left, top, width, height);
}

void me::Camera::setViewportOverlayEnabled(bool enabled)
{
	renderManager().setViewportOverlayEnabled(mName,enabled);
}




