#pragma once
#ifndef __DEBUG_DRAWER
#define __DEBUG_DRAWER

#include "MotorEngine/MotorEngineAPI.h"
#include <LinearMath/btIDebugDraw.h>

#include <Ogre.h>

namespace me {
    /**
    DebugDrawer ...
    */
	class __MOTORENGINE_API DebugDrawer : public btIDebugDraw // public Ogre::FrameListener
	{

        Ogre::ManualObject* line;
        std::vector<Ogre::ManualObject*> lines;
		DebugDrawModes mDebugDrawModes;

	public:
		DebugDrawer();
		~DebugDrawer();

        void clear();

        void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
        void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,
            btScalar distance, int lifeTime, const btVector3& color) override;
        void reportErrorWarning(const char* warningString) override;
        void draw3dText(const btVector3& location, const char* textString) override;
        void setDebugMode(int debugMode)override;

		int getDebugMode() const override;

	};

}

#endif

