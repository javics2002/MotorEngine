#include "Transform.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"

#include <iostream>

using namespace me;

Transform::Transform()
{
}

Transform::~Transform()
{
#ifdef _DEBUG
	std::cout << " >>> Component ( Transform ) deleted..." << std::endl;
#endif

	mChildren.clear();
}

void Transform::start()
{
	setParent();
	std::cout << "start transform";
}

void Transform::update(const double& dt)
{
	childTranslation();
}

Vector3 Transform::getPosition()
{
	return mPosition;
}

Vector4 Transform::getRotation() {
	return mRotation;
}

Vector3 Transform::getScale()
{
	return mScale;
}

void Transform::setPosition(Vector3 newPosition)
{	
	mTranslatePosition = newPosition - mPosition;
	mPosition = newPosition;
}

void Transform::setRotation(Vector3 newRotation)
{
	mRotation = Vector4(newRotation);
}

void Transform::setRotation(Vector4 newRotation)
{
	mRotation = newRotation;
}

void Transform::setScale(Vector3 newScale)
{
	mScale = newScale;
}

void Transform::translate(Vector3 translation)
{
	mPosition = mPosition + translation;
}

void Transform::rotate(float degrees, Vector3 axis)
{
	mRotation.rotate(degrees, axis);
}

void Transform::scaleF(float scaleF)
{
	mScale *= scaleF;
}

Vector3 Transform::forward()
{
	Vector3 rot = mRotation.toEuler();
	Vector3 v;

	Vector3 forwardVector;

	Vector3 vector_radians = rot;
	vector_radians.x = rot.x * 3.1415926 / 180.0;
	vector_radians.y = rot.y * 3.1415926 / 180.0;
	vector_radians.z = rot.z * 3.1415926 / 180.0;

	forwardVector.x = cos(vector_radians.y);
	forwardVector.y = -tan(vector_radians.x);
	forwardVector.z = -sin(vector_radians.y);

	forwardVector.dot(v.left());

	return forwardVector;
}

int Transform::childCount()
{
	return mChildren.size();
}

void Transform::addChild(Transform* child)
{
	mChildren.push_back(child);
}

void Transform::removeChild(Transform* child)
{
	mChildren.remove(child);
}

Transform* Transform::getChild(int index)
{
	if (index > mChildren.size() || index < 0 || mChildren.empty())
		return nullptr;

	auto it = mChildren.begin();
	for (int i = 0; i < index; i++)
		it++;

	return *it;
}

Transform* Transform::getParent()
{
	return mParent;
}

void Transform::childTranslation()
{
	if (childCount() > 0) {
		for (auto child : mChildren) {
			child->translate(mTranslatePosition);
		}
	}
}

void Transform::setParent()
{
	if (mParentName != "") {
		mParent = getEntity()->getScene()->findEntity(mParentName)->getComponent<Transform>("transform");
		mParent->addChild(this);
	}	
}

void Transform::setParentName(std::string name) {
	for (char& c : name)
		c = tolower(c);
	mParentName = name;
}