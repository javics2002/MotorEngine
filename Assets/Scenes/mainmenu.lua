Entities = {
    
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
    },

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "mainlight",
            direction = { x = 1, y = -1, z = -1 },
            type = 0
        }
    },
 

    Background = {
        UITransform = {
            position = { x = 0, y = 0 },
            scale = { x = 1, y = 1},
            rotation = 0
        },
        UISpriteRenderer = {
            sprite = "mainbackground",
            materialName = "Main/background"
        }
    },
    Title = {

        UISpriteRenderer = {
            sprite = "maintitle",
            materialName = "Main/title"
        },
        UITransform = {
            position = { x = 0.25, y = 0.1 },
            scale = { x = 0.5, y = 0.2},
            rotation = 0
        }
    },
    PlayButton = {
	
        UIButtonScene = {
            sprite = "mainbutton",
            materialName = "Main/button",
            scene = "Race"
        },

        UITransform = {
            position = { x = 0.25, y = 0.35 },
            scale = { x = 0.2, y = 0.2},
            rotation = 0
        }
    }
    

}


