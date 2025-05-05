#include "Scene5.h"

#include "IndexedBox.h"

void Scene5::init()
{
	setGL(); // OpenGL settings

	addLights();

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));
	gObjects.push_back(new IndexedBox(200.0f));
}
