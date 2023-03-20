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

Component* FactoryAnimator::create(Parameters params)
{
    Animator* animator = new Animator();
    /*if(params.count("animation"))
        animator->playAnim(value<std::string>(params, "animation"), value(params, "loop", true));*/
    return animator;
}

me::Component* me::FactoryTransform::create(Parameters params)
{
    Transform* transform = new Transform();
    transform->setPosition(Vector3(value(params, "position_x", 0.0f),
        value(params, "position_y", 0.0f), value(params, "position_z", 0.0f)));
    // transform->setRotation();  TO DO VECTOR 3 TO QUATERNION
    transform->setScale(Vector3(value(params, "scale_x", 0.0f),
        value(params, "scale_y", 0.0f), value(params, "scale_z", 0.0f)));
    return transform;
}

me::Component* me::FactoryAudioListener::create(Parameters params)
{
    return nullptr;
}

me::Component* me::FactoryAudioSource::create(Parameters params)
{
    return nullptr;
}

me::Component* me::FactoryCamera::create(Parameters params)
{
    return nullptr;
}

me::Component* me::FactoryCollider::create(Parameters params)
{
    Collider* collider = new Collider();
    // TODO: Y los setters????

    return collider;
}

me::Component* me::FactoryMeshRenderer::create(Parameters params)
{
    std::string mesh = value(params, "mesh", std::string());
    std::string meshName = value(params, "meshname", std::string());

    MeshRenderer* meshRenderer = new MeshRenderer(mesh, meshName);

    return meshRenderer;
}

me::Component* me::FactoryParticleSystem::create(Parameters params)
{
    return nullptr;
}

me::Component* me::FactoryRigidBody::create(Parameters params)
{
    RigidBody* rigidbody = new RigidBody();
    rigidbody->setMass(value(params, "mass", 0.0f));
    rigidbody->setRestitution(value(params, "restitution", 0.0f));
    rigidbody->setFriction(value(params, "friction", 0.0f));
    rigidbody->setTrigger(value(params, "istrigger", false));
    
    // TODO: colShape??
    // TODO: mvType??

    return rigidbody;
}

float me::FactoryComponent::value(Parameters params, std::string parameter, float defaultValue)
{
    return params.count(parameter) ? std::stof(params[parameter]) : defaultValue;
}

int me::FactoryComponent::value(Parameters params, std::string parameter, int defaultValue)
{
    return params.count(parameter) ? std::stoi(params[parameter]) : defaultValue;
}

bool me::FactoryComponent::value(Parameters params, std::string parameter, bool defaultValue)
{
    return params.count(parameter) ? (bool) std::stoi(params[parameter]) : defaultValue;
}

std::string me::FactoryComponent::value(Parameters params, std::string parameter, std::string defaultValue)
{
    return params.count(parameter) ? params[parameter] : defaultValue;
}
