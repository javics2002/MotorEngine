#include "Transform.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/Scene.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace me;

Component* FactoryTransform::create(Parameters& params)
{
	Transform* transform = new Transform();
	transform->setPosition(Vector3(Value(params, "position_x", 0.0f),
		Value(params, "position_y", 0.0f), Value(params, "position_z", 0.0f)));
	transform->setRotation(Vector3(Value(params, "rotation_x", 0.0f),
		Value(params, "rotation_y", 0.0f), Value(params, "rotation_z", 0.0f)));
	transform->setScale(Vector3(Value(params, "scale_x", 1.0f),
		Value(params, "scale_y", 1.0f), Value(params, "scale_z", 1.0f)));
	std::string transformParent = Value(params, "parentname", std::string());
	transform->setParentName(transformParent);
	return transform;
}

void me::FactoryTransform::destroy(Component* component)
{
	delete component;
}


Transform::Transform()
{
}

Transform::~Transform()
{
	mChildren.clear();
}

void Transform::start()
{
	setParent();
}

void Transform::update(const double& dt)
{
	childTranslation();
}

Vector3 Transform::getPosition()
{
	return mPosition;
}

me::Vector3 me::Transform::getVelocity()
{
	return mVelocity;
}

me::Vector4 me::Transform::getRotation() {
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

void me::Transform::setVelocity(Vector3 newVelocity)
{
	mVelocity = newVelocity;
}

void me::Transform::setRotation(Vector3 newRotation)
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

Vector3 Transform::right()
{
	return up().cross(forward());
}

Vector3 Transform::up()
{
	Vector3 rot = mRotation.toEuler();

	Vector3 upVector;

	Vector3 vector_radians = rot;
	vector_radians.x = rot.x * M_PI / 180.0;
	vector_radians.y = rot.y * M_PI / 180.0;
	vector_radians.z = rot.z * M_PI / 180.0;

	upVector.x = sin(vector_radians.x);
	upVector.y = cos(vector_radians.x) * cos(vector_radians.z);
	upVector.z = cos(vector_radians.x) * sin(vector_radians.z);

	return upVector;
}

Vector3 Transform::forward()
{
	Vector3 rot = mRotation.toEuler();

	Vector3 forwardVector;

	Vector3 vector_radians = rot;
	vector_radians.x = rot.x * M_PI / 180.0;
	vector_radians.y = rot.y * M_PI / 180.0;
	vector_radians.z = rot.z * M_PI / 180.0;

	forwardVector.x = cos(vector_radians.y);
	forwardVector.y = -tan(vector_radians.x);
	forwardVector.z = -sin(vector_radians.y);

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
		if (!getEntity()->getScene()->findEntity(mParentName)) {
			throwMotorEngineError("Transform Error", "Can't find the parent transform Entity");
			sceneManager().quit();

		}
		mParent = getEntity()->getScene()->findEntity(mParentName)->getComponent<Transform>("transform");
		if (!mParent) {
			throwMotorEngineError("Transform Error", "The parent Entity doesn't have the transform component");
			sceneManager().quit();

		}
		mParent->addChild(this);
	}	
}

void Transform::setParentName(std::string name) {
	for (char& c : name)
		c = tolower(c);
	mParentName = name;
}