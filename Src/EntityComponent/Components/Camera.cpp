#include "Camera.h"
#include "Render/RenderManager.h"
#include <OgreVector3.h>
#include "EntityComponent/Entity.h"
#include "Transform.h"
#include "Utils/Vector3.h"



me::Camera::Camera()
{
}

me::Camera::~Camera()
{
	renderManager().destroyCamera(mName);
}

void me::Camera::start()
{
	mTransform = getEntity()->getComponent<Transform>("transform");
	renderManager().createCamera(mName,mNearDistance,mFarDistance,mAutoRadio,mZOrder);
	renderManager().setCameraInfo(mName, mTransform->getPosition().v3ToOgreV3(), mLookAt.v3ToOgreV3());

}

void me::Camera::update()
{
	if (!mStaticObject)
	{
		renderManager().setCameraInfo(mName, mTransform->getPosition().v3ToOgreV3(), mLookAt.v3ToOgreV3());
	}
}

void me::Camera::setStatic(bool stat)
{
	mStaticObject = stat;
}

void me::Camera::setViewportDimension(float left, float top, float width, float height)
{
	renderManager().setViewportDimension(mName, left, top, width, height);
}




