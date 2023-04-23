#include "PhysicsManager.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/NarrowPhaseCollision/btPersistentManifold.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/Dynamics/btActionInterface.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/ConstraintSolver/btConstraintSolver.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <LinearMath/btDefaultMotionState.h>

#include "DebugDrawer.h"
#include "EntityComponent/Components/Collider.h"
#include "Render/RenderManager.h"

using namespace me;

PhysicsManager::PhysicsManager()
{
	mDynamicsWorld = nullptr;
	mDispatcher = nullptr;
	mBroadphaseInterface = nullptr;
	mCollisionConfiguration = nullptr;
	mConstraintSolver = nullptr;
	mDebug = nullptr;
}

PhysicsManager::~PhysicsManager()
{
	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	for (int i = mDynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = mDynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		mDynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < mCollisionShapes.size(); j++)
	{
		btCollisionShape* shape = mCollisionShapes[j];
		delete shape;
	}
	mCollisionShapes.clear();

	//delete dynamics world
	delete mDynamicsWorld;

	//delete solver
	delete mConstraintSolver;

	//delete broadphase
	delete mBroadphaseInterface;

	//delete dispatcher
	delete mDispatcher;

	delete mCollisionConfiguration;
}

void PhysicsManager::destroyRigidBody(btRigidBody *rb) {
	if (rb && rb->getMotionState())
		delete rb->getMotionState();

	mDynamicsWorld->removeCollisionObject(rb);

	btCollisionShape* shape = rb->getCollisionShape();
	std::vector<btCollisionShape*>::iterator it = std::find(mCollisionShapes.begin(), mCollisionShapes.end(), shape);
	if (it != mCollisionShapes.end()) {
		delete shape;
		mCollisionShapes.erase(it);
	}
}

/*
Collision Enter Callback, mainfold can get the 
pointers of the rigid bodies that have collided
*/
void callBackEnter(btPersistentManifold* const& manifold) {

	const btCollisionObject* body1 = manifold->getBody0();
	const btCollisionObject* body2 = manifold->getBody1();

	if (body1 && body2) {

		me::Collider* colliderBody1 = static_cast<me::Collider*>(body1->getUserPointer());
		me::Collider* colliderBody2 = static_cast<me::Collider*>(body2->getUserPointer());

		if (colliderBody1 && colliderBody2) {
			colliderBody1->onCollisionEnter(colliderBody2->getEntity());
			colliderBody2->onCollisionEnter(colliderBody1->getEntity());
		}

	}
}

/*
Collision Stay Callback
*/
bool callBackStay(btManifoldPoint& manifold, void* obj1, void* obj2) {

	const btCollisionObject* body1 = static_cast<btCollisionObject*>(obj1);
	const btCollisionObject* body2 = static_cast<btCollisionObject*>(obj2);

	if (body1 && body2) {

		me::Collider* colliderBody1 = static_cast<me::Collider*>(body1->getUserPointer());
		me::Collider* colliderBody2 = static_cast<me::Collider*>(body2->getUserPointer());

		if (colliderBody1 && colliderBody2) {
			colliderBody1->onCollisionStay(colliderBody2->getEntity());
			colliderBody2->onCollisionStay(colliderBody1->getEntity());
		}

	}

	return true;

}

/*
Collision Exit Callback, mainfold can get the
pointers of the rigid bodies that have collided
*/
void callBackExit(btPersistentManifold* const& manifold) {
	const btCollisionObject* body1 = manifold->getBody0();
	const btCollisionObject* body2 = manifold->getBody1();

	if (body1 && body2) {
		Collider* colliderBody1 = static_cast<Collider*>(body1->getUserPointer());
		Collider* colliderBody2 = static_cast<Collider*>(body2->getUserPointer());

		if (colliderBody1 && colliderBody2) {
			colliderBody1->onCollisionExit(colliderBody2->getEntity());
			colliderBody2->onCollisionExit(colliderBody1->getEntity());
		}
	}
}

void PhysicsManager::start()
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mBroadphaseInterface = new btDbvtBroadphase();
	mConstraintSolver = new btSequentialImpulseConstraintSolver;

	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphaseInterface, mConstraintSolver, mCollisionConfiguration);

	gContactStartedCallback = callBackEnter;
	gContactProcessedCallback = callBackStay;
	gContactEndedCallback = callBackExit;

#ifdef _DEBUG
	mDebug = new DebugDrawer();
	mDynamicsWorld->setDebugDrawer(mDebug);
#endif

	mDynamicsWorld->setGravity(btVector3(0, -9.8, 0));

}

void PhysicsManager::addRigidBody(btRigidBody* rigidBody)
{
	mDynamicsWorld->addRigidBody(rigidBody);
}

void PhysicsManager::addVehicle(btActionInterface* vehicle)
{
	mDynamicsWorld->addVehicle(vehicle);
}

btCollisionShape* PhysicsManager::createShape(Shapes shape, const btVector3 &scale, const btVector3 &colliderScale)
{
	
	btCollisionShape* shape_;

	switch (shape)
	{

	case SHAPES_SPHERE:
		shape_ = new btSphereShape(scale.length());
		break;
	case SHAPES_BOX:
		shape_ = new btBoxShape(btVector3(scale.x(), scale.y(), scale.z())*colliderScale);
		break;
	case SHAPES_CYLINDER:
		shape_ = new btCylinderShape(scale*colliderScale);
		break;
	case SHAPES_CAPSULE:
		shape_ = new btCapsuleShape(scale.x()*colliderScale.x(), scale.y()*colliderScale.y());
		break;
	default:
		shape_ = new btSphereShape(scale.length());
		break;
	}

	return shape_;
}

btRigidBody* PhysicsManager::createRigidBody(btTransform* transform, const btVector3 &scale, const btVector3 &colliderScale, 
	Shapes shape, MovementType mvType, bool isTrigger, float friction, float &mass, float restitution)
{

	btCollisionShape* colShape;

	colShape = createShape(shape, scale, colliderScale);
	mCollisionShapes.push_back(colShape);
	
	//Initially the rigidBody  is in repose
	btVector3 reposeInertia(0, 0, 0);

	//Stores the initial position and orientation of the rigid object to update them with each iteration
	btDefaultMotionState* dfMotionState = new btDefaultMotionState(*transform);

	//If the object is dynamic, calculate the localInertia
	if (mvType == MOVEMENT_TYPE_DYNAMIC) {
		colShape->calculateLocalInertia(mass, reposeInertia);
	}

	else if(mvType == MOVEMENT_TYPE_STATIC) mass = 0;

	//Info to create rigidBody
	btRigidBody::btRigidBodyConstructionInfo rbContruction = btRigidBody::btRigidBodyConstructionInfo(mass, dfMotionState, colShape, reposeInertia);

	btRigidBody* rb = new btRigidBody(rbContruction);

	rb->setRestitution(restitution);
	rb->setFriction(friction);
	rb->setCollisionFlags(mvType);

	if (isTrigger) {
		rb->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}

	addRigidBody(rb);

	return rb;

}

void PhysicsManager::update(const double& dt)
{
	mDynamicsWorld->stepSimulation(dt);
}


