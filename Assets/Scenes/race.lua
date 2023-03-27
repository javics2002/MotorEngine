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
            mvType = 2,
            mass = 5,
            restitution = .5,
            friction = .3,
            isTrigger = false
        },
        vehicleController = {
            speed = 0.05;
            rotationspeed = 3;
            driftFactor = 1;
        },
        meshrenderer = {
            mesh = "kart",
            meshName = "Kart.mesh",
            --materialName = "Material/roja"
        }
	},
    
    Camera = {
        Transform = {
        }
    }

    -- CameraFollow = { target = Car }

    -- Lights
}


