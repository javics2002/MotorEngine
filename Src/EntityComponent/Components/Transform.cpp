#include "Transform.h"

#include <iostream>

me::Transform::Transform()
{
	/*
	// Initialize position, rotation, size and scale vectors
	mPosition = Vector3(0.0, 0.0, 0.0);
	mRotation = Vector4(0.0, 0.0, 0.0);
	mScale = Vector3(1.0, 1.0, 1.0);

	// Set parent to null
	mParent = nullptr;

#ifdef _DEBUG
	std::cout << " > Component ( Transform ) created." << std::endl;
#endif*/
}

me::Transform::~Transform()
{
	//DELETES
#ifdef _DEBUG
	std::cout << " >>> Component ( Transform ) deleted..." << std::endl;
#endif
}

void me::Transform::start()
{

}

void me::Transform::update()
{

}

void me::Transform::lateUpdate()
{
}

me::Vector3 me::Transform::getPosition()
{
	return mPosition;
}

me::Vector4 me::Transform::getRotation() {
	return mRotation;
}

me::Vector3 me::Transform::getScale()
{
	return mScale;
}

void me::Transform::setPosition(Vector3 newPosition)
{
	mPosition = newPosition;
}

void me::Transform::setRotation(Vector3 newRotation)
{
	mRotation = Vector4(newRotation);
}

void me::Transform::setRotation(Vector4 newRotation)
{
	mRotation = newRotation;
}

void me::Transform::setScale(Vector3 newScale)
{
	mScale = newScale;
}

void me::Transform::translate(Vector3 translation)
{
	mPosition += translation;
}

void me::Transform::rotate(float degrees, Vector3 axis)
{
	mRotation.rotate(degrees, axis);
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
