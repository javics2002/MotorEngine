#pragma once

#ifndef __RENDER_SGTECHNIQUERESOLVERLISTENER
#define __RENDER_SGTECHNIQUERESOLVERLISTENER

#include "MotorEngine/MotorEngineAPI.h"
#include "OgreRTShaderSystem.h"
#include "OgreMaterialManager.h"

namespace me {
    /**
    Default implementation of a Listener to use with the Ogre::RTShader system.
    When a target scheme callback is invoked with the shader generator scheme it tries to create an equivalent shader
    based technique based on the default technique of the given material.
    */
    class __MOTORENGINE_API SGTechniqueResolverListener : public Ogre::MaterialManager::Listener {
    public:
        explicit SGTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator);

        /** 
        This is the hook point where shader based technique will be created.
        It will be called whenever the material manager won't find appropriate technique
        that satisfy the target scheme name. If the scheme name is out target RT Shader System
        scheme name we will try to create shader generated technique for it.
        */
        Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
            const Ogre::String &schemeName,
            Ogre::Material* originalMaterial, unsigned short lodIndex,
            const Ogre::Renderable* rend) override;

        bool afterIlluminationPassesCreated(Ogre::Technique* tech) override;

        bool beforeIlluminationPassesCleared(Ogre::Technique* tech) override;

    protected:
        // The shader generator instance.
        Ogre::RTShader::ShaderGenerator* mShaderGenerator; 
    };
}

#endif