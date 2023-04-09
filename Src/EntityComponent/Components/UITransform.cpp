#include "UITransform.h"
#include <iostream>

me::UITransform::UITransform()
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

me::UITransform::~UITransform()
{
	//DELETES
#ifdef _DEBUG
	std::cout << " >>> Component ( UITransform ) deleted..." << std::endl;
#endif


	mChildren.clear();
}

void me::UITransform::start()
{

}

void me::UITransform::update()
{

}

void me::UITransform::lateUpdate()
{
}

Vector2 me::UITransform::getPosition()
{
	return mPosition;
}

float me::UITransform::getRotation() {
	return mRotation;
}

Vector2 me::UITransform::getScale()
{
	return mScale;
}

void me::UITransform::setPosition(Vector2 newPosition)
{
	mPosition = newPosition;
}

void me::UITransform::setRotation(float newRotation)
{
	mRotation = newRotation;
}

void me::UITransform::setScale(Vector2 newScale)
{
	mScale = newScale;
}

void me::UITransform::translate(Vector2 translation)
{
	mPosition.x += translation.x;
	mPosition.y += translation.y;
}

void me::UITransform::rotate(float degrees)
{
	mRotation += degrees;
}

void me::UITransform::scaleF(float scaleF)
{
	mScale.x *= scaleF;
	mScale.y *= scaleF;
}

int me::UITransform::childCount()
{
	return mChildren.size();
}

void me::UITransform::addChild(UITransform* child)
{
	mChildren.push_back(child);
}

void me::UITransform::removeChild(UITransform* child)
{
	mChildren.remove(child);
}

me::UITransform* me::UITransform::getChild(int index)
{
	if (index > mChildren.size() || index < 0 || mChildren.empty())
		return nullptr;

	auto it = mChildren.begin();
	for (int i = 0; i < index; i++)
		it++;

	return *it;
}

me::UITransform* me::UITransform::getParent()
{
	return mParent;
}
