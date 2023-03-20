#pragma once

#include "Component.h"
#include "EntityComponent/Entity.h"

class InputManager;

class VehicleController : public me::Component {
private:
    float mSpeed;
    float mRotationSpeed;
    float mDriftFactor;

public:
    VehicleController(float s, float rs, float df);

    void update();
};



