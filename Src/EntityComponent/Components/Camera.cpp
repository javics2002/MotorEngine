#include "Camera.h"
#include "Render/RenderManager.h"
#include <OgreVector3.h>
#include "EntityComponent/Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"

using namespace me;

Camera::Camera()
{
}

Camera::~Camera()
{
	renderManager().destroyCamera(mName);
}

void Camera::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	renderManager().createCamera(mName, mNearDistance, mFarDistance, mAutoRatio, mZOrder, mBackgroundColour);
	renderManager().setCameraInfo(mName, mTransform->getPosition(), mLookAt);
}

void Camera::update()
{
	if (!mStaticObject)
	{
		//renderManager().setCameraInfo(mName, mTransform->getPosition(), mLookAt);
	}
}

void Camera::setStatic(bool stat)
{
	mStaticObject = stat;
}

void Camera::setViewportDimension(float left, float top, float width, float height)
{
	renderManager().setViewportDimension(mName, left, top, width, height);
}




