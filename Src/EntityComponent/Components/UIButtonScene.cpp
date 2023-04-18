#include "UIButtonScene.h"
#include "Input/InputManager.h"
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include "OgreTextAreaOverlayElement.h"
#include <OgreOverlayManager.h>
#include "Render/RenderManager.h"
#include "EntityComponent/SceneManager.h"

me::UIButtonScene::UIButtonScene()
{
}

me::UIButtonScene::~UIButtonScene()
{
	renderManager().destroyUISprite(mName);
}

void me::UIButtonScene::init(std::string name, std::string materialName, float width, float height, float left, float top)
{
	mName = name;
	mSpriteName = materialName;

	if (mSpriteName.size() > 0)
	{
		renderManager().createSprite(mName, mSpriteName);
	}
	mInteractive = true;

}

void me::UIButtonScene::start()
{
}


void me::UIButtonScene::setNewScene(std::string newScene) {
	mNewScene = newScene;
}

void me::UIButtonScene::update()
{
	

	if (inputManager().getButton("LEFTCLICK")) {
		Vector2 mousePosition = me::inputManager().getMousePositon();
		if (mousePosition.x >= getPos().x && mousePosition.x <= getPos().x + getSize().x &&
			mousePosition.y >= getPos().y && mousePosition.y <= getPos().y + getSize().y) {
			execute();
		}
	}
}

void me::UIButtonScene::execute()
{
	sceneManager().changeScene(mNewScene);

}

std::string me::UIButtonScene::getName()
{
	return mName;
}

void me::UIButtonScene::setSpriteMaterial(std::string materialName)
{
	renderManager().setUISpriteMaterial(mName, materialName);
}


