#include "Scene2.h"
#include "RGBCube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene2::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	GLdouble length = 200.f;
	RGBCube* cubito = new RGBCube(length);
	// Movemos el cubo
	cubito->setModelMat(translate(cubito->modelMat(), vec3(length/2, length/2, -length/2)));
	gObjects.push_back(cubito);

	//gObjects.push_back(new RGBCube(200.0f));


}