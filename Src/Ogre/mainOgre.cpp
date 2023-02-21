#ifdef _DEBUG
#pragma once
#ifndef __OGRE_MAIN
#define __OGRE_MAIN



#include "Ogre.h"
#include <iostream>
using namespace me;


int main() {
	initOgre("Juegox");
	int a;
	std::cin >> a;
	return 0;
}

#endif
#endif