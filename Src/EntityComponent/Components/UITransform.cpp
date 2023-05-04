#include "UITransform.h"

using namespace me;

UITransform::UITransform()
{
}

UITransform::~UITransform()
{
	mChildren.clear();
}

Vector2 UITransform::getPosition()
{
	return mPosition;
}

float UITransform::getRotation() {
	return mRotation;
}

Vector2 UITransform::getScale()
{
	return mScale;
}

void UITransform::setPosition(Vector2 newPosition)
{
	mPosition = newPosition;
}

void UITransform::setRotation(float newRotation)
{
	mRotation = newRotation;
}

void UITransform::setScale(Vector2 newScale)
{
	mScale = newScale;
}

void UITransform::translate(Vector2 translation)
{
	mPosition.x += translation.x;
	mPosition.y += translation.y;
}

void UITransform::rotate(float degrees)
{
	mRotation += degrees;
}

void UITransform::scaleF(float scaleF)
{
	mScale.x *= scaleF;
	mScale.y *= scaleF;
}

int UITransform::childCount()
{
	return mChildren.size();
}

void UITransform::addChild(UITransform* child)
{
	mChildren.push_back(child);
}

void UITransform::removeChild(UITransform* child)
{
	mChildren.remove(child);
}

UITransform* UITransform::getChild(int index)
{
	if (index > mChildren.size() || index < 0 || mChildren.empty())
		return nullptr;

	auto it = mChildren.begin();
	for (int i = 0; i < index; i++)
		it++;

	return *it;
}

UITransform* UITransform::getParent()
{
	return mParent;
}
