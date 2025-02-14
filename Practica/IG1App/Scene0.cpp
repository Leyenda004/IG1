#include "Scene0.h"
#include "RegularPolygon.h"
#include "RGBTriangle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene0::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	//
	// Color, lados, distancia al centro
	gObjects.push_back(new RegularPolygon(dvec4(0.0f, 1.0f, 1.0f, 1.0f), 3, 200.0f));
	gObjects.push_back(new RegularPolygon(dvec4(1.0f, 0.0f, 1.0f, 1.0f), 32, 200.0f));
}