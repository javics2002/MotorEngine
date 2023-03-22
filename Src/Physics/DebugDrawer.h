#pragma once
#ifndef __DEBUG_DRAWER
#define __DEBUG_DRAWER

#include "MotorEngine/MotorEngineAPI.h"
#include <LinearMath/btIDebugDraw.h>

#include <Ogre.h>

namespace me {

	class __MOTORENGINE_API DebugDrawer : public btIDebugDraw // public Ogre::FrameListener
	{

		Ogre::ManualObject* mTriangles;
		DebugDrawModes mDebugDrawModes;

        //struct ContactPoint {
        //    Ogre::Vector3 from;
        //    Ogre::Vector3 to;
        //    Ogre::ColourValue color;
        //    size_t dieTime;
        //};

        //Ogre::ManualObject* mTriangles_;
        //std::vector<ContactPoint>* mContactPoints_;
        //std::vector<ContactPoint> mContactPoints1_;
        //std::vector<ContactPoint> mContactPoints2_;

	//protected:

	//	bool frameStarted(const Ogre::FrameEvent& evt) override;
 //       bool frameEnded(const Ogre::FrameEvent& evt) override;

	public:
		DebugDrawer();
		~DebugDrawer();

		virtual void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar alpha) override;

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

