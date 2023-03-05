#include "VehicleController.h"
#include <SDL/InputManager.h>
#include "Transform.h"
#include "Utils/Vector3.h"
#include "RigidBody.h"



VehicleController::VehicleController(float s, float rs, float df)
{
    // Constructor - Initializes the speed, rotation speed, and drift factor variables
    mSpeed = s;
    mRotationSpeed = rs;
    mDriftFactor = df;
}


/**
Returns the difference between this vector and another vector

@param v The other vector to subtract from this vector
@return The difference between this vector and the other vector
*/
void VehicleController::update()
{
    // Get the input
    bool acelerate = me::im().getButton("ACELERATE");
    bool decelerate = me::im().getButton("DECELERATE");
    bool drift = me::im().getButton("DRIFT");

    //If the player is using keyboard
    bool left = me::im().getButton("LEFT");
    bool rigth = me::im().getButton("RIGTH");
    float deltaX; me::im().getAxis("HORIZONTAL");

    // Rotate the vehicle if the player is using DualShock or Xbox controller
    if(deltaX != 0) {
        if (drift) {
            // If the vehicle is drifting, rotate it based on the drift factor
            mEntity->getComponent<me::Transform>()->rotate(me::Vector3(0, mRotationSpeed * deltaX * mDriftFactor, 0));
        }
        else {
            // Otherwise, rotate it normally
            mEntity->getComponent<me::Transform>()->rotate(me::Vector3(0, mRotationSpeed * deltaX, 0));
        }
    }
    //If the player is using keyboard
    else if(left)
        mEntity->getComponent<me::Transform>()->rotate(me::Vector3(0, -mRotationSpeed, 0));
    else if(rigth)
        mEntity->getComponent<me::Transform>()->rotate(me::Vector3(0, mRotationSpeed, 0));

    // Move the vehicle forward or backward
    me::Vector3 v;
    if (acelerate) {
        // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
        mEntity->getComponent<me::RigidBody>()->addImpulse(v.forward()*mSpeed,mEntity->getComponent<me::Transform>()->getPosition());
    }
    else if (decelerate) {
        // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
        mEntity->getComponent<me::RigidBody>()->addImpulse(v.forward()*-mSpeed,mEntity->getComponent<me::Transform>()->getPosition());
    }
}
