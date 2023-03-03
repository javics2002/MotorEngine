#include "Transform.h"
#include <iostream>

me::Transform::Transform()
{
	// Initialize position, rotation and scale vectors
	mPosition = new Vector3<float>(0.0, 0.0, 0.0);
	mRotation = Ogre::Quaternion::IDENTITY;
	mScale = new Vector3<float>(1.0, 1.0, 1.0);

	// Set parent to null
	mParent = nullptr;

#ifdef _DEBUG
	std::cout << " > Component ( Transform ) created." << std::endl;
#endif
}

me::Transform::~Transform()
{
#ifdef _DEBUG
	std::cout << " >>> Component ( Transform ) deleted..." << std::endl;
#endif
}

void me::Transform::update()
{

}

me::Vector3<float> me::Transform::getPosition()
{
	return mPosition;
}

Ogre::Quaternion me::Transform::getRotation()
{
	return mRotation;
}

btQuaternion me::Transform::getRotationInBullet()
{
	return btQuaternion(mRotation.x, mRotation.y, mRotation.z, mRotation.w);
}

me::Vector3<float> me::Transform::getScale()
{
	return mScale;
}

void me::Transform::setPosition(Vector3<float> newPosition)
{
	mPosition = newPosition;
}

void me::Transform::setRotation(Ogre::Quaternion newRotation)
{
	mRotation = newRotation;
}

void me::Transform::setScale(Vector3<float> newScale)
{
	mScale = newScale;
}

void me::Transform::translate(Vector3<float> translation)
{
	mPosition += translation;
}

void me::Transform::rotate(Vector3<float> rotation)
{
	// To be implemented
}

void me::Transform::scaleF(float scaleF)
{
	mScale *= scaleF;
}

int me::Transform::childCount()
{
	return mChildren.size();
}

void me::Transform::addChild(Transform* child)
{
	mChildren.push_back(child);
}

void me::Transform::removeChild(Transform* child)
{
	mChildren.remove(child);
}

me::Transform* me::Transform::getChild(int index)
{
	if (index > mChildren.size() || index < 0 || mChildren.empty())
		return nullptr;

	auto it = mChildren.begin();
	for (int i = 0; i < index; i++)
		it++;

	return *it;
}

me::Transform* me::Transform::getParent()
{
	return mParent;
}
