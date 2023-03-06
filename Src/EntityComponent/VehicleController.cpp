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
    bool right = me::im().getButton("RIGHT");
    float deltaX = me::im().getAxis("HORIZONTAL");

    // Rotate the vehicle if the player is using DualShock or Xbox controller
    if(deltaX != 0) {
        if (drift) {
            // If the vehicle is drifting, rotate it based on the drift factor
            mEntity->getComponent<me::Transform>("transform")->rotate( mRotationSpeed * deltaX * mDriftFactor, me::AXIS_ROTATIONS_Y);
        }
        else {
            // Otherwise, rotate it normally
            mEntity->getComponent<me::Transform>("transform")->rotate(mRotationSpeed * deltaX, me::AXIS_ROTATIONS_Y);
        }
    }
    //If the player is using keyboard
    else if(left)
        mEntity->getComponent<me::Transform>("transform")->rotate(-mRotationSpeed, me::AXIS_ROTATIONS_Y);
    else if(right)
        mEntity->getComponent<me::Transform>("transform")->rotate(mRotationSpeed, me::AXIS_ROTATIONS_Y);

    // Move the vehicle forward or backward
    me::Vector3 v;
    if (acelerate) {
        // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
        mEntity->getComponent<me::RigidBody>("transform")->addImpulse(v.forward()*mSpeed,mEntity->getComponent<me::Transform>("transform")->getPosition());
    }
    else if (decelerate) {
        // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
        mEntity->getComponent<me::RigidBody>("transform")->addImpulse(v.forward()*-mSpeed,mEntity->getComponent<me::Transform>("transform")->getPosition());
    }
}
