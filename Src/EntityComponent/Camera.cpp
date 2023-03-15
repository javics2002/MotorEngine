#include "Camera.h"
#include "Render/OgreManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"



me::Camera::Camera(std::string name, int nearDist, int farDist, bool autoRadio, int zOrder,Vector3 lookAt)
{
	mName = name;
	mNearDistance = nearDist;
	mFarDistance = farDist;
	mAutoRadio = autoRadio;
	mZOrder = zOrder;
	mLookAt = lookAt;

}

me::Camera::~Camera()
{
	om().destroyCamera(mName);
}

void me::Camera::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	om().createCamera(mName,mNearDistance,mFarDistance,mAutoRadio,mZOrder);
	om().setCameraInfo(mName, mTransform->getPosition().v3ToOgreV3(), mLookAt.v3ToOgreV3());

}

void me::Camera::update()
{
	if (!mStaticObject)
	{
		om().setCameraInfo(mName, mTransform->getPosition().v3ToOgreV3(), mLookAt.v3ToOgreV3());
	}
}

void me::Camera::setStatic(bool stat)
{
	mStaticObject = stat;
}

void me::Camera::setViewportDimension(float left, float top, float width, float height)
{
	om().setViewportDimension(mName, left, top, width, height);
}




