Entities = {
	-- Circuit = {
	--     Transform = {
    --         position = { x = 0, y = 0, z = 0 },
	-- 		rotation = { x = -90, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1 }
	--     },
	--     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- },
    --     -- collider = {
    --     --     shape = "box",
    --     --     size = { x = 1, y = 1, z = 1 }
    --     -- },
    --     meshrenderer = {
    --         mesh = "circuit",
    --         meshName = "CircuitoEscalaArreglada.mesh",
    --         -- materialName = "Material/roja"
    --     }
	-- },

    CarMaterialTest = {
        Transform = {
            position = { x= 0, y = 0, z = 0 },
            scale = { x = 0.8, y = 0.8, z = 0.8 },
            rotation = {x = 0, y = 60, z = 0}
        },
        meshrenderer = {
            mesh = "kart",
            meshName = "Kart.mesh",
            -- materialName = "kartA"
        }
	},

    SpriteTest = {
        UITransform = {
            position = { x = 0.05, y = 0.07 },
            scale = { x = 0.1, y = 0.15 },
            rotation = 0
        },
        UISpriteRenderer = {
            sprite = "oil",     -- Nombre Interno
            materialName = "oil"  -- Nombre en MaterialsResource
        }
    },

    SpriteTest2 = {
        UITransform = {
            position = { x = 0.8, y = 0.8 },
            scale = { x = 0.1, y = 0.15 },
            rotation = 0
        },
        UISpriteRenderer = {
            sprite = "lightning",     -- Nombre Interno
            materialName = "lightningBolt"  -- Nombre en MaterialsResource
        }
    },

    SpriteTest3 = {
        UITransform = {
            position = { x = 0.05, y = 0.8 },
            scale = { x = 0.1, y = 0.15 },
            rotation = 0
        },
        UISpriteRenderer = {
            sprite = "nerf",     -- Nombre Interno
            materialName = "nerf"  -- Nombre en MaterialsResource
        }
    },

	Cube = {
        Transform = {
            position = { x = 0, y = 10, z = 0 },
            scale = { x = 1, y = 1, z = 1 },
            rotation = {x = 0, y = 0, z = 0}
        },
		meshrenderer = {
            mesh = "cube",
            meshName = "Suzanne.mesh",
        },
		RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
		    restitution = .5,
		    friction = .3,
		    isTrigger = true
	    },
        collider = {
            shape = "box",
            size = { x = 1, y = 1, z = 1 }
        },
		
	},

	-- Car = {
        -- Transform = {
            -- position = { x= 0, y = 0, z = 0 },
            -- scale = { x = 0.8, y = 0.8, z = 0.8 },
            -- rotation = {x = 0, y = 180, z = 0}
        -- },
        -- RigidBody = {
            -- colShape = 1,
            -- mvType = 0,
            -- mass = 5,
            -- restitution = .5,
            -- friction = .1,
            -- isTrigger = false
        -- },
        -- vehicleController = {
            -- speed = 20;
            -- rotationspeed = 5;
            -- driftFactor = 1;
            -- playerNumber = 0;
        -- },
        -- meshrenderer = {
            -- mesh = "kart",
            -- meshName = "Kart.mesh",
            -- --materialName = "Material/roja"
        -- }
	-- },
    
    -- Cube = {
        -- Transform = {
            -- position = { x = -10, y = 1, z = 0 },
            -- scale = { x = .015, y = .015, z = .015 },
            -- rotation = {x = 0, y = 0, z = 0}
        -- },
        -- RigidBody = {
            -- colShape = 1,
            -- mvType = 0,
            -- mass = 5,
            -- restitution = .5,
            -- friction = .01,
            -- isTrigger = false
        -- },
        -- vehicleController = {
            -- speed = 3;
            -- rotationspeed = 3;
            -- driftFactor = 1;
            -- playerNumber = 0;
        -- },
        -- meshrenderer = {
            -- mesh = "cube",
            -- meshName = "cube.mesh",
            -- --materialName = "Material/roja"
        -- }
	-- },
    
    camera = {
        transform = {
            position = { x = 30, y = 10, z = 0 }
        },
        camera = {
            lookat = { x = 0, y = 10, z = 0 },
            name = "main",
            neardistance = 10,
            fardistance = 100000,
            autoratio = true,
            zorder = 0,
            backgroundcolor = { r = .72, g = .92, b = 1, a = 1  }
        }
        -- camerafollow = { target = car }
    },

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "DirectionalLight",
            direction = { x = 1, y = -1, z = -1 },
            type = 0
        }
    }
}


