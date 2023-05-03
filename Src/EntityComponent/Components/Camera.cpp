#include "Camera.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Entity.h"
#include "Transform.h"

using namespace me;

Camera::Camera()
{

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
	mNearDistance = nearDistance;
}

void Camera::setFarDistance(float farDistance)
{
	mFarDistance = farDistance;
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
	renderManager().setCameraInfo(mName, mTransform->getPosition(), mLookAt);
}

void Camera::init()
{
	renderManager().createCamera(mName, mNearDistance, mFarDistance, mAutoRatio, mZOrder, mBackgroundColour);
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




