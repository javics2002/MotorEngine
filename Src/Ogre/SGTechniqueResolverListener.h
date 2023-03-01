#pragma once

#include "OgreRTShaderSystem.h"
#include "OgreMaterialManager.h"

namespace me {

    class SGTechniqueResolverListener : public Ogre::MaterialManager::Listener {
    public:
        explicit SGTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator);

        Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
            const Ogre::String& schemeName,
            Ogre::Material* originalMaterial, unsigned short lodIndex,
            const Ogre::Renderable* rend) override;

        bool afterIlluminationPassesCreated(Ogre::Technique* tech) override;

        bool beforeIlluminationPassesCleared(Ogre::Technique* tech) override;

    protected:
        Ogre::RTShader::ShaderGenerator* mShaderGenerator; // The shader generator instance.
    };
}
