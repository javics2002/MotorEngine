#include "FactoryComponent.h"
#include "Animator.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "Camera.h"
#include "Collider.h"
#include "MeshRenderer.h"
#include "UISpriteRenderer.h"
#include "ParticleSystem.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "Light.h"
#include "UITransform.h"

using namespace me;

float me::FactoryComponent::value(Parameters& params, const ParameterName& parameter, float defaultValue)
{
    return params.count(parameter) ? std::stof(params[parameter]) : defaultValue;
}

int me::FactoryComponent::value(Parameters& params, const ParameterName& parameter, int defaultValue)
{
    return params.count(parameter) ? std::stoi(params[parameter]) : defaultValue;
}

bool me::FactoryComponent::value(Parameters& params, const ParameterName& parameter, bool defaultValue)
{
    return params.count(parameter) ? (bool) std::stoi(params[parameter]) : defaultValue;
}

std::string me::FactoryComponent::value(Parameters& params, const ParameterName& parameter, std::string defaultValue)
{
    auto ci = params.count(parameter);
    return params.count(parameter) ? params[parameter] : defaultValue;
}

Component* FactoryAnimator::create(Parameters& params)
{
    Animator* animator = new Animator();
    /*if(params.count("animation"))
        animator->playAnim(value<std::string>(params, "animation"), value(params, "loop", true));*/
    return animator;
}

void me::FactoryAnimator::destroy(Component* component)
{
    delete component;
}

Component* FactoryTransform::create(Parameters& params)
{
    Transform* transform = new Transform();
    transform->setPosition(Vector3(value(params, "position_x", 0.0f),
        value(params, "position_y", 0.0f), value(params, "position_z", 0.0f)));
    transform->setRotation(Vector3(value(params, "rotation_x", 0.0f),
        value(params, "rotation_y", 0.0f), value(params, "rotation_z", 0.0f)));
    transform->setScale(Vector3(value(params, "scale_x", 1.0f),
        value(params, "scale_y", 1.0f), value(params, "scale_z", 1.0f)));
    std::string transformParent = value(params, "parentname", std::string());
    transform->setParentName(transformParent);
    return transform;
}

void me::FactoryTransform::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryAudioListener::create(Parameters& params)
{
    AudioListener* audioListener = new AudioListener();

    return audioListener;
}

void me::FactoryAudioListener::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryAudioSource::create(Parameters& params)
{
    AudioSource* audioSource = new AudioSource();

    audioSource->setSource(value(params, "source", std::string()));
    audioSource->setPlayOnStart(value(params, "onstart", false));
    audioSource->setVolume(value(params, "volume", 1));
    audioSource->setIs3D(value(params, "3d", false));
    audioSource->setLoop(value(params, "loop", false));

    return audioSource;
}

void me::FactoryAudioSource::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryCamera::create(Parameters& params)
{
    Camera* camera = new Camera();

    camera->setName(value(params, "name", std::string("Main")));
    camera->setNearDistance(value(params, "neardistance", .1f));
    camera->setFarDistance(value(params, "fardistance", 1000));
    camera->setAutoRadio(value(params, "autoratio", false));
    camera->setZOrder(value(params, "zorder", 0));
    camera->setBackgroundColour(Vector4(value(params, "backgroundcolor_r", .0f), value(params, "backgroundcolor_g", .0f),
        value(params, "backgroundcolor_b", .0f), value(params, "backgroundcolor_a", 1.0f)));
    camera->setLookAt(Vector3(value(params, "lookat_x", 0), value(params, "lookat_y", 0), value(params, "lookat_z", 0)));

    return camera;
}

void me::FactoryCamera::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryCollider::create(Parameters& params)
{
    Collider* collider = new Collider();

    return collider;
}

void me::FactoryCollider::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryMeshRenderer::create(Parameters& params)
{
    if (params.empty())
    {
        return new MeshRenderer();
    }
    std::string mesh = value(params, "mesh", std::string());
    std::string meshName = value(params, "meshname", std::string());
    std::string materialName = value(params, "materialname", std::string());
    bool staticState = value(params, "staticobj", false);

    MeshRenderer* meshRenderer = new MeshRenderer(mesh, meshName);
    meshRenderer->setMaterial(materialName);
    meshRenderer->setStatic(staticState);

    return meshRenderer;
}

void me::FactoryMeshRenderer::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryParticleSystem::create(Parameters& params)
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

void me::FactoryParticleSystem::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryRigidBody::create(Parameters& params)
{
    RigidBody* rigidbody = new RigidBody();

    rigidbody->setMass(value(params, "mass", 0.0f));
    rigidbody->setRestitution(value(params, "restitution", 0.0f));
    rigidbody->setFriction(value(params, "friction", 0.0f));
    rigidbody->setTrigger(value(params, "istrigger", false));
    rigidbody->setColShape(Shapes(value(params, "colshape", SHAPES_BOX)));
    rigidbody->setColliderScale(Vector3(value(params, "colliderscale_x", 1.0f),
        value(params, "colliderscale_y", 1.0f), value(params, "colliderscale_z", 1.0f)));
    rigidbody->setMomeventType(MovementType(value(params, "mvtype", MOVEMENT_TYPE_STATIC)));

    return rigidbody;
}

void me::FactoryRigidBody::destroy(Component* component)
{
    delete component;
}

Component* me::FactoryLight::create(Parameters& params)
{
    Light* light = new Light();

    light->setName(value(params, "name", std::string("Light")));
    light->setDirection(Vector3(value(params, "direction_x", 0.0f),
        value(params, "direction_y", -1.0f), value(params, "direction_z", 0.0f)));
    light->setLightType((LightType) value(params, "type", 0));

    return light;
}

void me::FactoryLight::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryUISpriteRenderer::create(Parameters& params)
{
    if (params.empty())
    {
        return new UISpriteRenderer();
    }
    std::string sprite = value(params, "sprite", std::string());
    std::string materialName = value(params, "materialname", std::string());
    bool staticState = value(params, "staticobj", false);

    UISpriteRenderer* spriteRenderer = new UISpriteRenderer(sprite, materialName);
    spriteRenderer->setStatic(staticState);

    return spriteRenderer;
}

void me::FactoryUISpriteRenderer::destroy(Component* component)
{
    delete component;
}

Component* me::FactoryUITransform::create(Parameters& params)
{
    UITransform* transform = new UITransform();
    transform->setPosition(Vector2(value(params, "position_x", 0.0f),
        value(params, "position_y", 0.0f)));
    transform->setRotation(value(params, "rotation", 0.0f));
    transform->setScale(Vector2(value(params, "scale_x", 1.0f),
        value(params, "scale_y", 1.0f)));
    return transform;
}

void me::FactoryUITransform::destroy(Component* component)
{
    delete component;
}
