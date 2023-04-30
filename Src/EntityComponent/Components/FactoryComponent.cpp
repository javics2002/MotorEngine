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
#include "UIText.h"
#include "UIButton.h"

using namespace me;

float me::FactoryComponent::Value(Parameters& params, const ParameterName& parameter, float defaultValue)
{
    return params.count(parameter) ? std::stof(params[parameter]) : defaultValue;
}

int me::FactoryComponent::Value(Parameters& params, const ParameterName& parameter, int defaultValue)
{
    return params.count(parameter) ? std::stoi(params[parameter]) : defaultValue;
}

bool me::FactoryComponent::Value(Parameters& params, const ParameterName& parameter, bool defaultValue)
{
    return params.count(parameter) ? (bool) std::stoi(params[parameter]) : defaultValue;
}

std::string me::FactoryComponent::Value(Parameters& params, const ParameterName& parameter, std::string defaultValue)
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
    transform->setPosition(Vector3(Value(params, "position_x", 0.0f),
        Value(params, "position_y", 0.0f), Value(params, "position_z", 0.0f)));
    transform->setRotation(Vector3(Value(params, "rotation_x", 0.0f),
        Value(params, "rotation_y", 0.0f), Value(params, "rotation_z", 0.0f)));
    transform->setScale(Vector3(Value(params, "scale_x", 1.0f),
        Value(params, "scale_y", 1.0f), Value(params, "scale_z", 1.0f)));
    std::string transformParent = Value(params, "parentname", std::string());
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

    audioSource->setSourceName(Value(params, "source", std::string()));
    audioSource->setSourcePath(Value(params, "path", std::string()));
    audioSource->setPlayOnStart(Value(params, "onstart", false));
    audioSource->setVolume(Value(params, "volume", 1));
    audioSource->setIs3D(Value(params, "3d", false));
    audioSource->setLoop(Value(params, "loop", false));

    return audioSource;
}

void me::FactoryAudioSource::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryCamera::create(Parameters& params)
{
    Camera* camera = new Camera();

    camera->setName(Value(params, "name", std::string("Main")));
    camera->setNearDistance(Value(params, "neardistance", .1f));
    camera->setFarDistance(Value(params, "fardistance", 1000));
    camera->setAutoRadio(Value(params, "autoratio", false));
    camera->setZOrder(Value(params, "zorder", 0));
    camera->setBackgroundColour(Vector4(Value(params, "backgroundcolor_r", .0f), Value(params, "backgroundcolor_g", .0f),
        Value(params, "backgroundcolor_b", .0f), Value(params, "backgroundcolor_a", 1.0f)));
    camera->setLookAt(Vector3(Value(params, "lookat_x", 0), Value(params, "lookat_y", 0), Value(params, "lookat_z", 0)));
    camera->init();

    camera->setViewportDimension(Value(params, "viewport_left", 0.0f), Value(params, "viewport_top", 0.0f), Value(params, "viewport_width", 1.0f), Value(params, "viewport_height", 1.0f));
    camera->setViewportOverlayEnabled(Value(params, "overlayenable", true));
    
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
    
    std::string mesh = Value(params, "mesh", std::string());
    std::string meshName = Value(params, "meshname", std::string());
    std::string materialName = Value(params, "materialname", std::string());
    bool staticState = Value(params, "staticobj", false);

    MeshRenderer* meshRenderer = new MeshRenderer();
    meshRenderer->setName(mesh);
    meshRenderer->setMeshName(meshName);
    meshRenderer->setStatic(staticState);

    meshRenderer->init();

    meshRenderer->setMaterial(materialName);
    return meshRenderer;
}

void me::FactoryMeshRenderer::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryParticleSystem::create(Parameters& params)
{

    std::string particle = Value(params, "particle", std::string());
    std::string particleName = Value(params, "particlename", std::string());
    bool emitted = Value(params, "emitted", false);

    ParticleSystem* particleSystem = new ParticleSystem();

    particleSystem->setName(particle);
    particleSystem->setParticleName(particleName);
    particleSystem->setOffsetPos(Vector3(Value(params, "offpos_x", 0.0f),
        Value(params, "offpos_y", 0.0f), Value(params, "offpos_z", 0.0f)));
    particleSystem->setOffsetScale(Vector3(Value(params, "offscale_x", 0.0f),
        Value(params, "offscale_y", 0.0f), Value(params, "offscale_z", 0.0f)));

    particleSystem->init();

    particleSystem->setEmitting(emitted);
    return particleSystem;
}

void me::FactoryParticleSystem::destroy(Component* component)
{
    delete component;
}

me::Component* me::FactoryRigidBody::create(Parameters& params)
{
    RigidBody* rigidbody = new RigidBody();

    rigidbody->setMass(Value(params, "mass", 0.0f));
    rigidbody->setRestitution(Value(params, "restitution", 0.0f));
    rigidbody->setFriction(Value(params, "friction", 0.0f));
    rigidbody->setTrigger(Value(params, "istrigger", false));
    rigidbody->setColShape(Shapes(Value(params, "colshape", SHAPES_BOX)));
    rigidbody->setColliderScale(Vector3(Value(params, "colliderscale_x", 1.0f),
        Value(params, "colliderscale_y", 1.0f), Value(params, "colliderscale_z", 1.0f)));
    rigidbody->setMomeventType(MovementType(Value(params, "mvtype", MOVEMENT_TYPE_STATIC)));
    rigidbody->setMask(Value(params, "mask", 15));
    rigidbody->setGroup(Value(params, "group", 1));

    return rigidbody;
}

void me::FactoryRigidBody::destroy(Component* component)
{
    delete component;
}

Component* me::FactoryLight::create(Parameters& params)
{
    Light* light = new Light();

    light->setName(Value(params, "name", std::string("Light")));
    light->setDirection(Vector3(Value(params, "direction_x", 0.0f),
        Value(params, "direction_y", -1.0f), Value(params, "direction_z", 0.0f)));
    light->setLightType((LightType)Value(params, "type", 0));
    light->setColor(Vector3(Value(params, "color_r", 1.0f),
        Value(params, "color_g", 1.0f), Value(params, "color_b", 1.0f)));

    if (params.count("ambientcolor_r"))
        light->setAmbientColor(Vector3(Value(params, "ambientcolor_r", 1.0f),
            Value(params, "ambientcolor_g", 1.0f), Value(params, "ambientcolor_b", 1.0f)));

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
    std::string sprite = Value(params, "sprite", std::string());
    std::string materialName = Value(params, "materialname", std::string());
    int zOrder = Value(params, "zorder", 1);
    bool staticState = Value(params, "staticobj", false);

    UISpriteRenderer* spriteRenderer = new UISpriteRenderer();
    spriteRenderer->init(sprite, materialName,zOrder);
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
    transform->setPosition(Vector2(Value(params, "position_x", 0.0f),
        Value(params, "position_y", 0.0f)));
    transform->setRotation(Value(params, "rotation", 0.0f));
    transform->setScale(Vector2(Value(params, "scale_x", 1.0f),
        Value(params, "scale_y", 1.0f)));
    return transform;
}

void me::FactoryUITransform::destroy(Component* component)
{
    delete component;
}

Component* me::FactoryUIText::create(Parameters& params)
{
    if (params.empty())
    {
        return new UIText();
    }
    std::string name = Value(params, "name", std::string());
    std::string text = Value(params, "text", std::string());
    int zOrder = Value(params, "zorder", 1);

    UIText* textRenderer = new UIText();
    textRenderer->init(name,text, zOrder);

    return textRenderer;
}

void me::FactoryUIText::destroy(Component* component)
{
    delete component;
}
