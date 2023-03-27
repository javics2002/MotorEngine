#include "FactoryComponent.h"
#include "Animator.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "Camera.h"
#include "Collider.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "Rigidbody.h"
#include "Transform.h"

using namespace me;

float me::FactoryComponent::value(Parameters params, const ParameterName& parameter, float defaultValue)
{
    return params.count(parameter) ? std::stof(params[parameter]) : defaultValue;
}

int me::FactoryComponent::value(Parameters params, const ParameterName& parameter, int defaultValue)
{
    return params.count(parameter) ? std::stoi(params[parameter]) : defaultValue;
}

bool me::FactoryComponent::value(Parameters params, const ParameterName& parameter, bool defaultValue)
{
    return params.count(parameter) ? (bool)std::stoi(params[parameter]) : defaultValue;
}

std::string me::FactoryComponent::value(Parameters params, const ParameterName& parameter, std::string defaultValue)
{
    return params.count(parameter) ? params[parameter] : defaultValue;
}

Component* FactoryAnimator::create(Parameters params)
{
    Animator* animator = new Animator();
    /*if(params.count("animation"))
        animator->playAnim(value<std::string>(params, "animation"), value(params, "loop", true));*/
    return animator;
}

Component* FactoryTransform::create(Parameters params)
{
    Transform* transform = new Transform();
    transform->setPosition(Vector3(value(params, "position_x", 0.0f),
        value(params, "position_y", 0.0f), value(params, "position_z", 0.0f)));
    transform->setRotation(Vector3(value(params, "rotation_x", 0.0f),
        value(params, "rotation_y", 0.0f), value(params, "rotation_z", 0.0f)));
    transform->setScale(Vector3(value(params, "scale_x", 1.0f),
        value(params, "scale_y", 1.0f), value(params, "scale_z", 1.0f)));
    return transform;
}

me::Component* me::FactoryAudioListener::create(Parameters params)
{

    AudioListener* audioListener = new AudioListener();

    return audioListener;
}

me::Component* me::FactoryAudioSource::create(Parameters params)
{
    AudioSource* audioSource = new AudioSource();

    audioSource->setSource(value(params, "source", std::string()));
    audioSource->setPlayOnStart(value(params, "onStart", false));
    audioSource->setVolume(value(params, "volume", 1));
    audioSource->setIs3D(value(params, "3D", false));
    audioSource->setLoop(value(params, "loop", false));

    return audioSource;
}

me::Component* me::FactoryCamera::create(Parameters params)
{
    Camera* camera = new Camera();

    camera->setName(value(params, "name", std::string()));
    camera->setNearDistance(value(params, "nearDistance", 1));
    camera->setFarDistance(value(params, "farDistance", 1));
    camera->setAutoRadio(value(params, "autoRadio", false));
    camera->setZOrder(value(params, "zOrder", false));
    camera->setLookAt(Vector3(value(params, "lookAt_x", 0), value(params, "lookAt_y", 0), value(params, "lookAt_y", 0)));

    return camera;
}

me::Component* me::FactoryCollider::create(Parameters params)
{
    Collider* collider = new Collider();

    return collider;
}

me::Component* me::FactoryMeshRenderer::create(Parameters params)
{
    std::string mesh = value(params, "mesh", std::string());
    std::string meshName = value(params, "meshname", std::string());
    std::string materialName = value(params, "materialname", std::string());
    bool staticState = value(params, "staticobj", false);

    MeshRenderer* meshRenderer = new MeshRenderer(mesh, meshName);
    meshRenderer->setMaterial(materialName);
    meshRenderer->setStatic(staticState);

    return meshRenderer;
}

me::Component* me::FactoryParticleSystem::create(Parameters params)
{

    std::string particle = value(params, "particle", std::string());
    std::string particleName = value(params, "particlename", std::string());
    bool emitted = value(params, "emitted", false);    

    ParticleSystem* particleSystem = new ParticleSystem(particle, particleName);
    particleSystem->setEmitting(emitted);
    particleSystem->setOffsetPos(Vector3(value(params, "offpos_x", 0.0f),
        value(params, "offpos_y", 0.0f), value(params, "offpos_z", 0.0f)));
    particleSystem->setOffsetScale(Vector3(value(params, "offscale_x", 0.0f),
        value(params, "offscale_y", 0.0f), value(params, "offscale_z", 0.0f)));

    return particleSystem;
}

me::Component* me::FactoryRigidBody::create(Parameters params)
{
    RigidBody* rigidbody = new RigidBody();

    rigidbody->setMass(value(params, "mass", 0.0f));
    rigidbody->setRestitution(value(params, "restitution", 0.0f));
    rigidbody->setFriction(value(params, "friction", 0.0f));
    rigidbody->setTrigger(value(params, "istrigger", false));
    rigidbody->setColShape(value(params, "colshape", 1));
    rigidbody->setMomeventType(value(params, "mvtype", 1));

    return rigidbody;
}
