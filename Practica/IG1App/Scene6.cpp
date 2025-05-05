#include "Scene6.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "AdvancedTIE.h"

using namespace glm;

void Scene6::init()
{
	setGL(); // OpenGL settings

	addLights();

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	AdvancedTIE* tie = new AdvancedTIE();
	gObjects.push_back(tie);

}