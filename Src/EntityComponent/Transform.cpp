#include "Transform.h"


/**
*  Construct a new Transform object with default position (0, 0, 0),
*  rotation (0, 0, 0) and scale (1, 1, 1).
*/
me::Transform::Transform()
{
	// Initialize position, rotation and scale vectors
	mPosition = new Vector3<float>(0.0, 0.0, 0.0);
	mRotation = new Vector3<float>(0.0, 0.0, 0.0);
	mScale = new Vector3<float>(1.0, 1.0, 1.0);

	// Set parent to null
	mParent = nullptr;
}

/**
*  Destroy the Transform object and its components.
*/
me::Transform::~Transform()
{
}


void me::Transform::update()
{

}


/**
*  Get the position vector of the Transform object.
*  @return A Vector3 object representing the position.
*/
Vector3<float> me::Transform::getPosition()
{
	return mPosition;
}

/**
*  Get the rotation vector of the Transform object.
*  @return A Vector3 object representing the rotation.
*/
Vector3<float> me::Transform::getRotation()
{
	return mRotation;
}


/**
*  Get the scale vector of the Transform object.
*  @return A Vector3 object representing the scale.
*/
Vector3<float> me::Transform::getScale()
{
	return mScale;
}


/**
*  Set the position vector of the Transform object.
*  @param newPosition A Vector3 object representing the new position.
*/
void me::Transform::setPosition(Vector3<float> newPosition)
{
	mPosition = newPosition;
}


/**
*  Set the rotation vector of the Transform object.
*  @param newRotation A Vector3 object representing the new rotation.
*/
void me::Transform::setRotation(Vector3<float> newRotation)
{
	mRotation = newRotation;
}


/**
*  Set the scale vector of the Transform object.
*  @param newScale A Vector3 object representing the new scale.
*/
void me::Transform::setScale(Vector3<float> newScale)
{
	mScale = newScale;
}


/**
*  Translate the Transform object by a given vector.
*  @param translation A Vector3 object representing the translation.
*/
void me::Transform::translate(Vector3<float> translation)
{
	mPosition += translation;
}


/**
*  Rotate the Transform object by a given vector.
*  @param rotation A Vector3 object representing the rotation.
*/
void me::Transform::rotate(Vector3<float> rotation)
{
	// To be implemented
}


/**
*  Scale the Transform object by a given factor.
*  @param scaleF A float representing the scale factor.
*/
void me::Transform::scaleF(float scaleF)
{
	mScale *= scaleF;
}


/**
*  Get the number of child Transform objects.
*/
int me::Transform::childCount()
{
	return mChildren.size();
}


/**
*  Add a child Transform object to the Transform object.
*  @param child A pointer to the child Transform object.
*/
void me::Transform::addChild(Transform* child)
{
	mChildren.push_back(child);
}


/**
*  Remove a child Transform object from the Transform object.
*  @param child A pointer to the child Transform object.
*/
void me::Transform::removeChild(Transform* child)
{
	mChildren.remove(child);
}


/**
 * Returns the child transform at the specified index. 
 * Returns nullptr if the index is out of range or if there are no children.
 * @param index The index of the child transform to retrieve.
 */
me::Transform* me::Transform::getChild(int index)
{
	if (index > mChildren.size() || index < 0 || mChildren.empty())
		return nullptr;

	auto it = mChildren.begin();
	for (int i = 0; i < index; i++)
		it++;

	return *it;
}


/**
 * Returns the parent transform of this transform.
 * @return A pointer to the parent transform of this transform.
 */
me::Transform* me::Transform::getParent()
{
	return mParent;
}
