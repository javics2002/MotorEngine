Entities = {
	Circuit = {
	    Transform = {
            position = { x = 0, y = 0, z = 0 },
            scale = { x = 5.3, y = 1, z = 1.4 }
	    },
	    -- RigidBody = {
		--     colShape = 1,
		--     mvType = static,
		--     mass = 5,
		--     restitution = .5,
		--     friction = .3,
		--     isTrigger = false
	    -- },
        -- collider = {
        --     shape = "box",
        --     size = { x = 1, y = 1, z = 1 }
        -- },
        meshrenderer = {
            mesh = "p",
            meshName = "Circuito.mesh",
            --materialName = "Material/roja"
        }
	},

	Car = {
        Transform = {
            position = { x= -1.3, y = 0.1, z = -1 },
            scale = { x = 0.015, y = 0.015, z = 0.015 },
            rotation = {x = 0, y = 180, z = 0}
        },
        RigidBody = {
            colShape = 1,
            mvType = 0,
            mass = 5,
            restitution = .5,
            friction = .01,
            isTrigger = false
        },
        vehicleController = {
            speed = 3;
            rotationspeed = 3;
            driftFactor = 1;
            playerNumber = 0;
        },
        meshrenderer = {
            mesh = "kart",
            meshName = "Kart.mesh",
            --materialName = "Material/roja"
        }
	},
    
    Camera = {
        Transform = {
            position = { x = 0, y = .45, z = -.8 }
        },
        Camera = {
            lookAt = { x = -1000, y = 0, z = 0 },
            name = "Main",
            nearDistance = 0.1,
            farDistance = 10000,
            autoRatio = true,
            zOrder = 0,
            backgroundColor = { r = .72, g = .92, b = 1, a = 1  }
        }
        -- CameraFollow = { target = Car }
    },

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "DirectionalLight",
            direction = { x = 0, y = -1, z = -1 },
            type = 0
        }
    }
}


