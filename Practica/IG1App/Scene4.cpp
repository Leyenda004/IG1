#include "Scene4.h"

#include "Torus.h"

void Scene4::init()
{
	setGL(); // OpenGL settings

	addLights();

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));
	gObjects.push_back(new Torus(180, 80));
}
