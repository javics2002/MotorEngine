#pragma once
#ifndef __DEBUG_DRAWER
#define __DEBUG_DRAWER

#include "MotorEngine/MotorEngineAPI.h"
#include <LinearMath/btIDebugDraw.h>

#include <Ogre.h>

namespace me {
    /**
    In charge of drawing the collision boxes of objects
    */
	class __MOTORENGINE_API DebugDrawer : public btIDebugDraw
	{

        Ogre::ManualObject* line;
        std::vector<Ogre::ManualObject*> lines;
		DebugDrawModes mDebugDrawModes;

	public:
		DebugDrawer();
		~DebugDrawer();

        /*
        Remove the old lines of the collider
        */
        void clear();

        /*
        Draws a line between two points indicated with a specific color
        */
        void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

        /*
        Method created to be able to use the class (virtual method)
        */
        void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,btScalar distance, int lifeTime, const btVector3& color) override;

        /*
        Method created to be able to use the class (virtual method)
        */
        void reportErrorWarning(const char* warningString) override;

        /*
        Method created to be able to use the class (virtual method)
        */
        void draw3dText(const btVector3& location, const char* textString) override;

        /*
        Set the flags for the desired debug
        */
        void setDebugMode(int debugMode)override;

        /*
        Returns the flags assigned to the debug
        */
		int getDebugMode() const override;

	};

}

#endif

