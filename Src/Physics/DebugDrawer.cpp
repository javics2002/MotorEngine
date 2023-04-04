#include "DebugDrawer.h"

#include "Utils/Vector3.h"

#include "Render/RenderManager.h"

me::DebugDrawer::DebugDrawer() {
	mDebugDrawModes = DBG_DrawWireframe;
}

me::DebugDrawer::~DebugDrawer() {
}

void me::DebugDrawer::clear()
{
	for (int i = 0; i < lines.size(); i++) {
		lines[i]->clear();
		delete lines[i];
	}

	lines.clear();

	renderManager().getSceneManager()->destroyAllManualObjects();
}

void me::DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	line = renderManager().getSceneManager()->createManualObject();
	line->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
	line->position(from.x(), from.y(), from.z());
	line->position(to.x(), to.y(), to.z());
	line->colour(Ogre::ColourValue(color.x(), color.y(), color.z()));
	line->end();
	renderManager().getRootSceneNode()->createChildSceneNode()->attachObject(line);
	lines.push_back(line);
}

void me::DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance,
	int lifeTime, const btVector3& color){}

void me::DebugDrawer::reportErrorWarning(const char* warningString){}

void me::DebugDrawer::draw3dText(const btVector3& location, const char* textString) {}

void me::DebugDrawer::setDebugMode(int debugMode){}

int me::DebugDrawer::getDebugMode() const 
{
	return mDebugDrawModes;
}
