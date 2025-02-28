#include "Scene3.h"
#include "Ground.h"

#include "Cube.h"
#include "BoxOutline.h"

#include "RGBTriangle.h"

#include "RegularPolygon.h"

#include "RGBRectangle.h"

#include "RGBCube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene3::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	//Ground* ground = new Ground();
	//
	//Texture* tex = new Texture();
	//tex->load("../assets/images/baldosaC.png", 255);
	//ground->setTexture(tex);
	//
	//gObjects.push_back(ground);

	BoxOutline* box = new BoxOutline(100.f);

	Texture* tex = new Texture();
	tex->load("../assets/images/container.jpg", 255);
	box->setTexture(tex);

	gObjects.push_back(box);
}