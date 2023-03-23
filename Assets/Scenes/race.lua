Entities = {
	Circuit = {
	    Transform = {
            position = { x = 0, y = 200, z = 0 },
            scale = { x = .1, y = .1, z = .1 }
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
            meshName = "cube.mesh"
        }
	},

	Car = {
        Transform = {
            position = { y = 1 }
        }
	},
    
    Camera = {
        Transform = {
        }
    }

    -- CameraFollow = { target = Car }

    -- Lights
}


