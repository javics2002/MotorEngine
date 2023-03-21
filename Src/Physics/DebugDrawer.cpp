#include "DebugDrawer.h"

#include "Utils/Vector3.h"

#include "Render/RenderManager.h"

//bool me::DebugDrawer::frameStarted(const Ogre::FrameEvent& evt)
//{
//	const size_t now = Ogre::Root::getSingleton().getTimer()->getMilliseconds();
//	std::vector<ContactPoint>* newCP = mContactPoints_ == &mContactPoints1_
//		? &mContactPoints2_
//		: &mContactPoints1_;
//	//for (auto i = mContactPoints_->begin(); i < mContactPoints_->end(); ++i) {
//	//	ContactPoint& cp = *i;
//	//	mLines->position(cp.from);
//	//	mLines_->colour(cp.color);
//	//	mLines_->position(cp.to);
//	//	if (now <= cp.dieTime)
//	//		newCP->push_back(cp);
//	//}
//	mContactPoints_->clear();
//	mContactPoints_ = newCP;
//
//	//mLines_->end();
//	mTriangles->end();
//
//	return true;
//}
//
//bool me::DebugDrawer::frameEnded(const Ogre::FrameEvent& evt)
//{
//	//mLines_->beginUpdate(0);
//	mTriangles->beginUpdate(0);
//	return true;
//}

me::DebugDrawer::DebugDrawer() {
	
	mTriangles = new Ogre::ManualObject("triangle");
	mTriangles->setDynamic(true);

	renderManager().getRootSceneNode()->createChildSceneNode()->attachObject(mTriangles);
	
	std::string materialName = "Material/amarillo";
	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(materialName);
	mat->setReceiveShadows(false);

	Vector3 v;
	Ogre::Vector3f ogreV = v.zero().v3ToOgreV3();

	mTriangles->begin(mat, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	mTriangles->position(ogreV);
	mTriangles->colour(Ogre::ColourValue::Blue);
	mTriangles->position(ogreV);
	mTriangles->colour(Ogre::ColourValue::Blue);
	mTriangles->position(ogreV);
	mTriangles->colour(Ogre::ColourValue::Blue);

	mDebugDrawModes = DBG_DrawWireframe;

}

me::DebugDrawer::~DebugDrawer() {

}



void me::DebugDrawer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar alpha)
{

	Ogre::ColourValue c(color.getX(), color.getY(), color.getZ());
	c.saturate();

	Vector3 v0_, v1_, v2_;
	/*v0_ = v0;
	v1_ = v1;
	v2_ = v2;*/

	mTriangles->position(v0_.v3ToOgreV3());
	mTriangles->colour(c);
	mTriangles->position(v1_.v3ToOgreV3());
	mTriangles->colour(c);
	mTriangles->position(v2_.v3ToOgreV3());
	mTriangles->colour(c);

}

void me::DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
}

void me::DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
}

void me::DebugDrawer::reportErrorWarning(const char* warningString)
{
}

void me::DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
}

void me::DebugDrawer::setDebugMode(int debugMode)
{
}

int me::DebugDrawer::getDebugMode() const 
{
	return mDebugDrawModes;
}
