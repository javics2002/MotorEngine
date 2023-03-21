Entities = {
	-- Define una entidad llamada "player"
	Plane = {
	  -- Componente Transform
	  TRANSFORM = { 
		rotation = { x = 0, y = 0, z = 0 },
		position = {},
		scale = { y = .1, z = 5, x = 5 }
	  },
	  -- Componente SpriteRenderer
	  riGidBody = {
		colShape = 1,
		mvType = static,
		mass = 5,
		restitution = .5,
		friction = .3,
		isTrigger = true
	  },
	  -- Componente Collider
	  collider = {
		shape = "box",
		size = { x = 1, y = 1, z = 1 }
	  },

	  meshrenderer = {
		mesh = "p",
		meshName = "cube.mesh"
	  }
	},

	test = {
		-- Componente Transform
	  TRANSFORM = {
		rotation = { x = 666, y = 666, z = 666 },
		position = {},
		scale = { y = .1, z = 5, x = 5 }
	  }
	}
}


