#ifdef _DEBUG
#pragma once
#ifndef __EC_MAIN
#define __EC_MAIN

#include "Utils/Vector3.h"

#include "EntityComponent/SceneManager.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Transform.h"

using namespace me;

int main() {

	sceneManager();

	/*Scene* s = sceneManager().addScene("Game").get();
	Entity* e = sceneManager().getActiveScene()->addEntity("dummyEntity").get();
	Transform* tr = e->addComponent<Transform>("transform");
	tr->setPosition(Vector3 (0, 0, 0));

	int cont = 0;
	while (cont < 100) {

		tr->setPosition(tr->getPosition() + Vector3 (-1, 1, -1));
		++cont;

		std::cout << "Entity " << e->getName() << " transform position " << tr->getPosition() << std::endl;

	};*/

	//e->removeComponent<Transform>("transform");
	//s->removeEntity(e->getName());
	//sceneManager().removeScene(s->getName());

};

#endif
#endif