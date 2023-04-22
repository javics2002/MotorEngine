Entities = {
	Circuit = {
	    Transform = {
            position = { x = 0, y = 5, z = 0 },
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 80, y = 25, z = 20} --80 30 40
	    },
	    RigidBody = {
		    colShape = 2,
		    mvType = static,
		    mass = 5,
            group = 2,
            mask = 6,
            colliderscale = {x = 1.5, y = 0.01, z = 1.5},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        meshrenderer = {
            mesh = "circuit",
            meshName = "Circuito.mesh",
            -- materialName = "Material/roja"
        }
	},

    ParedDerecha = {
        Transform = {
            position = { x = 0, y = 5, z = 20.5},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 91, y = 10, z = 0.01},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedIzquierda = {
        Transform = {
            position = { x = 0, y = 5, z = -20.5},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 91, y = 10, z = 0.01},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFondo1 = {
        Transform = {
            position = { x = 104, y = 5, z = 0},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFondo2 = {
        Transform = {
            position = { x = 101, y = 5, z = -12},
			rotation = { x = 0, y = 22, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFondo3 = {
        Transform = {
            position = { x = 100, y = 5, z = -12},
			rotation = { x = 0, y = 35, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFondo4 = {
        Transform = {
            position = { x = 97, y = 5, z = -15},
			rotation = { x = 0, y = 50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFondo5 = {
        Transform = {
            position = { x = 101, y = 5, z = 12},
			rotation = { x = 0, y = -22, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFondo6 = {
        Transform = {
            position = { x = 100, y = 5, z = 12},
			rotation = { x = 0, y = -35, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFondo7 = {
        Transform = {
            position = { x = 97, y = 5, z = 15},
			rotation = { x = 0, y = -50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFrente1 = {
        Transform = {
            position = { x = -98.5, y = 5, z = 0},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFrente2 = {
        Transform = {
            position = { x = -95.5, y = 5.5, z = -12},
			rotation = { x = 0, y = -22, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFrente3 = {
        Transform = {
            position = { x = -94.5, y = 5, z = -12},
			rotation = { x = 0, y = -35, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFrente4 = {
        Transform = {
            position = { x = -91.5, y = 5, z = -15},
			rotation = { x = 0, y = -50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFrente5 = {
        Transform = {
            position = { x = -95.5, y = 5.5, z = 12},
			rotation = { x = 0, y = 22, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFrente6 = {
        Transform = {
            position = { x = -94.5, y = 5, z = 12},
			rotation = { x = 0, y = 35, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    ParedFrente7 = {
        Transform = {
            position = { x = -91.5, y = 5, z = 15},
			rotation = { x = 0, y = 50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    }
    },

    --------------------------------

    -- ParedDerecha1 = {
    --     Transform = {
    --         position = { x = 0, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha2 = {
    --     Transform = {
    --         position = { x = 5, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha3 = {
    --     Transform = {
    --         position = { x = 10, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha4 = {
    --     Transform = {
    --         position = { x = 15, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha5 = {
    --     Transform = {
    --         position = { x = 20, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha6 = {
    --     Transform = {
    --         position = { x = 25, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha7 = {
    --     Transform = {
    --         position = { x = 30, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha8 = {
    --     Transform = {
    --         position = { x = 35, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha9 = {
    --     Transform = {
    --         position = { x = 40, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha10 = {
    --     Transform = {
    --         position = { x = 45, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha11 = {
    --     Transform = {
    --         position = { x = 50, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha12 = {
    --     Transform = {
    --         position = { x = 55, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha13 = {
    --     Transform = {
    --         position = { x = 60, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha14 = {
    --     Transform = {
    --         position = { x = 65, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha15 = {
    --     Transform = {
    --         position = { x = 70, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    -- ParedDerecha16 = {
    --     Transform = {
    --         position = { x = 75, y = 5, z = -22.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     }
    --     -- RigidBody = {
	-- 	--     colShape = 1,
	-- 	--     mvType = static,
	-- 	--     mass = 5,
    --     --     group = 1,
    --     --     mask = 2,
    --     --     colliderscale = {x = 2, y = 5, z = 0.01},
	-- 	--     restitution = .5,
	-- 	--     friction = .3,
	-- 	--     isTrigger = false
	--     -- }
    -- },

    
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

	-- Cube = {
    --     Transform = {
    --         position = { x = 0, y = 10, z = 0 },
    --         scale = { x = 1, y = 1, z = 1 },
    --         rotation = {x = 0, y = 0, z = 0}
    --     },
	-- 	meshrenderer = {
    --         mesh = "cube",
    --         meshName = "Suzanne.mesh",
    --     },
	-- 	RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = true
	--     },
    --     collider = {
    --         shape = "box",
    --         size = { x = 1, y = 1, z = 1 }
    --     },
		
	-- },

	Car = {
        Transform = {
            position = { x= 0, y = 10, z = -10 },
            scale = { x = 0.5, y = 0.5, z = 0.5 },
            rotation = {x = 0, y = 180, z = 0}
        },
        RigidBody = {
            colShape = 1,
            mvType = 0,
            mass = 1,
            group = 2,
            mask = 7,
            colliderscale = {x = 4, y = 2, z = 4},
            restitution = .5,
            friction = 0.5,
            isTrigger = false
        },
        vehicleController = {
            speed = 20;
            rotationspeed = 0.5;
            driftFactor = 1;
            playerNumber = 0;
        },
        meshrenderer = {
            mesh = "kart",
            meshName = "Kart.mesh",
            --materialName = "Material/roja"
        }
	},
    
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
            position = { x = 20, y = 10, z = -10 } -- -104 70 0 / 20 10 -10
        },
        camera = {
            lookat = { x = -20, y = 10, z = -10 }, -- -104 10 0 / -20 10 -10
            name = "main",
            neardistance = 0.5,
            fardistance = 100000,
            autoratio = true,
            zorder = 0,
            backgroundcolor = { r = .72, g = .92, b = 1, a = 1  }
        },
		camerafollow = {
			target = "car",
			offset = { x= 20, y = 10, z = -10 }
		}
    },

    -- DirectionalLight2 = {
    --     Transform = {
    --         position = { x = 0, y = 500, z = 500 }
    --     },
    --     Light = {
    --         name = "DirectionalLight2",
    --         direction = { x = -1, y = -1, z = -1 },
    --         type = 0
    --     }
    -- }, 

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


